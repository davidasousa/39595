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

			// Check If King Would Be In Check
			if(_board.isKingInCheck(toRow, toColumn, _color)) { return false; }

			// Ensure 1 Square Either Direction
			int deltaX = abs(toRow - _row);
			int deltaY = abs(toColumn - _column);

			if(deltaX > 1 || deltaY > 1) { return false; }

			return true;
		}

		virtual const char *toString() { return _string; }	
	};
}

#endif
