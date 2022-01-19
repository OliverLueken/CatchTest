#include "catch.hpp"

/*
CHECKED_IF( expr ) { ... }      //executes block if expr is true
CHECKED_ELSE( expr ) { ... }    //executes block if expr is false

CHECK_NOFAIL( expr )    //CHECK that doesn't fail if expr is false
SUCCEED( msg )

STATIC_REQUIRE  //checks at compile time
STATIC_CHECK
CATCH_CONFIG_RUNTIME_STATIC_REQUIRE     //define to deferre check to runtime
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