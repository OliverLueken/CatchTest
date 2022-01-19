#include "catch.hpp"

/*
pick desired reporter
command option:
-r xml
--reporter xml

picking multiple reporters
--reporter console::- --reporter JUnit::result-junit.xml
*/

//writing own reporter
// #include <catch2/reporters/catch_reporter_streaming_base.hpp>
// #include <catch2/catch_test_case_info.hpp>
// #include <catch2/reporters/catch_reporter_registrars.hpp>

// #include <iostream>
//
// class PartialReporter : public Catch::StreamingReporterBase {
// public:
//     using StreamingReporterBase::StreamingReporterBase;
//
//     static std::string getDescription() {
//         return "Reporter for testing TestCasePartialStarting/Ended events";
//     }
//
//     void testCasePartialStarting(Catch::TestCaseInfo const& testInfo,
//                                  uint64_t partNumber) override {
//         std::cout << "TestCaseStartingPartial: " << testInfo.name << '#' << partNumber << '\n';
//     }
//
//     void testCasePartialEnded(Catch::TestCaseStats const& testCaseStats,
//                               uint64_t partNumber) override {
//         std::cout << "TestCasePartialEnded: " << testCaseStats.testInfo->name << '#' << partNumber << '\n';
//     }
// };
//
//
// CATCH_REGISTER_REPORTER("partial", PartialReporter)