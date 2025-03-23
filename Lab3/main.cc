#include <assert.h>
#include "Chess.h"
#include "ChessBoard.hh"
#include "ChessPiece.hh"

#include <iostream>

int test_part1_4x4_1()
{
	// Config file content:
	// 0
	// 4 4
	// w r 3 2
	// b b 1 3
	// b r 1 1
	// w r 2 3
	// ~
	// isValidScan

	// Corresponding code
	Student::ChessBoard sBoard(4, 4);
	sBoard.createChessPiece(White, Rook, 3, 2);
	sBoard.createChessPiece(Black, Bishop, 1, 3);
	sBoard.createChessPiece(Black, Rook, 1, 1);
	sBoard.createChessPiece(White, Rook, 2, 3);

	// Calls isValidMove() from every position to every
	// other position on the chess board for all pieces.

	// Testing The White Rook On 3,2
	if(sBoard.isValidMove(3, 2, -1, 2)) { return 1; }
	if(sBoard.isValidMove(3, 2, 4, 2)) { return 1; }
	if(!sBoard.isValidMove(3, 2, 2, 2)) { return 1; }
	if(!sBoard.isValidMove(3, 2, 3, 0)) { return 1; }

	// Testing The White Rook On 2,3
	if(!sBoard.isValidMove(2, 3, 1, 3)) { return 1; }
	if(sBoard.isValidMove(2, 3, 0, 3)) { return 1; }
	if(sBoard.isValidMove(2, 3, -1, 3)) { return 1; }

	// Testing The Black Rook On 1,1
	if(!sBoard.isValidMove(1, 1, 1, 2)) { return 1; }
	if(sBoard.isValidMove(1, 1, 1, 3)) { return 1; }
	if(sBoard.isValidMove(2, 3, 0, 0)) { return 1; } // Diagonal Move
	if(sBoard.isValidMove(2, 3, 2, 3)) { return 1; } // Redundant Move

	return 0;
}

int test_part1_4x4_2() {
	Student::ChessBoard sBoard(4, 4);
	sBoard.createChessPiece(White, Bishop, 0, 0);
	sBoard.createChessPiece(Black, Bishop, 2, 2);
	sBoard.createChessPiece(Black, Bishop, 3, 3);

	if(!sBoard.isValidMove(0, 0, 2, 2)) { return 1; }
	if(sBoard.isValidMove(0, 0, 3, 3)) { return 1; }

	return 0;
}

int test_part1_4x4_3() {
	Student::ChessBoard sBoard(4, 4);
	sBoard.createChessPiece(Black, Pawn, 1, 0);
	sBoard.createChessPiece(White, Pawn, 2, 1);

	// Testing Black Pawn
	if(sBoard.isValidMove(1, 0, 0, 0)) { return 1; }
	if(sBoard.isValidMove(1, 0, 1, 2)) { return 1; }
	if(!sBoard.isValidMove(1, 0, 2, 0)) { return 1; }
	if(!sBoard.isValidMove(1, 0, 2, 1)) { return 1; }
	if(!sBoard.isValidMove(1, 0, 3, 0)) { return 1; }

	// Testing White Pawn
	if(!sBoard.isValidMove(2, 1, 0, 1)) { return 1; }
	if(sBoard.isValidMove(2, 1, 1, 2)) { return 1; }
	if(!sBoard.isValidMove(2, 1, 1, 1)) { return 1; }
	if(!sBoard.isValidMove(2, 1, 0, 1)) { return 1; }

	return 0;
}

