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
				_string = (color == White) ? (char*) u8"\u2656" : (char*) u8"\u265C";
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

				// Both Row & Column Changes -> Invalid
				if(toRow != _row && toColumn != _column) { return false; }
				else if(toRow != _row && toColumn == _column) { // Rows Dont Align
					int upperRow = (toRow > _row) ? toRow : _row;
					int lowerRow = (toRow < _row) ? toRow : _row;
					for(int rowIdx = lowerRow + 1; rowIdx != upperRow; rowIdx++) {
						if(_board.getPiece(rowIdx, _column) != nullptr) { return false; }
					}
				} else if(toRow == _row && toColumn != _column) { // Cols Dont Align
					int upperCol = (toColumn > _column) ? toColumn : _column;
					int lowerCol = (toColumn < _column) ? toColumn : _column;
					for(int colIdx = lowerCol + 1; colIdx != upperCol; colIdx++) {
						if(_board.getPiece(_row, colIdx) != nullptr) { return false; }
					}
				}
				
				if(_board.isMoveCauseCheck(_row, _column, toRow, toColumn)) { return false; }
								
				return true;
			}

			virtual const char *toString() { return _string; }
	
    };
}

#endif
