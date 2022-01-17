#include "catch.hpp"

#include <vector>
#include <string>

/*
TEMPLATE_TEST_CASE( description, tags, types...)
TEMPLATE_PRODUCT_TEST_CASE( description, tags, (templatedClass1, templatedClass2...), (templateType1, templateType2...))
*/


/*
executes test case with
TestType = int,
TestType = std::string,
TestType = std::tuple<int, float>
*/
TEMPLATE_TEST_CASE( "vectors can be sized and resized", "[vector][template]", int, std::string, (std::tuple<int,float>) ) {

    std::vector<TestType> v( 5 );

    REQUIRE( v.size() == 5 );
    REQUIRE( v.capacity() >= 5 );

    SECTION( "resizing bigger changes size and capacity" ) {
        v.resize( 10 );

        REQUIRE( v.size() == 10 );
        REQUIRE( v.capacity() >= 10 );
    }
    SECTION( "resizing smaller changes size but not capacity" ) {
        v.resize( 0 );

        REQUIRE( v.size() == 0 );
        REQUIRE( v.capacity() >= 5 );

        SECTION( "We can use the 'swap trick' to reset the capacity" ) {
            std::vector<TestType> empty;
            empty.swap( v );

            REQUIRE( v.capacity() == 0 );
        }
    }
    SECTION( "reserving smaller does not change size or capacity" ) {
        v.reserve( 0 );

        REQUIRE( v.size() == 5 );
        REQUIRE( v.capacity() >= 5 );
    }
}

template< typename T>
struct Foo {
    size_t size() {
        return 0;
    }
};

/*
executes test case with
TestType = std::vector<int>,
TestType = std::vector<float>,
TestType = Foo<int>,
TestType = Foo<float>
*/
TEMPLATE_PRODUCT_TEST_CASE("A Template product test case", "[template][product]", (std::vector, Foo), (int, float)) {
    TestType x;
    REQUIRE(x.size() == 0);
}


/*
executes test case with
TestType = std::tuple<int>
TestType = std::tuple<int, double>
TestType = std::tuple<int, double, float>
*/
TEMPLATE_PRODUCT_TEST_CASE("Product with differing arities", "[template][product]", std::tuple, (int, (int, double), (int, double, float))) {
    TestType x;
    REQUIRE(std::tuple_size<TestType>::value >= 1);
}