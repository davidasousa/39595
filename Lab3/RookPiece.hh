#ifndef _ROOKPIECE_H__
#define _ROOKPIECE_H__

#include "ChessPiece.hh"

/**
 * Student implementation of a Rook chess piece.
 * The class is defined within the Student namespace.
 */
namespace Student
{
    class RookPiece : public ChessPiece {
		public:
			// Bishop Constructor
			RookPiece(ChessBoard& board, Color color, int row, int column) 
				: ChessPiece(board, color, row, column) {
				_type = Rook;
				_string = (color == White) ? (char*) U'\u2656' : (char*) U'\u265C';
			}
			
			// Destructor
			virtual ~RookPiece() {};

			virtual bool canMoveToLocation(int toRow, int toColumn) {
				// Redundant Move
				if(toRow == _row && toColumn == _column) { return false; }
				// Check Movement Within Bounds
				if(toRow <= -1 || toRow >= 8) { return false; }
				if(toColumn <= -1 || toColumn >= 8) { return false; }	
				// Both Row & Column Changes
				if(toRow != _row && toColumn != _column) { return false; }
				return true;
			}

			virtual const char *toString() { return _string; }
	
    };
}

#endif
