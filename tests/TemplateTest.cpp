/*!
    \file TemplateTest.cpp
    \brief Provides tests for Template. See Template.h.
    \author Karl Miller
    \date April 2023
    \note TemplateTest is deprecated! Template is not currently used in the program!
    \deprecated 
*/
#include "QUnit.hpp"
#include <iostream>
#include "Template.h"

using namespace std;

class TemplateTest {
    QUnit::UnitTest qunit;

private: 
    void init() {
        Template t = Template();
        string result = t.getAlias();
        QUNIT_IS_EQUAL(result, "");
        result = t.getInfo();
        QUNIT_IS_EQUAL(result, "No information provided for .");
        result = t.getPath();
        QUNIT_IS_EQUAL(result, "");
        t = Template("C:/global/t1");
        result = t.getAlias();
        QUNIT_IS_EQUAL(result, "t1");
        result = t.getPath();
        QUNIT_IS_EQUAL(result, "C:/global/t1");
        result = t.getInfo();
        QUNIT_IS_EQUAL(result, "No information provided for t1.");
        t= Template("C:/global/t1", "test1", "some info");
        result = t.getAlias();
        QUNIT_IS_EQUAL(result, "test1");
        result = t.getPath();
        QUNIT_IS_EQUAL(result, "C:/global/t1");
        result = t.getInfo();
        QUNIT_IS_EQUAL(result, "some info");
    }

public:
    TemplateTest(std::ostream & out, int verbose_level = QUnit::verbose) : qunit(out, verbose_level) {}

    int run() {
        init();
        return qunit.errors();
    }
};

