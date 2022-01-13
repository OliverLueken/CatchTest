#include "catch.hpp"

static auto eatCucumbers(int start, int eat) -> int {return start-eat;}

SCENARIO("Eating cucumbers", "[approvals]"){
    auto [start, eat, left] = GENERATE( table<int,int,int>({
        {12, 5, 7 },
        {20, 5, 15 }
    }));

    GIVEN( "there are " << start << " cucumbers")
    WHEN( "I eat " << eat << " cucumbers")
    THEN( "I should have " << left << " cucumbers left"){
        REQUIRE( eatCucumbers(start, eat) == left );
    }
}