/*!
    \file ConfigTest.cpp
    \brief Provides tests for Config. See Config.h.
    \author Karl Miller
    \date April 2023
*/
#include "QUnit.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>
#include "Config.h"

using namespace std;
namespace fs = std::filesystem;

const string tmp_conf = "./tmp/testconf.json";
const string tmp_tdir = "./tmp/tmpl";

/*! \brief Tests the Config class. */
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
            QUNIT_IS_EQUAL(res, "No info for cpp2.");
            res = c.getInfo("unknown");
            QUNIT_IS_EQUAL(res, "No info for unknown.");

            remove(tmp_conf.c_str());
        }

        void set() {
            fs::path testpath = fs::path(tmp_conf);
            Config c = Config(testpath);

            fs::create_directory(tmp_tdir);

            c.setTemplateDir(tmp_tdir);

            fs::path result = c.getTemplateDir();
            QUNIT_IS_EQUAL(result.string(), fs::canonical(tmp_tdir).string());

            fs::remove(tmp_tdir);
            remove(tmp_conf.c_str());

        }

        void write() {
            fs::path testpath = fs::path(tmp_conf);
            Config c = Config(testpath);

            c.setInfo("cpp", "cpp proj");
            c.setInfo("y","ynot");
            fs::create_directory(tmp_tdir);
            c.setTemplateDir(tmp_tdir);
            c.writeConfig();

            Config c2 = Config(testpath);
            c2.readConfig();
            string res = c2.getInfo("cpp");
            QUNIT_IS_EQUAL(res, "cpp proj");
            res = c2.getInfo("y");
            QUNIT_IS_EQUAL(res, "ynot");

            fs::path td = c2.getTemplateDir();
            QUNIT_IS_EQUAL(fs::canonical(td.string()), fs::canonical(tmp_tdir));

            fs::remove(tmp_tdir);
            fs::remove(tmp_conf);

        }

    public:
        ConfigTest(std::ostream & out, int verbose_level = QUnit::verbose) : qunit(out, verbose_level) {}

        int run() {
            init();
            read();
            set();
            write();
            return qunit.errors();
        }
};

