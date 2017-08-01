#ifndef TEST_COMMAND_HPP
#define TEST_COMMAND_HPP

#include <sstream>
#include <string>

#include "tdd.h"
#include "../src/command.hpp"

unit_test(parse_simple_command, cb) {
  std::stringstream str("get node/x");  
  dmc12::command cmd(str);
  assert_true(cmd, cb);
  assert_eq(cmd.verb, dmc12::command::GET, cb);
  assert_eq(cmd.argv[0], "node", cb);
  assert_eq(cmd.argv[1], "x", cb);
  cb(ok());
}

#endif