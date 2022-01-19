#include "catch.hpp"

/*
CHECKED_IF( expr ) { ... }      //executes block if expr is true
CHECKED_ELSE( expr ) { ... }    //executes block if expr is false

CHECK_NOFAIL( expr )    //CHECK that doesn't fail if expr is false
SUCCEED( msg )
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
