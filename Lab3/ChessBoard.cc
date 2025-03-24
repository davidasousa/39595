#include "ChessBoard.hh"
#include "PawnPiece.hh"
#include "RookPiece.hh"
#include "BishopPiece.hh"
#include "KingPiece.hh"
#include <iostream>

using Student::ChessBoard;

// Constructor
ChessBoard::ChessBoard(int numRow, int numCol) {
	numRows = numRow;
	numCols = numCol;
	turn = White;

	// Initialize Board Vector
	for(int idx = 0; idx < numRows; idx++) {
		board.push_back(std::vector<ChessPiece *>{});
		for(int jdx = 0; jdx < numCols; jdx++) {
			board[idx].push_back(nullptr);
		}
	}
}

// Destructor
ChessBoard::~ChessBoard() {
	for(int idx = 0; idx < numRows; idx++) {
		for(int jdx = 0; jdx < numCols; jdx++) {
			if(board[idx][jdx] != nullptr) { 
				delete board[idx][jdx]; 
			}
		}
	}
}

// Clone Function
void* ChessBoard::clone(int row, int col) {
	if(board[row][col] == nullptr) { return nullptr; }
	Color pieceColor = board[row][col] -> getColor();
	ChessPiece* newPiece = nullptr;
	switch(board[row][col] -> getType()) {
	case King: newPiece = new KingPiece(*this, pieceColor, row, col); break;
	case Pawn: newPiece = new PawnPiece(*this, pieceColor, row, col); break;
	case Bishop: newPiece = new BishopPiece(*this, pieceColor, row, col); break;
	case Rook: newPiece = new RookPiece(*this, pieceColor, row, col); break;
	}
	return newPiece;
}

bool ChessBoard::isKingUnderThreat(Color color) {
	for(int rowIdx = 0; rowIdx < numRows; rowIdx++) {
		for(int colIdx = 0; colIdx < numCols; colIdx++) {
			if(board[rowIdx][colIdx] == nullptr) { continue; }
			if(board[rowIdx][colIdx] -> getColor() == color) { continue; }
			if(board[rowIdx][colIdx] -> getType() == King) { 
				if(isPieceUnderThreat(rowIdx,colIdx)) { return true; }
			}
		}
	}
	return false;
}

// Creating Chess Piece
void ChessBoard::createChessPiece(Color col, Type ty, int startRow, int startColumn) {
	if(board[startRow][startColumn] != nullptr) { 
		delete board[startRow][startColumn]; 
		board[startRow][startColumn] = nullptr;
	}
	ChessPiece* newPiece = nullptr;
	switch(ty) {
	case Pawn:
		newPiece = new PawnPiece(*this, col, startRow, startColumn);
		break;
	case Rook:
		newPiece = new RookPiece(*this, col, startRow, startColumn);
		break;
	case Bishop:
		newPiece = new BishopPiece(*this, col, startRow, startColumn);
		break;
	case King:
		newPiece = new KingPiece(*this, col, startRow, startColumn);
		break;
	}
	board[startRow][startColumn] = newPiece;
}

bool ChessBoard::movePiece(int fromRow, int fromColumn, int toRow, int toColumn) {
	if(board[fromRow][fromColumn] == nullptr) { return false; }
	if(turn != board[fromRow][fromColumn] -> getColor()) { return false; }
	if(board[fromRow][fromColumn] -> getColor() != turn) { return false; } // Out Of Turn
	if(!isValidMove(fromRow, fromColumn, toRow, toColumn)) { return false; } // Invalid Move

	// If Capture -> Delete & Remove Piece
	if(board[toRow][toColumn] != nullptr) { delete board[toRow][toColumn]; }

	board[fromRow][fromColumn] -> setPosition(toRow, toColumn);
	board[toRow][toColumn] = board[fromRow][fromColumn];
	board[fromRow][fromColumn] = nullptr;

	// Changing Turn
	if(turn == White) { turn = Black; }
	else if(turn == Black) { turn = White; }
	return true;
}

bool ChessBoard::isValidMove(int fromRow, int fromColumn, int toRow, int toColumn) {
	return board[fromRow][fromColumn] -> canMoveToLocation(toRow, toColumn);
}

bool ChessBoard::isPieceUnderThreat(int row, int column) {
	if(board[row][column] == nullptr) { return false; }
	Color pieceColor = board[row][column] -> getColor();
	// Piece Under Threat
	for(int rowIdx = 0; rowIdx < numRows; rowIdx++) {
		for(int colIdx = 0; colIdx < numCols; colIdx++) {
			ChessPiece* threatPiece = board[rowIdx][colIdx];
			if(threatPiece == nullptr) { continue; }
			if(threatPiece -> getColor() == pieceColor) { continue; }
			if(isValidMove(rowIdx, colIdx, row, column)) { return true; }
		}
	}
	return false; // No Piece Threatening
}

