#include "catch.hpp"
#include "Board.h"

TEST_CASE("enPassant", "[rules]")
{
    Board board("rnbqkbnr/pp1p1ppp/8/2pP4/4p3/8/PPP1PPPP/RNBQKBNR w KQkq c6 0 1");
    REQUIRE(board.isValidMove(35, 42));
}

TEST_CASE("castling", "[rules]")
{
}

TEST_CASE("king movement", "[rules]")
{
}