//
// async_tcp_echo_server.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2017 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// #include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include "asio/streambuf.hpp"
#include "asio/ts/buffer.hpp"
#include "asio/ts/internet.hpp"

using asio::ip::tcp;

class session: public std::enable_shared_from_this<session> {
public:
  session(tcp::socket socket): socket(std::move(socket)) {}

  void start() {
    do_read();
  }

private:
  void do_read() {
    auto self(shared_from_this());
    asio::async_read_until(socket, data, "\r\n",
        [this, self](std::error_code ec, std::size_t length) {
          if (ec) {
            std::cerr << "error reading from socket - ";
                      // << ec.category() << ": " << ec.message();
            socket.close();
          }
          else {
            respond(length);
          }
        });
  }

  void respond(std::size_t length) {
    auto self(shared_from_this());
    asio::async_write(socket, asio::buffer("Hello\r\n", 7),
        [this, self](std::error_code ec, std::size_t /*length*/) {
          // if (!ec) {
          //   do_read();
          // }
          socket.close();
        });
  }

  tcp::socket socket;
  asio::streambuf data;
};

class server {
public:
  server(asio::io_context& io_context, short port): 
      acceptor(io_context, tcp::endpoint(tcp::v4(), port)),
      socket(io_context) {
    do_accept();
  }

private:
  void do_accept() {
    acceptor.async_accept(socket,
        [this](std::error_code ec) {
          if (!ec) {
            std::make_shared<session>(std::move(socket))->start();
          }

          do_accept();
        });
  }

  tcp::acceptor acceptor;
  tcp::socket socket;
};

int main(int argc, char* argv[]) {
  try {
    if (argc != 2) {
      std::cerr << "Usage: async_tcp_echo_server <port>\n";
      return 1;
    }

    asio::io_context io_context;
    server s(io_context, std::atoi(argv[1]));
    io_context.run();
  }
  catch (std::exception& e) {
    std::cerr << "Exception: " << e.what() << "\n";
    return 1;
  }

  return 0;
}