#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#include "matchers.cpp" //providing tests by including files

auto thisReturnsTrue (){return true ;}
auto thisReturnsFalse(){return false;}

//providing tests directly
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

int main(){
    Catch::Session session;
    return session.run();
}


