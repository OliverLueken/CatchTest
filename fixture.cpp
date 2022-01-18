#include "catch.hpp"

#include <string>

/*
TEST_CASE_METHOD( fixture, description, tags )
TEMPLATE_TEST_CASE_METHOD( fixture, description, tags, type1...)
TEMPLATE_PRODUCT_TEST_CASE_METHOD( fixture, description, tags, (templatedClass1...), (templateType1...))
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

