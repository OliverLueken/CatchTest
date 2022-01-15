#include "catch.hpp"

/*
INFO( message )
is scoped

UNSCOPED_INFO( message )
tied to the first following assertion

WARN( message )
always reported

FAIL( message )
reports message and fails the test case

FAIL_CHECK( message )
As FAIL but does not abort the test

CAPTURE( expression1, expression2, ... )
quick variable/expression logger
CAPTURE( theAnswer )
"theAnswer := 42"
*/


/*
prints:
Test case start
The number is 1
*/
TEST_CASE("LoggerFoo") {
    INFO("Test case start");
    for (int i = 0; i < 2; ++i) {
        INFO("The number is " << i);
        CHECK(i == 0);
    }
}


/*
prints:
Test case start
*/
TEST_CASE("LoggerBar") {
    INFO("Test case start");
    for (int i = 0; i < 2; ++i) {
        INFO("The number is " << i);
        CHECK(i == i);
    }
    CHECK(false);
}


void print_some_info() {
    UNSCOPED_INFO("Info from helper");
}

/*
prints:
Info from helper
The number is 0
The number is 1
*/
TEST_CASE("UnscopedLoggerBaz") {
    print_some_info();
    for (int i = 0; i < 2; ++i) {
        UNSCOPED_INFO("The number is " << i);
    }
    CHECK(false);
}

/*
prints:
First info
First unscoped info

First info
Second info
Second unscoped info
*/
TEST_CASE("UnscopedLoggerQux") {
    INFO("First info");
    UNSCOPED_INFO("First unscoped info");
    CHECK(false);

    INFO("Second info");
    UNSCOPED_INFO("Second unscoped info");
    CHECK(false);
}