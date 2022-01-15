#include "catch.hpp"

#include <vector>
#include <string>

/*
AAA or A³ test pattern
Assemble-Activate-Assert or Arrange-Act-Assert
GIVEN( something )
WHEN( something )
THEN( something )

AND_GIVEN( something )
AND_WHEN( something )
AND_THEN( something )
*/

static auto eatCucumbers(int start, int eat) -> int {return start-eat;}

SCENARIO("Eating cucumbers", "[givenWhenThen]" ){
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


/*
Scenario : vector can be sized and resized
  Given  : An empty vector
  Then   : The size and capacity start at 0

Scenario : vector can be sized and resized
  Given  : An empty vector
  When   : push_back() is called
  Then   : The size changes
*/
SCENARIO( "vector can be sized and resized", "[givenWhenThen]" ) {
    GIVEN( "An empty vector" ) {
        auto v = std::vector<std::string>{};

        // Validate assumption of the GIVEN clause
        THEN( "The size and capacity start at 0" ) {
            REQUIRE( v.size() == 0 );
            REQUIRE( v.capacity() == 0 );
        }

        // Validate one use case for the GIVEN object
        WHEN( "push_back() is called" ) {
            v.push_back("hullo");

            THEN( "The size changes" ) {
                REQUIRE( v.size() == 1 );
                REQUIRE( v.capacity() >= 1 );
            }
        }
    }
}