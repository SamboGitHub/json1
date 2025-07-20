// // C++ library headers
// #include <iostream>

// // project headers
// #include "ip4_address.h"
// #include "tcp4_socket.h"


// const char DEFAULT_PORT[] = "7000";

// int main(int argc, char **argv)
// {
//   if (argc != 2 && argc != 3) {
//     std::cerr << "usage: tcp-client <ip-address> [<port> (default " << DEFAULT_PORT << ")]" << std::endl;
//     exit(-1);
//   }

//   std::string server_address_string(argv[1]);
//   std::string server_port_string(argc == 3 ? argv[2] : DEFAULT_PORT);

//   try {
//     ip4_address_t server_address(server_address_string, server_port_string);
//     tcp4_socket_t socket;
//     socket.connect(server_address);

//     // at this point, socket.stream() is a std::iostream suitable for
//     // writing to and reading from the connected socket.

//     // // demo; send an HTTP get and show the results.
//     // socket.stream() << "GET / HTTP/1.1\r\n"
//     //                 << "Host: localhost\r\n"
//     //                 << "\r\n";

//     // demo; send an HTTP get and show the results.

// std::string command = "{\"jsonrpc\": \"2.0\",\"id\": \"1\",\"method\": \"banks\",\"params\": []}";

//     socket.stream() << command << "\r\n";
//                     // << "Host: localhost\r\n"
//                     // << "\r\n";
  
//     while (!socket.stream().eof()) {
//       std::string line;
//       std::getline(socket.stream(), line);
//       std::cout << line << std::endl;
//     }
//   }
//   catch (const char *error_message) {
//     std::cerr << error_message << std::endl;
//     exit(-1);
//   }
// }
