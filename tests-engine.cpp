#include "catch.hpp"
#include "Engine.h"

TEST_CASE("perf", "[engine]")
{
    Engine engine;
    int moves = engine.perft(engine.getCurrentPosition(), 1);
    const int DEPTH_ONE = 20;
    REQUIRE(moves == DEPTH_ONE);
}

TEST_CASE("en_passant", "[rules]")
{
    Engine engine("rnbqkbnr/pp1p1ppp/8/2pP4/4p3/8/PPP1PPPP/RNBQKBNR w KQkq c6 0 1");
    REQUIRE(engine.userMove("P", "d5", "c6"));
}

TEST_CASE("king_movement", "[rules]")
{
    Engine engine;
}