int test_part1_4x4_4() {
	Student::ChessBoard sBoard(4, 4);
	sBoard.createChessPiece(White, Rook, 3, 2);
	sBoard.createChessPiece(Black, Bishop, 1, 3);
	sBoard.createChessPiece(Black, Rook, 1, 1);
	sBoard.createChessPiece(White, Rook, 2, 3);

	// Testing The Black Rook
	if(sBoard.isValidMove(1, 1, 0, 0)) { return 1; }
	if(sBoard.isValidMove(1, 1, 0, 1) == false) { return 1; }
	if(sBoard.isValidMove(1, 1, 0, 2)) { return 1; }
	if(sBoard.isValidMove(1, 1, 0, 3)) { return 1; }
	if(sBoard.isValidMove(1, 1, 1, 0) == false) { return 1; }
	if(sBoard.isValidMove(1, 1, 1, 1)) { return 1; }
	if(sBoard.isValidMove(1, 1, 1, 2) == false) { return 1; }
	if(sBoard.isValidMove(1, 1, 1, 3)) { return 1; }
	if(sBoard.isValidMove(1, 1, 2, 0)) { return 1; }
	if(sBoard.isValidMove(1, 1, 2, 1) == false) { return 1; }
	if(sBoard.isValidMove(1, 1, 2, 2)) { return 1; }
	if(sBoard.isValidMove(1, 1, 2, 3)) { return 1; }
	if(sBoard.isValidMove(1, 1, 3, 0)) { return 1; }
	if(sBoard.isValidMove(1, 1, 3, 1) == false) { return 1; }
	if(sBoard.isValidMove(1, 1, 3, 2)) { return 1; }
	if(sBoard.isValidMove(1, 1, 3, 3)) { return 1; }

	// Testing The Black Bishop
	if(sBoard.isValidMove(1, 3, 0, 0)) { return 1; }
	if(sBoard.isValidMove(1, 3, 0, 1)) { return 1; }
	if(sBoard.isValidMove(1, 3, 0, 2) == false) { return 1; }
	if(sBoard.isValidMove(1, 3, 0, 3)) { return 1; }
	if(sBoard.isValidMove(1, 3, 1, 0)) { return 1; }
	if(sBoard.isValidMove(1, 3, 1, 1)) { return 1; }
	if(sBoard.isValidMove(1, 3, 1, 2)) { return 1; }
	if(sBoard.isValidMove(1, 3, 1, 3)) { return 1; }
	if(sBoard.isValidMove(1, 3, 2, 0)) { return 1; }
	if(sBoard.isValidMove(1, 3, 2, 1)) { return 1; }
	if(sBoard.isValidMove(1, 3, 2, 2) == false) { return 1; }
	if(sBoard.isValidMove(1, 3, 2, 3)) { return 1; }
	if(sBoard.isValidMove(1, 3, 3, 0)) { return 1; }
	if(sBoard.isValidMove(1, 3, 3, 1 == false)) { return 1; }
	if(sBoard.isValidMove(1, 3, 3, 2)) { return 1; }
	if(sBoard.isValidMove(1, 3, 3, 3)) { return 1; }

	// Testing The First White Rook
	if(sBoard.isValidMove(3, 2, 0, 0)) { return 1; }
	if(sBoard.isValidMove(3, 2, 0, 1)) { return 1; }
	if(sBoard.isValidMove(3, 2, 0, 2) == false) { return 1; }
	if(sBoard.isValidMove(3, 2, 0, 3)) { return 1; }
	if(sBoard.isValidMove(3, 2, 1, 0)) { return 1; }
	if(sBoard.isValidMove(3, 2, 1, 1)) { return 1; }
	if(sBoard.isValidMove(3, 2, 1, 2) == false) { return 1; }
	if(sBoard.isValidMove(3, 2, 1, 3)) { return 1; }
	if(sBoard.isValidMove(3, 2, 2, 0)) { return 1; }
	if(sBoard.isValidMove(3, 2, 2, 1)) { return 1; }
	if(sBoard.isValidMove(3, 2, 2, 2) == false) { return 1; }
	if(sBoard.isValidMove(3, 2, 2, 3)) { return 1; }
	if(sBoard.isValidMove(3, 2, 3, 0) == false) { return 1; }
	if(sBoard.isValidMove(3, 2, 3, 1) == false) { return 1; }
	if(sBoard.isValidMove(3, 2, 3, 2)) { return 1; }
	if(sBoard.isValidMove(3, 2, 3, 3) == false) { return 1; }

	// Testing The Second White Rook
	if(sBoard.isValidMove(2, 3, 0, 0)) { return 1; }
	if(sBoard.isValidMove(2, 3, 0, 1)) { return 1; }
	if(sBoard.isValidMove(2, 3, 0, 2)) { return 1; }
	if(sBoard.isValidMove(2, 3, 0, 3)) { return 1; }
	if(sBoard.isValidMove(2, 3, 1, 0)) { return 1; }
	if(sBoard.isValidMove(2, 3, 1, 1)) { return 1; }
	if(sBoard.isValidMove(2, 3, 1, 2)) { return 1; }
	if(sBoard.isValidMove(2, 3, 1, 3) == false) { return 1; }
	if(sBoard.isValidMove(2, 3, 2, 0) == false) { return 1; }
	if(sBoard.isValidMove(2, 3, 2, 1) == false) { return 1; }
	if(sBoard.isValidMove(2, 3, 2, 2) == false) { return 1; }
	if(sBoard.isValidMove(2, 3, 2, 3)) { return 1; }
	if(sBoard.isValidMove(2, 3, 3, 0)) { return 1; }
	if(sBoard.isValidMove(2, 3, 3, 1)) { return 1; }
	if(sBoard.isValidMove(2, 3, 3, 2)) { return 1; }
	if(sBoard.isValidMove(2, 3, 3, 3) == false) { return 1; }

	return 0;
}

