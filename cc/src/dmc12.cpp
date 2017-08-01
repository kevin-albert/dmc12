#include "dmc12.h"

using namespace dmc12;

engine::engine() {

}

void engine::get_node(const std::string &key, std::function<void(const std::string&)> cb) {
  cb("XXX");
}

void engine::put_node(const std::string &key, const std::string &data, std::function<void(void)> cb) {
    cb();
}