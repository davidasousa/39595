#ifndef __PAWNPIECE_H__
#define __PAWNPIECE_H__

#include "ChessPiece.hh"

// Helper Function
int abs(int input) { return (input < 0) ? -input : input; }

/**
 * Student implementation of a Pawn chess piece.
 * The class is defined within the Student namespace.
 */
namespace Student
{
    class PawnPiece : public ChessPiece {
		public:
			// Bishop Constructor
			PawnPiece(ChessBoard& board, Color color, int row, int column) 
				: ChessPiece(board, color, row, column) {
				_type = Pawn;
				_string = (color == White) ? (char*) u8"\u2659" : (char*) u8"\u265F";
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

				// Changing Columns
				if(toColumn != _column) { 
					// Column Not 1 Column Away
					if(abs(toColumn - _column) != 1) { return false; }
					// No Piece
					if(_board.getPiece(toRow, toColumn) == nullptr) { return false; }
					// Same Color Piece
					if(_board.getPiece(toRow, toColumn) -> getColor() == _color) { return false; } 
				} else if(destPiece != nullptr) { return false; } // Capture Without Changing Columns

				// Row Movement
				int delta = toRow - _row;
				if(_color == White) {
					if(_row == _board.getNumRows() - 2) {
						if(delta < -2 || delta > -1) { return false; }
					} else {
						if(delta != -1) { return false; }
					}
				} else if(_color == Black) {
					if(_row == 1) {
						if(delta < 1 || delta > 2) { return false; }
					} else {
						if(delta != 1) { return false; }
					}
				}

				return true;
			}

			virtual const char *toString() { return _string; }
	
    };
}

#endif
