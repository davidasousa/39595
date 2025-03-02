#include "ChessBoard.hh"
#include "PawnPiece.hh"
#include "RookPiece.hh"
#include "BishopPiece.hh"
#include "KingPiece.hh"

using Student::ChessBoard;

// Constructor
ChessBoard::ChessBoard(int numRow, int numCol) {
	numRows = numRow;
	numCols = numCol;

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

// Creating Chess Piece
void ChessBoard::createChessPiece(Color col, Type ty, int startRow, int startColumn) {
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
	/*
	case King:
		newPiece = new KingPiece(*this, col, startRow, startColumn);
		break;
	*/
	}
	board[startRow][startColumn] = newPiece;
}

bool ChessBoard::movePiece(int fromRow, int fromColumn, int toRow, int toColumn) {
	return false;
}

bool ChessBoard::isValidMove(int fromRow, int fromColumn, int toRow, int toColumn) {
	return board[fromRow][fromColumn] -> canMoveToLocation(toRow, toColumn);
}

bool ChessBoard::isPieceUnderThreat(int row, int column) {
	return false;
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
