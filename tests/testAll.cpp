#include <string>
#include <iostream>
#include "TemplateTest.cpp"
#include "ConfigTest.cpp"

/*!
    Runs the tests.

    Format for CLI args are as follows:

    test { template | all } { noisy | normal | quiet | silent }

    Defaults to normal verbosity and all tests.

*/
int main(int argc, char ** argv) {
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
        errors = TemplateTest(std::cerr, verbosity).run() + ConfigTest(std::cerr, verbosity).run();
    } else if(test_choice == "config") {
        errors = ConfigTest(std::cerr, verbosity).run();
    }else {
        cout << "'" << test_choice << "' is not a valid test option. Try 'all'. \n";
    }
    return errors;
}