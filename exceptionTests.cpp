#include "catch.hpp"
#include <string>
#include <sstream>

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