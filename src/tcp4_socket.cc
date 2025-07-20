#include "tcp4_socket.h"

#include <unistd.h>
#include <string.h>
#include <sstream>
#include "ip4_address.h"


tcp4_socket_t::tcp4_socket_t()
  : fd(-1)
{}

tcp4_socket_t::~tcp4_socket_t()
{
  if (fd >= 0) {
    ::close(fd);
    fd = -1;
  }
}

void tcp4_socket_t::connect(ip4_address_t &to_address)
{
  if (fd >= 0)
    throw "tried to connect an already connected socket";
      
  if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    std::stringstream error_message;
    error_message << "error creating socket: " << strerror(errno);
    throw error_message.str();
  }

  if (::connect(fd, to_address.raw_address(), to_address.raw_address_size()) != 0) {
    std::stringstream error_message;
    error_message << "error connecting: " << strerror(errno);
    throw error_message.str();
  }
}

std::iostream &tcp4_socket_t::stream()
{
  ensure_stream_set_up();
  return *iostream.get();
}


const std::iostream &tcp4_socket_t::stream() const
{
  const_cast<tcp4_socket_t *>(this)->ensure_stream_set_up();
  return *iostream.get();
}


void tcp4_socket_t::ensure_stream_set_up()
{
  if (fd < 0)
    throw("asked for stream from an unconnected socket");

  if (!socket_buffer)
    socket_buffer = std::make_unique<__gnu_cxx::stdio_filebuf<char> >(fd, std::ios::in | std::ios::out);

  if (!iostream)
    iostream = std::make_unique<std::iostream>(socket_buffer.get());
}
