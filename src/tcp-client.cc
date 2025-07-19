// system headers
#include <unistd.h>
#include <signal.h>

// C++ library headers
#include <ext/stdio_filebuf.h>
#include <iostream>
#include <cstring>

// project headers
#include "ip4_address.h"
#include "tcp4_socket.h"


const char DEFAULT_PORT[] = "7000";

int main(int argc, char **argv)
{
  if (argc != 2 && argc != 3) {
    std::cerr << "usage: tcp-client <ip-address> [<port> (default " << DEFAULT_PORT << ")]" << std::endl;
    exit(-1);
  }

  if (signal(SIGPIPE, SIG_IGN) != 0) {
    std::cout << "error setting signal handler: " << strerror(errno) << std::endl;
    exit(-1);
  }

  std::string server_address_string(argv[1]);
  std::string server_port_string(argc == 3 ? argv[2] : DEFAULT_PORT);

  ip4_address_t server_address(server_address_string, server_port_string);
  tcp4_socket_t socket;
  if (socket.connect(server_address) != 0) {
    std::cerr << "error connecting: " << strerror(errno) << std::endl;
    exit(-1);
  }

  __gnu_cxx::stdio_filebuf<char> socket_buffer(socket.fd(), std::ios::in | std::ios::out);
  std::iostream socket_stream(&socket_buffer);

  // at this point, socket stream is a std::iostream suitable for
  // writing to and reading from the connected socket.

  // demo; send an HTP get and show the results.
  socket_stream << "GET / HTTP/1.1\r\n"
                << "Host: localhost\r\n"
                << "\r\n";
  while (!socket_stream.eof()) {
    std::string line;
    std::getline(socket_stream, line);
    std::cout << line << std::endl;
  }
}
