#ifndef IP4_ADDRESS_H_MARK
#define IP4_ADDRESS_H_MARK 1

#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>

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

#endif
