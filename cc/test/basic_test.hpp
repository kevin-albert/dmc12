#ifndef BASIC_TEST_HPP
#define BASIC_TEST_HPP

#include "fructose/fructose.h"
struct basic_test : public fructose::test_base<basic_test> {
    basic_test() {
        add_test("sanity check", &basic_test::sanity_check);
    }

    void sanity_check(const std::string &name) {
        fructose_assert(true);
    }
};

#endif