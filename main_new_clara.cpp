#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

//command line options via ./a.out -?


int main( int argc, char* argv[] ){
    Catch::Session session;

    int number = 0;
    using namespace Catch::clara;
    auto cli = session.cli() | Opt( number, "a number" ) //adding custom command line option -m
        ["-m"]["--number"]
        ("some custom number");
    session.cli( cli );

    auto exitCode = session.applyCommandLine( argc, argv );
    if( exitCode != 0 ){
        return exitCode;
    }

    std::cout << "The number is: " << number << '\n';

    return session.run();
}