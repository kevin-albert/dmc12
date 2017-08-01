#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <istream>
#include <locale>
#include <vector>
#include <string>

namespace dmc12 {

struct command {

  command(std::istream &is) {
    std::string verb;
    std::string argv;
    is >> verb >> argv;
    // read everything else into "data"
    data = std::string(std::istreambuf_iterator<char>(is), {});

    if (verb == "get") this->verb = GET;
    else if (verb == "post") this->verb = POST;
    else if (verb == "put") this->verb = PUT;
    else if (verb == "delete") this->verb = DELETE;
    else {
      // invalid verb
      return;
    }

    for (size_t i = 0; i < argv.length();) {
      size_t j = argv.find('/', i);
      if (j == std::string::npos) j = argv.length();
      this->argv.push_back(argv.substr(i, j));
      i = j + 1;
    }
  }

  static constexpr int GET = 1;
  static constexpr int PUT = 2;
  static constexpr int POST = 3;
  static constexpr int DELETE = 4;

  short verb {0};
  std::vector<std::string> argv;
  std::string data;
  operator bool() { return verb; }
};

}


#endif