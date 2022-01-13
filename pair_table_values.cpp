#include "catch.hpp"

TEST_CASE( "strlen", "[approvals]" ){
    auto [test_input, expected] = GENERATE( values<std::pair<std::string_view, size_t>>({
        {"one", 3},
        {"two", 3},
        {"three", 5},
        {"four", 4},
    }));
    REQUIRE( test_input.size() == expected );
}

//using table generator
TEST_CASE( "strlen2", "[approvals]" ){
    auto [test_input, expected] = GENERATE( table<std::string, size_t>({
        {"one", 3},
        {"two", 3},
        {"three", 5},
        {"four", 4},
    }));
    REQUIRE( test_input.size() == expected );
}

//another alternative
struct Data{ std::string str; size_t len;};

TEST_CASE( "strlen3" ){
    auto data = GENERATE( values<Data>({
        {"one", 3},
        {"two", 3},
        {"three", 5},
        {"four", 4},
    }));
    REQUIRE( data.str.size() == data.len );
}