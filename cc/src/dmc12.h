#ifndef DMC12_H
#define DMC12_H 

#include <string>
#include <functional>

#include "asio/streambuf.hpp"

namespace dmc12 {

class engine {
public:
    engine();
    void get_node(const std::string &key, asio::streambuf &out, std::function<void()> cb);
    void put_node(const std::string &key, const std::string &data, std::function<void(void)> cb);
};

}

#endif