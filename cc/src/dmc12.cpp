#include <iostream>
#include "dmc12.h"

using namespace dmc12;

engine::engine() {

}

void engine::run_command(const command &cmd, std::ostream &out, callback cb) {
  std::cout << "verb:   " << cmd.verb << "\n"
            << "argv:   ";
  for (auto arg: cmd.argv) std::cout << arg << " ";
  std::cout << "\ndata:   " << cmd.data << "\n";
  out << "Hello\r\n";
  cb();
}