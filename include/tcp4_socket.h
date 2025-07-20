#ifndef TCP4_SOCKET_H_MARK
#define TCP4_SOCKET_H_MARK 1

#include <ext/stdio_filebuf.h>
#include <iosfwd>
#include <memory>

class ip4_address_t;

class tcp4_socket_t
{
public:
  tcp4_socket_t();
  ~tcp4_socket_t();

  void connect(ip4_address_t &to_address);
  std::iostream &stream();

private:
  std::unique_ptr<__gnu_cxx::stdio_filebuf<char> > socket_buffer;
  std::unique_ptr<std::iostream> iostream;
  int fd;
};

#endif
