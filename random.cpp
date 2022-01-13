#include "catch.hpp"

static auto square(int i) -> int {return i*i;}

TEST_CASE( "Random numbers in a range", "[.][approvals]" ){
    auto x = GENERATE( random( -10000, 10000 ) );
    CAPTURE(x);
    REQUIRE( square(x) >= 0 );
}