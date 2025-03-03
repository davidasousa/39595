#ifndef __BISHOPPIECE_H__
#define __BISHOPPIECE_H__

#include "ChessPiece.hh"

/**
 * Student implementation of a Bishop chess piece.
 * The class is defined within the Student namespace.
 */
namespace Student {
	class BishopPiece : public ChessPiece {
		public:
			// Bishop Constructor
			BishopPiece(ChessBoard& board, Color color, int row, int column) 
				: ChessPiece(board, color, row, column) {
				_type = Bishop;
				_string = (color == White) ? (char*) U'\u2657' : (char*) U'\u265D';
			}
			
			// Destructor
			virtual ~BishopPiece() {};

			virtual bool canMoveToLocation(int toRow, int toColumn) {
				// Redundant Move
				if(toRow == _row && toColumn == _column) { return false; }

				// Check Movement Within Bounds
				if(toRow <= -1 || toRow >= _board.getNumRows()) { return false; }
				if(toColumn <= -1 || toColumn >= _board.getNumCols()) { return false; }

				// Check If To Square Has Same Color Piece
				ChessPiece* destPiece = _board.getPiece(toRow, toColumn);
				if(destPiece != nullptr && destPiece -> getColor() == _color) { return false; }

				// Check Change In Both Directions Has Equal Magnitude
				int deltaRatio = (toRow - _row) / (toColumn - _column);
				if(!(deltaRatio == 1 || deltaRatio == -1)) { return false; }
				return true;
			}

			virtual const char *toString() { return _string; }
	
	};
}

#endif