int test_part1_4x4_5() {
	Student::ChessBoard sBoard(4, 4);
	sBoard.createChessPiece(White, Rook, 1, 0);
	sBoard.createChessPiece(White, Pawn, 1, 1);
	sBoard.createChessPiece(White, Bishop, 2, 2);
	sBoard.createChessPiece(Black, Pawn, 0, 1);

	// Testing The Black Pawn
	if(sBoard.isValidMove(0, 1, 0, 0)) { return 1; }
	if(sBoard.isValidMove(0, 1, 0, 1)) { return 1; }
	if(sBoard.isValidMove(0, 1, 0, 2)) { return 1; }
	if(sBoard.isValidMove(0, 1, 0, 3)) { return 1; }
	if(sBoard.isValidMove(0, 1, 1, 0) == false) { return 1; }
	if(sBoard.isValidMove(0, 1, 1, 1)) { return 1; }
	if(sBoard.isValidMove(0, 1, 1, 2)) { return 1; }
	if(sBoard.isValidMove(0, 1, 1, 3)) { return 1; }
	if(sBoard.isValidMove(0, 1, 2, 0)) { return 1; }
	if(sBoard.isValidMove(0, 1, 2, 1)) { return 1; }
	if(sBoard.isValidMove(0, 1, 2, 2)) { return 1; }
	if(sBoard.isValidMove(0, 1, 2, 3)) { return 1; }
	if(sBoard.isValidMove(0, 1, 2, 0)) { return 1; }
	if(sBoard.isValidMove(0, 1, 2, 1)) { return 1; }
	if(sBoard.isValidMove(0, 1, 2, 2)) { return 1; }
	if(sBoard.isValidMove(0, 1, 2, 3)) { return 1; }


	// Testing The White Pawn
	if(sBoard.isValidMove(1, 1, 0, 0)) { return 1; }
	if(sBoard.isValidMove(1, 1, 0, 1)) { return 1; }
	if(sBoard.isValidMove(1, 1, 0, 2)) { return 1; }
	if(sBoard.isValidMove(1, 1, 0, 3)) { return 1; }
	if(sBoard.isValidMove(1, 1, 1, 0)) { return 1; }
	if(sBoard.isValidMove(1, 1, 1, 1)) { return 1; }
	if(sBoard.isValidMove(1, 1, 1, 2)) { return 1; }
	if(sBoard.isValidMove(1, 1, 1, 3)) { return 1; }
	if(sBoard.isValidMove(1, 1, 2, 0)) { return 1; }
	if(sBoard.isValidMove(1, 1, 2, 1)) { return 1; }
	if(sBoard.isValidMove(1, 1, 2, 2)) { return 1; }
	if(sBoard.isValidMove(1, 1, 2, 3)) { return 1; }
	if(sBoard.isValidMove(1, 1, 3, 0)) { return 1; }
	if(sBoard.isValidMove(1, 1, 3, 1)) { return 1; }
	if(sBoard.isValidMove(1, 1, 3, 2)) { return 1; }
	if(sBoard.isValidMove(1, 1, 3, 3)) { return 1; }

	// Testing The White Bishop
	if(sBoard.isValidMove(2, 2, 0, 0)) { return 1; }
	if(sBoard.isValidMove(2, 2, 0, 1)) { return 1; }
	if(sBoard.isValidMove(2, 2, 0, 2)) { return 1; }
	if(sBoard.isValidMove(2, 2, 0, 3)) { return 1; }
	if(sBoard.isValidMove(2, 2, 1, 0)) { return 1; }
	if(sBoard.isValidMove(2, 2, 1, 1)) { return 1; }
	if(sBoard.isValidMove(2, 2, 1, 2)) { return 1; }
	if(sBoard.isValidMove(2, 2, 1, 3) == false) { return 1; }
	if(sBoard.isValidMove(2, 2, 2, 0)) { return 1; }
	if(sBoard.isValidMove(2, 2, 2, 1)) { return 1; }
	if(sBoard.isValidMove(2, 2, 2, 2)) { return 1; }
	if(sBoard.isValidMove(2, 2, 2, 3)) { return 1; }
	if(sBoard.isValidMove(2, 2, 3, 0)) { return 1; }
	if(sBoard.isValidMove(2, 2, 3, 1) == false) { return 1; }
	if(sBoard.isValidMove(2, 2, 3, 2)) { return 1; }
	if(sBoard.isValidMove(2, 2, 3, 3) == false) { return 1; }

	// Testing The White Rook
	if(sBoard.isValidMove(1, 0, 0, 0) == false) { return 1; }
	if(sBoard.isValidMove(1, 0, 0, 1)) { return 1; }
	if(sBoard.isValidMove(1, 0, 0, 2)) { return 1; }
	if(sBoard.isValidMove(1, 0, 0, 3)) { return 1; }
	if(sBoard.isValidMove(1, 0, 1, 0)) { return 1; }
	if(sBoard.isValidMove(1, 0, 1, 1)) { return 1; }
	if(sBoard.isValidMove(1, 0, 1, 2)) { return 1; }
	if(sBoard.isValidMove(1, 0, 1, 3)) { return 1; }
	if(sBoard.isValidMove(1, 0, 2, 0) == false) { return 1; }
	if(sBoard.isValidMove(1, 0, 2, 1)) { return 1; }
	if(sBoard.isValidMove(1, 0, 2, 2)) { return 1; }
	if(sBoard.isValidMove(1, 0, 2, 3)) { return 1; }
	if(sBoard.isValidMove(1, 0, 3, 0) == false) { return 1; }
	if(sBoard.isValidMove(1, 0, 3, 1)) { return 1; }
	if(sBoard.isValidMove(1, 0, 3, 2)) { return 1; }
	if(sBoard.isValidMove(1, 0, 3, 3)) { return 1; }

	return 0;
}

