
#include "QUnit.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>
#include "Config.h"

using namespace std;
namespace fs = std::filesystem;

const string tmp_conf = "./tests/testconf.json";
const string tmp_tdir = "./tests/tmpl";

class ConfigTest {
    QUnit::UnitTest qunit;

    private: 
        // Validates that Config will generate a file if one doesn't exist.
        void init() {
            fs::path testpath = fs::path(tmp_conf);
            Config c = Config(testpath);
            fs::path result = c.getPath();
            QUNIT_IS_EQUAL(result.string(), tmp_conf);

            ifstream file;
            file.open(tmp_conf, ios::in);
            string line;
            getline(file, line);
            file.close();
            QUNIT_IS_EQUAL(line, "{}");
            remove(tmp_conf.c_str());
        }

        // Tests Config's reading functionality.
        void read() {
            fs::path testpath = fs::path(tmp_conf);
            Config c = Config(testpath);

            ofstream file;
            file.open(tmp_conf, ios::out);
            file << "{\"templateDir\":\"./tests\",";
            file << "\"infos\":{";
            file << "\"js1\":\"someinfo\",";
            file << "\"cpp\":\"someinfo2\",";
            file << "\"cpp2\":\"\"}}";
            file.close();

            c.readConfig();

            string res = c.getInfo("js1");
            QUNIT_IS_EQUAL(res, "someinfo");
            res = c.getInfo("cpp");
            QUNIT_IS_EQUAL(res, "someinfo2");
            res = c.getInfo("cpp2");
            QUNIT_IS_EQUAL(res, "");
            res = c.getInfo("unknown");
            QUNIT_IS_EQUAL(res, "");

            remove(tmp_conf.c_str());
        }

    public:
        ConfigTest(std::ostream & out, int verbose_level = QUnit::verbose) : qunit(out, verbose_level) {}

        int run() {
            init();
            read();
            return qunit.errors();
        }
};

