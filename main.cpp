/*
catch2 repository
https://github.com/catchorg/Catch2
and introduction
https://www.youtube.com/watch?v=Ob5_XZrFQH0
by Phil Nash, cppcon 2018
Reference:
https://github.com/catchorg/Catch2/blob/devel/docs/Readme.md#top
*/

#define CATCH_CONFIG_MAIN //writes main for us

#include "catch.hpp"

#include "matchers.cpp"
#include "exceptionTests.cpp"
#include "generators.cpp"
#include "pair_table_values.cpp"
#include "random.cpp"
#include "given_when_then.cpp"
#include "basics.cpp"
#include "logger.cpp"