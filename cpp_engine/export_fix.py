import torch
import torch.nn as nn
import numpy as np
import sys

NUM_FEATURES = 40960
HIDDEN_SIZE  = 256

class HalfKPNet(nn.Module):
    def __init__(self):
        super().__init__()
        self.fc1 = nn.Linear(NUM_FEATURES, HIDDEN_SIZE)
        self.fc2 = nn.Linear(HIDDEN_SIZE * 2, 1)

    def forward(self, w_features, b_features):
        w_acc = torch.clamp(self.fc1(w_features), 0.0, 1.0)
        b_acc = torch.clamp(self.fc1(b_features), 0.0, 1.0)
        acc   = torch.cat([w_acc, b_acc], dim=1)
        return torch.sigmoid(self.fc2(acc))

def export_correct_weights(model_path, out_path):
    device = torch.device('cpu')
    model = HalfKPNet().to(device)
    model.load_state_dict(torch.load(model_path, map_location=device))
    model.eval()

    # Transpose fc1.weight from (256, 40960) to (40960, 256)
    # copy() is needed because .T returns a view which might not be contiguous C-order
    fc1_w = (model.fc1.weight.detach().cpu().numpy().T.copy() * 256).astype('int16')
    fc1_b = (model.fc1.bias.detach().cpu().numpy() * 256).astype('int16')
    fc2_w = (model.fc2.weight.detach().cpu().numpy() * 64).astype('int16')
    fc2_b = (model.fc2.bias.detach().cpu().numpy() * 64 * 256).astype('int32')

    with open(out_path, 'wb') as f:
        f.write(fc1_w.tobytes())
        f.write(fc1_b.tobytes())
        f.write(fc2_w.tobytes())
        f.write(fc2_b.tobytes())
    print(f"Corrected NNUE weights exported to {out_path}")

if __name__ == "__main__":
    export_correct_weights("best_model.pth", "nnue_weights.bin")
