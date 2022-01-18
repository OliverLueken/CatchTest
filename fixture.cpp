#include "catch.hpp"

#include <string>

/*
TEST_CASE_METHOD( fixture, description, tags )

TEMPLATE_TEST_CASE_METHOD( fixture, description, tags, type1...)
TEMPLATE_PRODUCT_TEST_CASE_METHOD( fixture, description, tags, (templatedClass1...), (templateType1...))

TEMPLATE_TEST_CASE_METHOD_SIG( fixture, description , tags, signature, type1, type2... )
TEMPLATE_PRODUCT_TEST_CASE_METHOD_SIG( fixture, description , tags, signature, (templatedClass1...), (templateType1...) )
*/

class DBConnection{
public:
    static DBConnection createConnection(std::string){ return DBConnection{}; }
    bool executeSQL(std::string, int, std::string name){
        if(name.empty()) throw "Empty name value exception";
        return true;
    }
};

class UniqueTestsFixture {
private:
    static int uniqueID;
protected:
    DBConnection conn;
public:
    UniqueTestsFixture() : conn(DBConnection::createConnection("myDB")) {}
protected:
    int getID() {
        return ++uniqueID;
    }
};

int UniqueTestsFixture::uniqueID = 0;

TEST_CASE_METHOD(UniqueTestsFixture, "Create Employee/No Name", "[create][fixture]") {
    REQUIRE_THROWS(conn.executeSQL("INSERT INTO employee (id, name) VALUES (?, ?)", getID(), ""));
}
TEST_CASE_METHOD(UniqueTestsFixture, "Create Employee/Normal", "[create][fixture]") {
    REQUIRE(conn.executeSQL("INSERT INTO employee (id, name) VALUES (?, ?)", getID(), "Joe Bloggs"));
}




template< typename T >
struct Template_Fixture {
    Template_Fixture(): m_a(1) {}

    T m_a;
};

/*
executes test with
TestType = int,
TestType = float,
TestType = double,
*/
TEMPLATE_TEST_CASE_METHOD(Template_Fixture,"A TEMPLATE_TEST_CASE_METHOD based test run that succeeds", "[class][template][fixture]",
        int, float, double) {
            REQUIRE( Template_Fixture<TestType>::m_a == 1 );
}

template<typename T>
struct Template_Template_Fixture {
    Template_Template_Fixture() {}

    T m_a;
};

template<typename T>
struct Foo_class {
    size_t size() {
        return 0;
    }
};

/*
executes test with
TestType = Foo_class<int>
TestType = std::vector<int>
*/
TEMPLATE_PRODUCT_TEST_CASE_METHOD(Template_Template_Fixture, "A TEMPLATE_PRODUCT_TEST_CASE_METHOD based test succeeds", "[class][template][fixture]",
        (Foo_class, std::vector), int) {
            REQUIRE( Template_Template_Fixture<TestType>::m_a.size() == 0 );
}



template <int V>
struct Nttp_Fixture{
    int value = V;
};

TEMPLATE_TEST_CASE_METHOD_SIG(Nttp_Fixture, "A TEMPLATE_TEST_CASE_METHOD_SIG based test run that succeeds", "[class][template][nttp][fixture]",
        ((int V), V), 1, 3, 6) {
            REQUIRE(Nttp_Fixture<V>::value > 0);
}

template<typename T>
struct Template_Fixture_2 {
    Template_Fixture_2() {}

    T m_a;
};

template< typename T, size_t V>
struct Template_Foo_2 {
    size_t size() { return V; }
};

TEMPLATE_PRODUCT_TEST_CASE_METHOD_SIG(Template_Fixture_2, "A TEMPLATE_PRODUCT_TEST_CASE_METHOD_SIG based test run that succeeds", "[class][template][product][nttp][fixture]",
        ((typename T, size_t S), T, S),(std::array, Template_Foo_2), ((int,2), (float,6)))
{
    REQUIRE(Template_Fixture_2<TestType>{}.m_a.size() >= 2);
}