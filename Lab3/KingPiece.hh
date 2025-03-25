#ifndef __KINGPIECE_H__
#define __KINGPIECE_H__

#include "ChessPiece.hh"

/**
 * Student implementation of a King chess piece.
 * The class is defined within the Student namespace.
 */

namespace Student 
{
	class KingPiece : public ChessPiece {
	public:
		// King Constructor
		KingPiece(ChessBoard& board, Color color, int row, int column) 
			: ChessPiece(board, color, row, column) {
			_type = King;
			_string = (color == White) ? (char*) u8"\u2654" : (char*) u8"\u265A" ;
		}
		
		virtual bool canMoveToLocation(int toRow, int toColumn) {
			// Redundant Move
			if(toRow == _row && toColumn == _column) { return false; }

			// Check Movement Within Bounds
			if(toRow <= -1 || toRow >= _board.getNumRows()) { return false; }
			if(toColumn <= -1 || toColumn >= _board.getNumCols()) { return false; }

			// Check If To Square Has Same Color Piece
			ChessPiece* destPiece = _board.getPiece(toRow, toColumn);
			if(destPiece != nullptr && destPiece -> getColor() == _color) { return false; }

			// Ensure 1 Square Either Direction
			int deltaX = abs(toRow - _row);
			int deltaY = abs(toColumn - _column);

			if(deltaX > 1 || deltaY > 1) { return false; }

			return true;
		}

		virtual bool isValidCastle(int toRow, int toColumn, int* crX, int* crY) {
			if(_hasMoved == true) { return false; }
			// Invalid Moves
			if(toRow == _row && toColumn == _column) { return false; }
			if(toRow != _row) { return false; }
			// Check Movement Within Bounds
			if(toRow <= -1 || toRow >= _board.getNumRows()) { return false; }
			if(toColumn <= -1 || toColumn >= _board.getNumCols()) { return false; }

			ChessPiece* castleRook = nullptr;
			// Check King Moved 2 Columns
			int deltaX = toColumn - _column;
			if(deltaX == -2) {
				// Ensure No Piece Between The Rook & King
				for(int idx = _column - 1; idx != -1; idx--) {
					ChessPiece* piece = _board.getPiece(_row, idx);
					if(piece != nullptr) { 
						if(piece -> getType() == Rook && piece -> getColor() == _color) { 
							castleRook = piece; 
							break;
						} else { return false; }
					}
				}
			} else if(deltaX == 2) {
				// Ensure No Piece Between The Rook & King
				for(int idx = _column + 1; idx != _board.getNumRows(); idx++) {
					ChessPiece* piece = _board.getPiece(_row, idx);
					if(piece != nullptr) { 
						if(piece -> getType() == Rook && piece -> getColor() == _color) { 
							castleRook = piece; 
							break;
						} else { return false; }
					} 		
				}
			} else { return false; }

			// No Valid Rook Was Found
			if(castleRook == nullptr) { return false; }
			// If The King & Rook Were Within Two Squares Of Each Other
			if(abs(castleRook -> getColumn() - _column) <= 2) { return false; }

			// Check If The King Would Be Under Threat
			if(deltaX == 2) {
				if(_board.isPieceUnderThreat(_row, _column)) { return false; }
				if(_board.isTempPieceUnderThreat(_row, _column, _row, _column + 1)) { return false; }
				if(_board.isTempPieceUnderThreat(_row, _column, _row, _column + 2)) { return false; }
			}
			if(deltaX == -2) {
				if(_board.isPieceUnderThreat(_row, _column)) { return false; }
				if(_board.isTempPieceUnderThreat(_row, _column, _row, _column - 1)) { return false; }
				if(_board.isTempPieceUnderThreat(_row, _column, _row, _column - 2)) { return false; }
			}

			// Passing The Rook Info
			*crY = castleRook -> getRow();
			*crX = castleRook -> getColumn();
			return true;
		}

		virtual const char *toString() { return _string; }	
	};
}

#endif
