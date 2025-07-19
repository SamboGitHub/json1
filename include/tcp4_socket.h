#ifndef TCP4_SOCKET_H_MARK
#define TCP4_SOCKET_H_MARK 1

class ip4_address_t;

class tcp4_socket_t
{
public:
  tcp4_socket_t();

  int connect(ip4_address_t &to_address);
  int fd();

private:
  int raw_fd;
};

#endif
