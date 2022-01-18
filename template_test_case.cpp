#include "catch.hpp"

#include <vector>
#include <string>

/*
TEMPLATE_TEST_CASE( description, tags, types...)
TEMPLATE_PRODUCT_TEST_CASE( description, tags, (templatedClass1, templatedClass2...), (templateType1, templateType2...))
TEMPLATE_LIST_TEST_CASE( description, tags, type list ) //allows reuse of the type list
TEMPLATE_TEST_CASE_SIG( description , tags, signature, type1, type2... )
TEMPLATE_PRODUCT_TEST_CASE_SIG( description , tags, signature, (templatedClass1...), (templateType1...) )
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


/*
executes test case with
TestType = int
TestType = char
TestType = float
*/
using MyTypes = std::tuple<int, char, float>;
TEMPLATE_LIST_TEST_CASE("Template test case with test types specified inside std::tuple", "[template][list]", MyTypes)
{
    REQUIRE(sizeof(TestType) > 0);
}

/*
executes test case with
T = int,                    V = 5
T = float,                  V = 4
T = std::string,            V = 15
T = std::tuple<int, flaot>, V = 6
*/
TEMPLATE_TEST_CASE_SIG("TemplateTestSig: arrays can be created from NTTP arguments", "[vector][template][nttp]",
  ((typename T, int V), T, V), (int,5), (float,4), (std::string,15), ((std::tuple<int, float>), 6)) {

    std::array<T, V> v;
    REQUIRE(v.size() > 1);
}



template<typename T, size_t S>
struct Bar {
    size_t size() { return S; }
};


/*
executes test case with
TestType = std::array<int, 9>
TestType = std::array<float, 42>
TestType = Bar<int, 9>
TestType = Bar<float, 42>
*/
TEMPLATE_PRODUCT_TEST_CASE_SIG("A Template product test case with array signature", "[template][product][nttp]",
        ((typename T, size_t S), T, S), (std::array, Bar), ((int, 9), (float, 42))) {
    TestType x;
    REQUIRE(x.size() > 0);
}