bool ChessBoard::isTempPieceUnderThreat(int fromRow, int fromCol, int toRow, int toCol) {
	bool ans = false;
	Color color = board[fromRow][fromCol] -> getColor();

	// Saving Old Pieces
	ChessPiece* tempPiece = (ChessPiece*) clone(toRow, toCol);
	ChessPiece* tempKing = (ChessPiece*) clone(fromRow, fromCol);
	
	// Check If Two Kings Are Touching
	for(int rowIdx = 0; rowIdx < numRows; rowIdx++) {
		for(int colIdx = 0; colIdx < numCols; colIdx++) {
			if(board[rowIdx][colIdx] == nullptr) { continue; }
			if(rowIdx == toRow && colIdx == toCol) { continue; }
			if(rowIdx == fromRow && colIdx == fromCol) { continue; }
			if(board[rowIdx][colIdx] -> getType() == King) { 
				int deltaX = abs(toRow - rowIdx);
				int deltaY = abs(toCol - colIdx);
				if(deltaX <= 1 && deltaY <= 1) { 
					delete tempPiece;
					delete tempKing;
					return true; 
				}
			}
		}
	}
	// End Two King Touching

	delete board[toRow][toCol];
	delete board[fromRow][fromCol];
	board[toRow][toCol] = nullptr;
	board[fromRow][fromCol] = nullptr;

	// Testing New Board
	createChessPiece(color, King, toRow, toCol);
	if(isPieceUnderThreat(toRow, toCol)) { ans = true; }

	// Restoring Board
	delete board[toRow][toCol];
	board[toRow][toCol] = tempPiece;
	board[fromRow][fromCol] = tempKing;

	return ans;
}

bool ChessBoard::isMoveCauseCheck(int fromRow, int fromCol, int toRow, int toCol) {
	bool res = false;
	Color pieceColor = board[fromRow][fromCol] -> getColor();
	// Finding King
	ChessPiece* kingPiece = nullptr;
	if(turn == pieceColor) { // Only Consider Safety Of King Whose Turn It Is
		for(int rowIdx = 0; rowIdx < numRows; rowIdx++) {
			for(int colIdx = 0; colIdx < numCols; colIdx++) {
				if(board[rowIdx][colIdx] == nullptr) { continue; }
				if(board[rowIdx][colIdx] -> getType() == King) {
					if(board[rowIdx][colIdx] -> getColor() == pieceColor) { 
						kingPiece = board[rowIdx][colIdx]; 
					}
				}
			}
		}
	}
	if(kingPiece == nullptr) { return res; } 
	// Saving And Taking Old Pieces Off Board
	ChessPiece* tempFromPiece = (ChessPiece*) clone(fromRow, fromCol);
	ChessPiece* tempToPiece = (ChessPiece*) clone(toRow, toCol);
	delete board[fromRow][fromCol];
	delete board[toRow][toCol];
	board[fromRow][fromCol] = nullptr;
	board[toRow][toCol] = nullptr;

	// Creating New Piece
	createChessPiece(tempFromPiece -> getColor(), tempFromPiece -> getType(), toRow, toCol);
	// Checking
	if(isPieceUnderThreat(kingPiece -> getRow(), kingPiece -> getColumn())) { res = true; }
	delete board[toRow][toCol];
	board[toRow][toCol] = nullptr;

	// Moving Pieces Back
	board[fromRow][fromCol] = tempFromPiece;	
	board[toRow][toCol] = tempToPiece;
	// Returning Result
	return res;	
}

std::ostringstream ChessBoard::displayBoard()
{
    std::ostringstream outputString;
    // top scale
    outputString << "  ";
    for (int i = 0; i < numCols; i++)
    {
        outputString << i;
    }
    outputString << std::endl
                 << "  ";
    // top border
    for (int i = 0; i < numCols; i++)
    {
        outputString << "-";
    }
    outputString << std::endl;

    for (int row = 0; row < numRows; row++)
    {
        outputString << row << "|";
        for (int column = 0; column < numCols; column++)
        {
            ChessPiece *piece = board.at(row).at(column);
            outputString << (piece == nullptr ? " " : piece->toString());
        }
        outputString << "|" << std::endl;
    }

    // bottom border
    outputString << "  ";
    for (int i = 0; i < numCols; i++)
    {
        outputString << "-";
    }
    outputString << std::endl
                 << std::endl;

    return outputString;
}
