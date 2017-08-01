#ifndef DMC12_H
#define DMC12_H 

#include <ostream>
#include <string>
#include <functional>
#include "command.hpp"

namespace dmc12 {

using callback = std::function<void()>;

class engine {
public:
    engine();
    void run_command(const command &cmd, std::ostream &out, callback cb);
};

}

#endif