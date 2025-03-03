#include <assert.h>
#include "Chess.h"
#include "ChessBoard.hh"
#include "ChessPiece.hh"

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

    return 0;
}

int main()
{
    assert(test_part1_4x4_1() == 0);
    return EXIT_SUCCESS;
}
