#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <istream>
#include <locale>
#include <vector>
#include <string>

/*
select a node:
  V['x']  -> { (id='x', name='Kevin') }

select an edge:
  E['x', 'y']

select edges from 'x':
  E['x', _] -> { (from='x', to='z', ...), (from='x', to='w')}

select edges to 'y':
  E[_, 'y'] -> { (from='z', to='y', ...), (...), ... }

select some nodes
  V[name = "Kevin" or value >= 123]
  V[name = "Kevin"] | V[value >= 123] 
  V[name = "Eric" and color="green"]
  V[name = "Eric" ] & V[color="green"]

select edges of nodes
  E[ V[name = "Kevin"] ] & { (from='x', to='y') } -> { }

select path from 'x' to 'y'
  path(V['x'], V['y'])

select edges in path from 'x' to 'y' with capacity >= 2
  path(V['x'], V['y']) & E[capacity >= 2]
*/

namespace dmc12 {

struct command {

  command(std::istream &is) {
    std::string argv;
    is >> verb >> argv;
    // read everything else into "data"
    data = std::string(std::istreambuf_iterator<char>(is), {});

    for (size_t i = 0; i < argv.length();) {
      size_t j = argv.find('/', i);
      if (j == std::string::npos) j = argv.length();
      this->argv.push_back(argv.substr(i, j));
      i = j + 1;
    }
  }

  static constexpr int get = 1;
  static constexpr int set = 2;
  static constexpr int del = 3;

  std::string verb;
  std::vector<std::string> argv;
  std::string data;
  operator bool() { return verb; }
};

}


#endif