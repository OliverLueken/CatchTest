#include "catch.hpp"

/*
GENERATE( val1, val2... )
//runs test case once for each value
*/


TEST_CASE( "10x10 ints", "[generators]" ){
    auto x = GENERATE( range(1,11) );
    auto y = GENERATE( range(101,111) );

    CHECK( x<y );
}

TEST_CASE("Generators", "[generators]"){
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
TEST_CASE("Generators2", "[generators]") {
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



/*
runs first section once
the second section twice
*/
TEST_CASE("GENERATE between SECTIONs", "[generators]") {
    SECTION("first") { REQUIRE(true); }
    auto _ = GENERATE(1, 2);
    SECTION("second") { REQUIRE(true); }
}



/*
reports 14 assertions
A(1),           C(5),
        B(3),   C(6),
        B(4),   C(5),
                C(6),
A(2),           C(5),
        B(3),   C(6),
        B(4),   C(5),
                C(6),

*/
TEST_CASE("Complex mix of sections and generates", "[generators]") {
    auto i = GENERATE(1, 2);
    SECTION("A") {
        SUCCEED("A(" + std::to_string(i) + ')' );
    }
    auto j = GENERATE(3, 4);
    SECTION("B") {
        SUCCEED("B(" + std::to_string(j) + ')' );
    }
    auto k = GENERATE(5, 6);
    SUCCEED("C(" + std::to_string(j) + ')' );
}