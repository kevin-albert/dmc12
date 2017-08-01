#include "tdd.h"

std::vector <test_case> tdd::tests;
std::vector <test_result> tdd::results;

#include "command.hpp"

int main(void) {
    tdd::run();
}