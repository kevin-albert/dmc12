#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include "asio/ts/internet.hpp"
#include "dmc12.h"

namespace dmc12 {

class tcp_server {
public:
  tcp_server(dmc12::engine &engine, asio::io_context& io_context, short port);

private:
  void do_accept();

  dmc12::engine &engine;  
  asio::ip::tcp::acceptor acceptor;
  asio::ip::tcp::socket socket;
};

}

#endif