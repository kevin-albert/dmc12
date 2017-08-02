
#include <iostream>
#include <memory>
#include <utility>
#include <thread>
#include "asio/streambuf.hpp"
#include "asio/ts/buffer.hpp"
#include "asio/ts/internet.hpp"

#include "tcp_server.hpp"
using asio::ip::tcp;

namespace dmc12 {
class session: public std::enable_shared_from_this<session> {
public:
  session(dmc12::engine &engine, tcp::socket socket): 
    engine(engine), 
    socket(std::move(socket)) {}

  void start() {
    std::cout << "thread " << std::this_thread::get_id() << " start()\n";
    read_loop();
  }

private:
  void read_loop() {
    auto self(shared_from_this());
    asio::async_read_until(socket, input, "\r\n",
        [this, self](std::error_code ec, std::size_t length) {
          std::cout << "thread " << std::this_thread::get_id() << " read\n";
          if (ec) {
            std::cerr << "error reading from socket - " << ec.message() << "\n";
            socket.close();
          }
          else {
            std::istream is(&input); 
            std::ostream os(&output);

            dmc12::command cmd(is);
            if (cmd) {
              engine.run_command(cmd, os, [this, self]() {
                respond();
              });
            } else {
              os << "error invalid command\r\n";
              socket.close();
            }
          }
        });
  }

  void respond() {
    auto self(shared_from_this());
    asio::async_write(socket, output,
        [this, self](std::error_code ec, std::size_t /*length*/) {
          if (!ec) { read_loop(); }
        });
  }

  dmc12::engine &engine;
  tcp::socket socket;
  asio::streambuf input;
  asio::streambuf output;
};

tcp_server::tcp_server(dmc12::engine &engine, asio::io_context& io_context, short port): 
    engine(engine),
    acceptor(io_context, tcp::endpoint(tcp::v4(), port)),
    socket(io_context) {
  do_accept();
}

void tcp_server::do_accept() {
  acceptor.async_accept(socket,
      [this](std::error_code ec) {
        if (!ec) {
          std::make_shared<session>(engine, std::move(socket))->start();
        }

        do_accept();
      });
}
}