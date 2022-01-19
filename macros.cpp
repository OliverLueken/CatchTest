#include "catch.hpp"

#include <string>

/*
CHECKED_IF( expr ) { ... }      //executes block if expr is true
CHECKED_ELSE( expr ) { ... }    //executes block if expr is false

CHECK_NOFAIL( expr )    //CHECK that doesn't fail if expr is false
SUCCEED( msg )

STATIC_REQUIRE  //checks at compile time
STATIC_CHECK
CATCH_CONFIG_RUNTIME_STATIC_REQUIRE     //define to deferre check to runtime

METHOD_AS_TEST_CASE( memberFunctionPointer, description, tags )     //calls object method as test

REGISTER_TEST_CASE( function, description, tags )   //calls function void() as test
*/


TEST_CASE( "CHECKED", "[checked][macro]"){
    int a = 1;
    int b = 2;
    CHECKED_IF( a == b ) {
        // This block is entered when a == b
        SUCCEED( a << " is equal to " << b );
    } CHECKED_ELSE ( a == b ) {
        // This block is entered when a != b
        SUCCEED( a << " is not equal to " << b);
    }
}



TEST_CASE( "CHECK_NOFAIL", "[macro]"){
    CHECK_NOFAIL( 1==2 );
    SUCCEED("is ok");
}


TEST_CASE("STATIC_REQUIRE showcase", "[traits][macro]") {
    STATIC_REQUIRE( std::is_void<void>::value );
    STATIC_REQUIRE_FALSE( std::is_void<int>::value );
}

/*
STATIC_CHECK not declared
TEST_CASE("STATIC_CHECK showcase", "[traits][macro]") {
    STATIC_CHECK( std::is_void<void>::value );
    STATIC_CHECK_FALSE( std::is_void<int>::value );
}
*/



class TestClass {
    std::string s;

public:
    TestClass()
        :s( "hello" )
    {}

    void testCase() {
        REQUIRE( s == "hello" );
    }
};


METHOD_AS_TEST_CASE( TestClass::testCase, "Use class's method as a test case", "[class][macro]" )



void testCase() {
    std::string s{"hello"};
    REQUIRE( s == "hello" );
}
REGISTER_TEST_CASE( testCase, "Use function as a test case", "[macro]" )
