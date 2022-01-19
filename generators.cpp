#include "catch.hpp"

/*
GENERATE( val1, val2... )
//runs test case once for each value
*/


TEST_CASE( "10x10 ints" ){
    auto x = GENERATE( range(1,11) );
    auto y = GENERATE( range(101,111) );

    CHECK( x<y );
}

TEST_CASE("Generators"){
    auto i = GENERATE( as<std::string>(), "a", "b", "c");

    SECTION("one"){
        auto j = GENERATE(range(8,11), 2); //generates j = 8,9,10,2

        CAPTURE(i,j); //as there is no test, capture values here
        SUCCEED();    //and report a success, see report with -s
    }
    SECTION("two"){
        auto j = GENERATE(3.141, 1.379);
        CAPTURE(i,j);
        SUCCEED();
    }
}

/*
i=1, j=-3
i=1, j=-2
i=1, k=4
i=1, k=5
i=1, k=6
i=2, j=-3
i=2, j=-2
i=2, k=4
i=2, k=5
i=2, k=6
*/
TEST_CASE("Generators") {
    auto i = GENERATE(1, 2);
    SECTION("one") {
        auto j = GENERATE(-3, -2);
        REQUIRE(j < i);
    }
    SECTION("two") {
        auto k = GENERATE(4, 5, 6);
        REQUIRE(i != k);
    }
}