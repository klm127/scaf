
#include "QUnit.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>
#include "Filer.h"

using namespace std;
namespace fs = std::filesystem;

const string flr_tmp_tdir = "./tmp/tmpl2";
const string flr_tmp_tdir2 = "./tmp/tmpl2/tt";
const string flr_tmp_fl = "./tmp/tmpl2/t.x";
const string flr_tmp_fl2 = "./tmp/tmpl2/tt/t2.x";
const string flr_tmp_odir = "./tmp/tout";

class FilerTest {
    QUnit::UnitTest qunit;

    private: 
        // Validates that Config will generate a file if one doesn't exist.
        void isEmpty() {
            fs::create_directory(flr_tmp_tdir);
            bool result = Filer::isEmpty(flr_tmp_tdir);
            QUNIT_IS_EQUAL(result, true);
            fs::create_directory(flr_tmp_tdir + "/.git");
            result = Filer::isEmpty(flr_tmp_tdir);
            QUNIT_IS_EQUAL(result, true);
            ofstream file;
            file.open(flr_tmp_fl, ios::out);
            file.close();
            result = Filer::isEmpty(flr_tmp_tdir);
            QUNIT_IS_EQUAL(result, false);
            fs::remove_all(flr_tmp_tdir);
            
        }

        void copyRecursive() {
            fs::create_directory(flr_tmp_tdir);
            fs::create_directory(flr_tmp_tdir2);
            fs::create_directory(flr_tmp_odir);
            ofstream file;
            file.open(flr_tmp_fl, ios::out);
            file.close();
            file.open(flr_tmp_fl2, ios::out);
            file.close();

            int count = Filer::copyRecursive(flr_tmp_tdir, flr_tmp_odir);
            QUNIT_IS_EQUAL(count, 2);

            fs::remove_all(flr_tmp_tdir);
            
        }

    public:
        FilerTest(std::ostream & out, int verbose_level = QUnit::verbose) : qunit(out, verbose_level) {}

        int run() {
            isEmpty();
            copyRecursive();
            return qunit.errors();
        }
};

