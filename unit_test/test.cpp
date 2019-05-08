// 010-TestCase.cpp

// Let Catch provide main():
#define CATCH_CONFIG_MAIN

#include "catch.hpp"

char skaicius( int a ) {
    return a;
}

TEST_CASE( "skaicius", "[skaicius]" ) {
    REQUIRE( skaicius(1) == 1 ); // gerai
    REQUIRE( skaicius(2) == 2 ); // gerai
    REQUIRE( skaicius(3) == 4 ); // 3 nera lygu 4 turi buti failas
    REQUIRE( skaicius(4) == 4 ); // gerai
}
