#!/bin/bash
sed -i 's/if (board.isCapture(m) || m.typeOf() == Move::ENPASSANT || m.typeOf() == Move::PROMOTION) {/if (board.isCapture(m) || m.typeOf() == Move::ENPASSANT || m.typeOf() == Move::PROMOTION || (m.typeOf() == Move::NORMAL && board.at(m.from()).type() == chess::PieceType::PAWN && (m.to().rank() == chess::Rank::RANK_7 || m.to().rank() == chess::Rank::RANK_2))) {/g' nnue_engine.cpp
