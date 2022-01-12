#include "catch.hpp"

TEST_CASE("test case name"){
    REQUIRE(6*9 == 42); //fails
}

inline const char* testStringForMatching(){
    return "this string contains 'abc' as a substring";
}
using namespace Catch::Matchers;
TEST_CASE("String matchers", "[matchers]"){
    REQUIRE_THAT( testStringForMatching(), Contains( "string" ) );
    CHECK_THAT  ( testStringForMatching(), Contains( "abc"    ) );

    CHECK_THAT(   testStringForMatching(), StartsWith( "this"      ) );
    CHECK_THAT(   testStringForMatching(), EndsWith  ( "substring" ) );
}

TEST_CASE( "Matchers can be composed with both && and ||",
           "[matchers][operators][operator||][operator&&]"){
    CHECK_THAT( testStringForMatching(),
        ( Contains("string") || Contains("different") ) && Contains("substring") );
}