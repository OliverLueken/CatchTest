#include "catch.hpp"
#include <vector>

/*
REQUIRE_THAT( lhs, matcher expression)
  CHECK_THAT( lhs, matcher expression)

//string matchers
StartsWith( string, CaseSEnsitive )
EndsWith( string, CaseSEnsitive )
ContainsSubstring( string, CaseSEnsitive )
Equals( string, CaseSEnsitive )
Matches( string, CaseSEnsitive )

//Floating point matchers
WithinAbs( double target, double margin )
WithinULP( floatingPoint target, uint64_t maxUlpDiff )
WithinRel( floatingPoint target, floatingPoint eps )

Predicate<T>( callable pred, std::string description )

REQUIRE_THROWS_MATCHES( expr, ExceptionType, Matcher )

//Range matchers
IsEmpty()
SizeIs( size_t target_size )
SizeIs( Matcher size_matcher )
Contains( T&& target_element, Comparator = std::equal_to<>{} )
Contains( Matcher element_matcher )

matchers can be composed with &&, || and !
*/

TEST_CASE("test case name"){
    REQUIRE(6*9 == 42); //fails
}

inline const char* testStringForMatching(){
    return "this string contains 'abc' as a substring";
}
using namespace Catch::Matchers;
TEST_CASE("String matchers", "[matchers]"){
    REQUIRE_THAT( testStringForMatching(), Contains( "string" ) ); //require aborts test on failure
    CHECK_THAT  ( testStringForMatching(), Contains( "abc"    ) ); //check carries on even on failure

    CHECK_THAT( testStringForMatching(), StartsWith( "this"      ) );
    CHECK_THAT( testStringForMatching(), EndsWith  ( "substring" ) );
}



TEST_CASE( "Matchers can be composed with both && and ||",
           "[matchers][operators][operator||][operator&&]"){
    CHECK_THAT( testStringForMatching(),
        ( Contains("string") || Contains("different") ) && Contains("substring") );
}



TEST_CASE( "Testing what elements a vector contains", "[vector]" ){
    std::vector<int> v{1, 3};
    SECTION( "Contains (element)" ){
        CHECK_THAT( v, VectorContains(1) );
        CHECK_THAT( v, VectorContains(2) ); //fails
    }

    std::vector<int> v2{1};
    std::vector<int> empty{};
    SECTION( "Contains (vector)" ){
        CHECK_THAT( v, Contains(v2) ); //check if v contains every element of v2
        v2.push_back(3); //now v == v2
        CHECK_THAT( v, Contains(v2) );
        v2.push_back(2); //now v.size() < v2.size()
        CHECK_THAT( v, Contains(v2) ); //fails

        CHECK_THAT( v, Contains(empty) );
        CHECK_THAT( empty, Contains(empty) );
    }
}


TEST_CASE( "Predicate matcher test", "[matchers][predicate]" ){
    REQUIRE_THAT("Hello olleH",
        Predicate<std::string>(
            [] (std::string const& str) -> bool { return str.front() == str.back(); },
            "First and last character should be equal"
        )
    );
}