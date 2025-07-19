// system headers
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// C++ library headers
#include <ext/stdio_filebuf.h>
#include <iostream>
#include <cstring>

class ip4_address_t
{
public:
  ip4_address_t(const std::string &ip_address_string,
                const std::string &port_string);

  struct sockaddr *raw_address();
  size_t raw_address_size();

private:
  struct sockaddr_in raw_ip4_address;
};

ip4_address_t::ip4_address_t(const std::string &ip_address_string,
                             const std::string &port_string)
{
  memset(&raw_ip4_address, 0, sizeof(raw_ip4_address));

  raw_ip4_address.sin_family = AF_INET;

  if (inet_pton(AF_INET, ip_address_string.c_str(), &raw_ip4_address.sin_addr) != 1) {
    std::cerr << "invalid address: " << ip_address_string << std::endl;
    exit(-1);
  }

  long port = atol(port_string.c_str());
  if (port == 0 || port > 65535) {
    std::cerr << "invalid port: " << port_string << std::endl;
    exit(-1);
  }
  raw_ip4_address.sin_port = htons((short) port);
}

struct sockaddr *ip4_address_t::raw_address()
{
  return (struct sockaddr *) &raw_ip4_address;
}

size_t ip4_address_t::raw_address_size()
{
  return sizeof(raw_ip4_address);
}


class tcp4_socket_t
{
public:
  tcp4_socket_t();

  int connect(ip4_address_t &to_address);
  int fd();

private:
  int raw_fd;
};

tcp4_socket_t::tcp4_socket_t()
{
  raw_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (raw_fd < 0) {
    std::cerr << "error creating socket: " << strerror(errno) << std::endl;
    exit(-1);
  }
}

int tcp4_socket_t::connect(ip4_address_t &to_address)
{
  return ::connect(fd(), to_address.raw_address(), to_address.raw_address_size());
}

int tcp4_socket_t::fd()
{
  return raw_fd;
}


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

  // demonstrate; send an HTP get and show the results.
  socket_stream << "GET / HTTP/1.1\r\n"
                << "Host: localhost\r\n"
                << "\r\n";
  while (!socket_stream.eof()) {
    std::string line;
    std::getline(socket_stream, line);
    std::cout << line << std::endl;
  }
}
