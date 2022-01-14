#include "catch.hpp"

auto thisReturnsTrue (){return true ;}
auto thisReturnsFalse(){return false;}

/*
REQUIRE()
CHECK()
REQUIRE_FALSE()
CHECK_FALSE()
*/

TEST_CASE("basics"){
    const auto str = std::string{"string"};
    CHECK( str == "string value" ); //fails

    CHECK( thisReturnsTrue() );

    const auto i = 42;
    REQUIRE( i == 42 );

    CHECK( !thisReturnsFalse() );
    CHECK_FALSE( thisReturnsFalse() );

    const auto a = 1;
    const auto b = 2;
    //CHECK(a == 1 && b == 2); //too complex because &&
    CHECK( a == 1 ); CHECK( b == 2);
    //CHECK( a == 2 || b == 2 ); //too complex because ||
    CHECK( (a == 2 || b == 2) ); //ok with additional parenthesis
}

auto performComputation(){
    return 2.1+1E-5;
}

TEST_CASE("floating_point"){
    REQUIRE( performComputation() == Catch::Detail::Approx( 2.1 ) );
    //allowed approximation can be varied with epsilon, margin and scale

    using namespace Catch::literals;
    REQUIRE( performComputation() == 2.1_a );
}