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
	int crX = -1; int crY = -1;
	ChessPiece* piece = board[fromRow][fromColumn];
	if(piece == nullptr) { return false; }
	if(turn != piece -> getColor()) { return false; }
	if(piece -> getColor() != turn) { return false; } // Out Of Turn
	// Check If Castling
	if(piece -> getType() == King && piece -> isValidCastle(toRow, toColumn, &crX, &crY)) {
		// Set Moved
		board[fromRow][fromColumn] -> setMoved();
		board[crY][crX] -> setMoved();

		ChessPiece* kingPiece = board[fromRow][fromColumn];
		ChessPiece* otherPiece = board[crY][crX];
		board[fromRow][fromColumn] = nullptr;
		board[crY][crX] = nullptr;

		if(toColumn < fromColumn) {
			// Move The King
			kingPiece -> setPosition(fromRow, fromColumn - 2);
			board[fromRow][fromColumn - 2] = kingPiece;
			// Move The Rook
			otherPiece -> setPosition(fromRow, fromColumn - 1);
			board[fromRow][fromColumn - 1] = otherPiece;
		} else {
			// Move The King
			kingPiece -> setPosition(fromRow, fromColumn + 2);
			board[toRow][fromColumn + 2] = kingPiece;
			// Move The Rook
			otherPiece -> setPosition(fromRow, fromColumn + 1);
			board[toRow][fromColumn + 1] = otherPiece;
		}
		return true;
	}
	if(!isValidMove(fromRow, fromColumn, toRow, toColumn)) { return false; } // Invalid Move

	// If Capture -> Delete & Remove Piece
	if(board[toRow][toColumn] != nullptr) { delete board[toRow][toColumn]; }

	board[fromRow][fromColumn] -> setPosition(toRow, toColumn);
	board[toRow][toColumn] = board[fromRow][fromColumn];
	board[fromRow][fromColumn] = nullptr;

	// Changing Turn
	if(turn == White) { turn = Black; }
	else if(turn == Black) { turn = White; }
	// Setting The Moved Flag
	if(piece -> hasMoved() == false) { piece -> setMoved(); }
	return true;
}

bool ChessBoard::isValidMove(int fromRow, int fromColumn, int toRow, int toColumn) {
	ChessPiece* piece = board[fromRow][fromColumn];
	int crX = -1; int crY = -1;
	if(piece -> getType() == King && piece -> isValidCastle(toRow, toColumn, &crX, &crY)) {
		return true;
	}
	if(!piece -> canMoveToLocation(toRow, toColumn)) { return false; }
	if(piece -> getType() == King) {
		if(isTempPieceUnderThreat(fromRow, fromColumn, toRow, toColumn)) { return false; }
	} else {
		if(isMoveCauseCheck(fromRow, fromColumn, toRow, toColumn)) { return false; }
	}
	return true;
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

			// Check If Piece Within Range Of A Enemy King But Our King Is Protecting
			if(threatPiece -> getType() == King) {
				int deltaX = abs(row - rowIdx);
				int deltaY = abs(column - colIdx);
				if(deltaX <= 1 && deltaY <= 1) { 
					return true; 
				}
			} else if(board[rowIdx][colIdx] -> canMoveToLocation(row, column)) { return true; }
		}
	}
	return false; // No Piece Threatening
}

bool ChessBoard::isTempPieceUnderThreat(int fromRow, int fromCol, int toRow, int toCol) {
	bool ans = false;
	Color color = board[fromRow][fromCol] -> getColor();

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
					return true; 
				}
			}
		}
	}
	// End Two King Touching

	// Saving Old Pieces
	ChessPiece* tempPiece = board[toRow][toCol];
	ChessPiece* tempKing = board[fromRow][fromCol];
	
	board[toRow][toCol] = nullptr;
	board[fromRow][fromCol] = nullptr;

	// Testing New Board
	createChessPiece(color, King, toRow, toCol);
	if(isPieceUnderThreat(toRow, toCol)) { ans = true; }
	delete board[toRow][toCol];
	board[toRow][toCol] = nullptr;

	// Restoring Board
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
	ChessPiece* tempFromPiece = board[fromRow][fromCol];
	ChessPiece* tempToPiece = board[toRow][toCol];
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
