#include "catch.hpp"
#include <vector>

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

TEST_CASE( "Testing a vector", "[vector]" ){
    std::vector<int> v{1, 3};
    SECTION( "Contains (element)" ){
        CHECK_THAT( v, VectorContains(1) );
        CHECK_THAT( v, VectorContains(2) ); //fails
    }
    std::vector<int> v2{1};
    std::vector<int> empty{};
    SECTION( "Contains (vector)" ){
        CHECK_THAT( v, Contains(v2) );
        v2.push_back(3); //now v == v2
        CHECK_THAT( v, Contains(v2) );
        v2.push_back(2); //now v < v2
        CHECK_THAT( v, Contains(v2) ); //fails

        CHECK_THAT( v, Contains(empty) );
        CHECK_THAT( empty, Contains(empty) );
    }
}