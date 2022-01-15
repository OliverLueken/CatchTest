#include "catch.hpp"
#include <string>
#include <sstream>

/*
//Expects no exceptions thrown
REQUIRE_NOTHROW(expression)
  CHECK_NOTHROW(expression)


//Expects exceptions to be thrown
REQUIRE_THROWS(expression)
  CHECK_THROWS(expression)


//Expects exceptions of the specified type to be thrown
REQUIRE_THROWS_AS(expression, exception_type)
  CHECK_THROWS_AS(expression, exception_type)


//Expects exceptions that, converted to a string, matches the string or string matcher
REQUIRE_THROWS_WITH(expression, string or string matcher)
  CHECK_THROWS_WITH(expression, string or string matcher)
*/

#include <stdexcept>

auto notThrowing(){}
auto throwing(){ throw "exception"; }

TEST_CASE("not throwing"){
    REQUIRE_NOTHROW( notThrowing() );
    CHECK_NOTHROW( notThrowing() );
    CHECK_NOTHROW( throwing() ); //fails
}


TEST_CASE("throwing"){
    REQUIRE_THROWS( throwing() );
    CHECK_THROWS( throwing() );
    CHECK_THROWS( notThrowing() ); //fails

    using int_pair = std::pair<int,int>;
    CHECK_THROWS_AS( int_pair(1, 3), std::invalid_argument);

    REQUIRE_THROWS_WITH( throwing(), "exception");
}















//My own exception
class SpecialException : public std::exception{
public:
    int i;
    explicit SpecialException(int _i) : i{_i} {}
};

//Building own exception matcher for my exception
class ExceptionMatcher : public Catch::MatcherBase<SpecialException>{
    int m_expected;
public:
    explicit ExceptionMatcher(int i) : m_expected(i){}
    bool match(const SpecialException& se) const override{
        return se.i == m_expected;
    }

    std::string describe() const override{
        std::ostringstream ss;
        ss << "special exception has value of " << m_expected;
        return ss.str();
    }
};

auto throws(int i){
    throw SpecialException(i);
}

TEST_CASE( "Exception matchers that succeed", "[matchers][exceptions][!throws]" ){
    CHECK_THROWS_MATCHES  (throws(1), SpecialException, ExceptionMatcher{1});
    REQUIRE_THROWS_MATCHES(throws(2), SpecialException, ExceptionMatcher{2});
}