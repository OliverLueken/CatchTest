#include "catch.hpp"

/*
https://github.com/catchorg/Catch2/blob/devel/docs/generators.md#top

GENERATE( val1, val2... )
//runs test case once for each value

Generators
    SingleValueGenerator<T>
    FixedValuesGenerator<T>

    FilterGenerator<T, Predicate>       //filters out elements from a generator for which a predicate returns false
    TakeGenerator<T>                    //test first n elements from a generator
    RepeatGenerator<T>                  //repeats output from a generator n times
    MapGenerator<T, U, Func>            //applies func on elements from a generator
    ChunkGenerator<T>                   //chunks of n elements from a generator (in a vector)

    RandomIntegerGenerator<Integral>    //random integrals from a range
    RandomFloatGenerator<Float>         //random floats from a range
    RangeGenerator<T>(first, last)      //all values inside a range [first, last)
    IteratorGenerator<T>                //copies and returns values from an iterator range

Helper functions
    value(T&&)                                                  for SingleValueGenerator<T>
    values(std::initializer_list<T>)                            for FixedValuesGenerator<T>
    table<Ts...>(std::initializer_list<std::tuple<Ts...>>)      for FixedValuesGenerator<std::tuple<Ts...>>
    filter(predicate, GeneratorWrapper<T>&&)                    for FilterGenerator<T, Predicate>
    take(count, GeneratorWrapper<T>&&)                          for TakeGenerator<T>
    repeat(repeats, GeneratorWrapper<T>&&)                      for RepeatGenerator<T>
    map(func, GeneratorWrapper<T>&&)                            for MapGenerator<T, U, Func> (map U to T, deduced from Func)
    map<T>(func, GeneratorWrapper<U>&&)                         for MapGenerator<T, U, Func> (map U to T)
    chunk(chunk-size, GeneratorWrapper<T>&&)                    for ChunkGenerator<T>
    random(IntegerOrFloat a, IntegerOrFloat b)                  for RandomIntegerGenerator or RandomFloatGenerator
    range(Arithemtic start, Arithmetic end)                     for RangeGenerator<Arithmetic> with a step size of 1
    range(Arithmetic start, Arithmetic end, Arithmetic step)    for RangeGenerator<Arithmetic> with a custom step size
    from_range(InputIterator from, InputIterator to)            for IteratorGenerator<T>
    from_range(Container const&)                                for IteratorGenerator<T>
*/


TEST_CASE( "10x10 ints", "[generators]" ){
    auto x = GENERATE( range(1,11) );
    auto y = GENERATE( range(101,111) );

    CHECK( x<y );
}

TEST_CASE("Generators", "[generators]"){
    auto i = GENERATE( as<std::string>(), "a", "b", "c");

    SECTION("one"){
        auto j = GENERATE(range(8,11), 2); //generates j = 8,9,10,2

        CAPTURE(i,j); //as there is no test, capture values here
        SUCCEED();    //and report a success, see report with -s
    }
    SECTION("two"){
        auto j = GENERATE(3.141, 1.379);
        CAPTURE(i,j);
        SUCCEED();
    }
}

/*
i=1, j=-3
i=1, j=-2
i=1, k=4
i=1, k=5
i=1, k=6
i=2, j=-3
i=2, j=-2
i=2, k=4
i=2, k=5
i=2, k=6
*/
TEST_CASE("Generators2", "[generators]") {
    auto i = GENERATE(1, 2);
    SECTION("one") {
        auto j = GENERATE(-3, -2);
        REQUIRE(j < i);
    }
    SECTION("two") {
        auto k = GENERATE(4, 5, 6);
        REQUIRE(i != k);
    }
}



/*
runs first section once
the second section twice
*/
TEST_CASE("GENERATE between SECTIONs", "[generators]") {
    SECTION("first") { REQUIRE(true); }
    auto _ = GENERATE(1, 2);
    SECTION("second") { REQUIRE(true); }
}



/*
reports 14 assertions
A(1),           C(5),
        B(3),   C(6),
        B(4),   C(5),
                C(6),
A(2),           C(5),
        B(3),   C(6),
        B(4),   C(5),
                C(6),

*/
TEST_CASE("Complex mix of sections and generates", "[generators]") {
    auto i = GENERATE(1, 2);
    SECTION("A") {
        SUCCEED("A(" + std::to_string(i) + ')' );
    }
    auto j = GENERATE(3, 4);
    SECTION("B") {
        SUCCEED("B(" + std::to_string(j) + ')' );
    }
    auto k = GENERATE(5, 6);
    SUCCEED("C(" + std::to_string(j) + ')' );
}


/*
example with take, filter, random
*/
TEST_CASE("Generating random ints", "[example][generator]") {
    SECTION("Deducing functions") {
        auto i = GENERATE(take(100, filter([](int i) { return i % 2 == 1; }, random(-100, 100))));
        REQUIRE(i > -100);
        REQUIRE(i < 100);
        REQUIRE(i % 2 == 1);
    }
}