int test_part1_4x4_6() {
	Student::ChessBoard sBoard(4, 4);
	sBoard.createChessPiece(White, Bishop, 3, 0);
	sBoard.createChessPiece(White, Bishop, 3, 3);
	sBoard.createChessPiece(Black, Rook, 2, 2);
	sBoard.createChessPiece(Black, Rook, 0, 2);

	// Testing The First White Bishop
	if(sBoard.isValidMove(3, 0, 0, 0)) { return 1; }
	if(sBoard.isValidMove(3, 0, 0, 1)) { return 1; }
	if(sBoard.isValidMove(3, 0, 0, 2)) { return 1; }
	if(sBoard.isValidMove(3, 0, 0, 3) == false) { return 1; }
	if(sBoard.isValidMove(3, 0, 1, 0)) { return 1; }
	if(sBoard.isValidMove(3, 0, 1, 1)) { return 1; }
	if(sBoard.isValidMove(3, 0, 1, 2) == false) { return 1; }
	if(sBoard.isValidMove(3, 0, 1, 3)) { return 1; }
	if(sBoard.isValidMove(3, 0, 2, 0)) { return 1; }
	if(sBoard.isValidMove(3, 0, 2, 1) == false) { return 1; }
	if(sBoard.isValidMove(3, 0, 2, 2)) { return 1; }
	if(sBoard.isValidMove(3, 0, 2, 3)) { return 1; }
	if(sBoard.isValidMove(3, 0, 3, 0)) { return 1; }
	if(sBoard.isValidMove(3, 0, 3, 1)) { return 1; }
	if(sBoard.isValidMove(3, 0, 3, 2)) { return 1; }
	if(sBoard.isValidMove(3, 0, 3, 3)) { return 1; }

	return 0;
}

