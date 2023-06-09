/*!
    \file testAll.cpp
    \brief Calls appropriate unit tests by parsing command line arguments.
    \author Karl Miller
    \date April 2023
*/
#include <string>
#include <iostream>
#include "TemplateTest.cpp"
#include "ConfigTest.cpp"
#include "FilerTest.cpp"

/*!
    Runs the tests.

    Format for CLI args are as follows:

    test { template | all } { noisy | normal | quiet | silent }

    Defaults to normal verbosity and all tests.

    \brief Parses command line arguments to run all or one test.

*/
int main(int argc, char ** argv) {
    filesystem::create_directory("tmp");
    int errors;
    std::string test_choice;
    short verbosity = QUnit::normal;
    if(argc < 2) {
        test_choice = "all";
    }
    if(argc >= 2) {
        test_choice = std::string(argv[1]);
    }
    if(argc >= 3) {
        std::string verbosity_string = std::string(argv[2]);
        if(verbosity_string == "noisy") {
            verbosity = QUnit::noisy;
        } else if(verbosity_string == "quiet") {
            verbosity = QUnit::quiet;
        } else if (verbosity_string == "silent") {
            verbosity = QUnit::silent;
        } else if(verbosity_string == "normal") {
            verbosity = QUnit::normal;
        } else {
            cout << "\nCouldn't understand verbosity level of '" << verbosity_string << "'. Valid values are 'noisy', 'quiet' 'normal', and 'silent'. Using default 'normal'." ;
        }
    }
    if(test_choice == "template") {
        errors = TemplateTest(std::cerr, verbosity).run();
    } else if(test_choice == "all") {
        errors = TemplateTest(std::cerr, verbosity).run() + ConfigTest(std::cerr, verbosity).run() + FilerTest(std::cerr, verbosity).run();
    } else if(test_choice == "config") {
        errors = ConfigTest(std::cerr, verbosity).run();
    } else if(test_choice == "filer") {
        errors = FilerTest(std::cerr, verbosity).run();
    } else {
        cout << "'" << test_choice << "' is not a valid test option. Try 'all'. \n";
    }
    filesystem::remove_all("tmp");
    return errors;
}