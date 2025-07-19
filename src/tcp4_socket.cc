#include "tcp4_socket.h"

#include <unistd.h>
#include "ip4_address.h"


tcp4_socket_t::tcp4_socket_t()
  : socket_buffer(0),
    iostream(0),
    fd(-1)
{}

tcp4_socket_t::~tcp4_socket_t()
{
  if (iostream) {
    delete iostream;
    iostream = 0;
  }
  if (socket_buffer) {
    delete socket_buffer;
    socket_buffer = 0;
  }
  if (fd >= 0) {
    ::close(fd);
    fd = -1;
  }
}

void tcp4_socket_t::connect(ip4_address_t &to_address)
{
  if (fd >= 0)
    throw "tried to connect an already connected socket";
      
  fd = socket(AF_INET, SOCK_STREAM, 0);

  if (fd < 0)
    throw "error creating socket";

  if (::connect(fd, to_address.raw_address(), to_address.raw_address_size()) != 0)
    throw "error connecting";
}

std::iostream &tcp4_socket_t::stream()
{
  if (fd < 0)
    throw("asked for stream from an unconnected socket");

  if (!socket_buffer)
    socket_buffer = new __gnu_cxx::stdio_filebuf<char>(fd, std::ios::in | std::ios::out);

  if (!iostream)
    iostream = new std::iostream(socket_buffer);

  return *iostream;
}