int test_part1_4x4_7() {
	Student::ChessBoard sBoard(4, 4);
	sBoard.createChessPiece(Black, Pawn, 0, 0);
	sBoard.createChessPiece(White, Pawn, 2, 1);

	if(sBoard.isValidMove(0, 0, 2, 1)) { return 1; }
	if(sBoard.isValidMove(0, 0, 1, 0) == false) { return 1; }
	if(sBoard.isValidMove(0, 0, 2, 0)) { return 1; }
	if(sBoard.isValidMove(0, 0, 3, 0)) { return 1; }

	if(sBoard.isValidMove(2, 1, 1, 1) == false) { return 1; }
	if(sBoard.isValidMove(2, 1, 0, 1) == false) { return 1; }
	if(sBoard.isValidMove(2, 1, 0, 0)) { return 1; }

	return 0;
}

int test_part2_4x4_1() {
	Student::ChessBoard sBoard(4, 4);
	sBoard.createChessPiece(White, Rook, 3, 2);
	sBoard.createChessPiece(Black, Bishop, 1, 3);
	sBoard.createChessPiece(Black, Rook, 1, 1);
	sBoard.createChessPiece(White, Rook, 2, 3);

	if(sBoard.isPieceUnderThreat(1, 1)) { return 1; }
	if(!sBoard.isPieceUnderThreat(1, 3)) { return 1; }
	if(sBoard.isPieceUnderThreat(2, 3)) { return 1; }
	if(sBoard.isPieceUnderThreat(3, 2)) { return 1; }
	
	if(!sBoard.movePiece(3, 2, 3, 1)) { return 1; }
	if(!sBoard.movePiece(1, 1, 1, 2)) { return 1; }
	if(!sBoard.movePiece(2, 3, 2, 1)) { return 1; }
	if(!sBoard.movePiece(1, 2, 0, 2)) { return 1; }
	if(sBoard.movePiece(0, 0, 2, 3)) { return 1; } // No Piece At Position

	if(sBoard.isPieceUnderThreat(0, 2)) { return 1; }
	if(sBoard.isPieceUnderThreat(1, 3)) { return 1; }
	if(sBoard.isPieceUnderThreat(2, 1)) { return 1; }
	if(!sBoard.isPieceUnderThreat(3, 1)) { return 1; }

	if(!sBoard.movePiece(2, 1, 0, 1)) { return 1; }
	if(!sBoard.movePiece(1, 3, 2, 2)) { return 1; }
	if(!sBoard.movePiece(3, 1, 3, 0)) { return 1; }
	if(!sBoard.movePiece(2, 2, 3, 1)) { return 1; }
	if(sBoard.movePiece(0, 2, 1, 0)) { return 1; } // Bad Move

	if(!sBoard.isPieceUnderThreat(0, 2)) { return 1; }
	if(!sBoard.isPieceUnderThreat(0, 1)) { return 1; }
	if(sBoard.isPieceUnderThreat(3, 0)) { return 1; }
	if(!sBoard.isPieceUnderThreat(3, 1)) { return 1; }

	if(!sBoard.movePiece(3, 0, 3, 1)) { return 1; }
	if(!sBoard.movePiece(0, 2, 2, 2)) { return 1; }
	if(!sBoard.movePiece(3, 1, 3, 0)) { return 1; }
	if(!sBoard.movePiece(2, 2, 1, 2)) { return 1; } 
	if(sBoard.movePiece(1, 1, 2, 3)) { return 1; }

	if(sBoard.isPieceUnderThreat(0, 1)) { return 1; }
	if(sBoard.isPieceUnderThreat(1, 2)) { return 1; }
	if(sBoard.isPieceUnderThreat(3, 0)) { return 1; }

	if(!sBoard.movePiece(3, 0, 0, 0)) { return 1; }

	return 0;
}

