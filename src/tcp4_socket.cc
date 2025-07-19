#include "tcp4_socket.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "ip4_address.h"


tcp4_socket_t::tcp4_socket_t()
{
  raw_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (raw_fd < 0)
    throw "error creating socket";
}

int tcp4_socket_t::connect(ip4_address_t &to_address)
{
  return ::connect(fd(), to_address.raw_address(), to_address.raw_address_size());
}

int tcp4_socket_t::fd()
{
  return raw_fd;
}
