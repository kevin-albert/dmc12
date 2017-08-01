#include <iostream>
#include <thread>
#include <vector>
#include "asio/io_context.hpp"

#include "dmc12.h"
#include "tcp_server.h"


int main(int argc, char **argv) {
  try {

    short port = 8000;
    if (argc == 2) port = std::atoi(argv[1]);
    
    dmc12::engine engine;
    asio::io_context io_context;

    dmc12::tcp_server server(engine, io_context, port);

    std::vector<std::thread> threads;
    for (int i = 0; i < 4; ++i) {
      threads.push_back(std::thread([&io_context]() { io_context.run(); }));
    }
    for (auto &t: threads)
      t.join();
  }
  catch (std::exception& e) {
    std::cerr << "Exception: " << e.what() << "\n";
    return 1;
  }

  return 0;
}