int test_part2_4x4_2() {
	Student::ChessBoard sBoard(4, 4);
	sBoard.createChessPiece(White, Rook, 2, 1);
	sBoard.createChessPiece(Black, Rook, 1, 0);
	sBoard.createChessPiece(Black, Bishop, 0, 3);

	if(sBoard.isPieceUnderThreat(0, 0)) { return 1; } // Fake Piece
	if(sBoard.isPieceUnderThreat(0, 3)) { return 1; }
	if(sBoard.isPieceUnderThreat(1, 0)) { return 1; }
	if(sBoard.isPieceUnderThreat(2, 1) == false) { return 1; }

	
	return 0;
}

int test_part3_4x4_1() {
	Student::ChessBoard sBoard(4, 4);
	sBoard.createChessPiece(White, Rook, 3, 2);
	sBoard.createChessPiece(Black, Bishop, 1, 3);
	sBoard.createChessPiece(Black, Rook, 1, 1);
	sBoard.createChessPiece(White, Rook, 2, 3);
	sBoard.createChessPiece(Black, King, 0 ,0);
	sBoard.createChessPiece(White, King, 3 ,0);

	std::cout << sBoard.displayBoard().str() << std::endl;
	if(!sBoard.movePiece(3, 0, 2, 0)) { return 1; }
	std::cout << sBoard.displayBoard().str() << std::endl;
	if(!sBoard.movePiece(1, 3, 0, 2)) { return 1; }
	std::cout << sBoard.displayBoard().str() << std::endl;
	if(!sBoard.movePiece(2, 3, 1, 3)) { return 1; }
	std::cout << sBoard.displayBoard().str() << std::endl;
	if(!sBoard.movePiece(1, 1, 0, 1)) { return 1; }
	std::cout << sBoard.displayBoard().str() << std::endl;
	if(sBoard.movePiece(1, 2, 0, 3)) { return 1; }
	std::cout << sBoard.displayBoard().str() << std::endl;
	if(!sBoard.movePiece(2, 0, 3, 0)) { return 1; }
	std::cout << sBoard.displayBoard().str() << std::endl;
	if(!sBoard.movePiece(0, 1, 2, 1)) { return 1; }
	std::cout << sBoard.displayBoard().str() << std::endl;
	if(!sBoard.movePiece(3, 2, 0, 2)) { return 1; }
	std::cout << sBoard.displayBoard().str() << std::endl;
	if(!sBoard.movePiece(2, 1, 0, 1)) { return 1; }
	std::cout << sBoard.displayBoard().str() << std::endl;
	if(sBoard.movePiece(0, 1, 3, 2)) { return 1; }
	std::cout << sBoard.displayBoard().str() << std::endl;

	return 0;
}

int main() {
	assert(test_part1_4x4_1() == 0);
	assert(test_part1_4x4_2() == 0);
	assert(test_part1_4x4_3() == 0);
	assert(test_part1_4x4_4() == 0);
	assert(test_part1_4x4_5() == 0);
	assert(test_part1_4x4_6() == 0);
	assert(test_part1_4x4_7() == 0);
	assert(test_part2_4x4_1() == 0);
	assert(test_part2_4x4_2() == 0);
	assert(test_part3_4x4_1() == 0);
	return EXIT_SUCCESS;
}
