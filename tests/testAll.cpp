#include "TemplateTest.cpp"
#include <string>

/*!
    Runs the tests.

    Format for CLI args are as follows:

    test { template | all } { noisy | normal | quiet | silent }

    Defaults to verbosity normal.

*/
int main(int argc, char ** argv) {
    int errors;
    std::string test_choice;
    short verbosity = QUnit::normal;
    if(argc < 2) {
        test_choice = "All";
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
        }
    }
    if(test_choice == "template") {
        errors = TemplateTest(std::cerr, verbosity).run();
    } else if(test_choice == "all") {
        errors = TemplateTest(std::cerr, verbosity).run();
    }
    return errors;
}