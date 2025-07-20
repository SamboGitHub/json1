#include "ip4_address.h"

#include <unistd.h>
#include <cstring>
#include <iostream>
#include <sstream>


ip4_address_t::ip4_address_t(const std::string &ip_address_string,
                             const std::string &port_string)
{
  memset(&raw_ip4_address, 0, sizeof(raw_ip4_address));

  raw_ip4_address.sin_family = AF_INET;

  if (inet_pton(AF_INET, ip_address_string.c_str(), &raw_ip4_address.sin_addr) != 1) {
    std::stringstream error_message;
    error_message << "invalid address: " << ip_address_string << ": " << strerror(errno);
    throw error_message.str();
  }

  long port = atol(port_string.c_str());
  if (port == 0 || port > 65535) {
    std::stringstream error_message;
    error_message << "bad port: " << port << ": " << strerror(errno);
    throw error_message.str();
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
