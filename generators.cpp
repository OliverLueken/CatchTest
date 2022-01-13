#include "catch.hpp"

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