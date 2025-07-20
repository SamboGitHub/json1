// C++ library headers
#include <iostream>
#include <stdio.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <cassert>
#include <iomanip>

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
    // pulled from main to test banks
    printf("Begin Set Up\n");
    using json = nlohmann::json;
   // vars used in the code
    std::string keystring = "";
    std::string valstring = "";

    json::iterator parm_it;
    json parm_result_array = json::array();
    json::iterator parm_array_it;

    json::iterator bank_it;
    json bank_result_array = json::array();
    json::iterator bank_array_it;
    json bank_preset_result_array = json::array();
    json::iterator bank_preset_array_it;
    json bank_data;
        // Start to define the class structure
    std::string bank_name = "";
    int bank_mutable = 0;
    std::string bank_type = "";
    std::array<std::string, 20> bank_presets = {{""}}; // Enum
    int bank_preset_index = 0;

  std::string server_address_string(argv[1]);
  std::string server_port_string(argc == 3 ? argv[2] : DEFAULT_PORT);

  try {
    ip4_address_t server_address(server_address_string, server_port_string);
    tcp4_socket_t socket;
    socket.connect(server_address);

    // at this point, socket.stream() is a std::iostream suitable for
    // writing to and reading from the connected socket.

    // // demo; send an HTTP get and show the results.
    // socket.stream() << "GET / HTTP/1.1\r\n"
    //                 << "Host: localhost\r\n"
    //                 << "\r\n";

    // demo; send an HTTP get and show the results.

std::string command = "{\"jsonrpc\": \"2.0\",\"id\": \"1\",\"method\": \"banks\",\"params\": []}";

    socket.stream() << command << "\r\n";
                    // << "Host: localhost\r\n"
                    // << "\r\n";
  
    while (!socket.stream().eof()) {
      std::string line;
      std::getline(socket.stream(), line);
      std::cout << line << std::endl;

        printf("Begin First Bank Parsing\n");
        bank_data = json::parse(line);

        printf("Begin Iterating Parse 1 \n");
        for (bank_it = bank_data.begin(); bank_it != bank_data.end(); ++bank_it)
        {
            keystring = bank_it.key();
            std::cout << keystring << " - ";

            if (keystring.find("result") == 0)
            {
                bank_result_array = bank_it.value();
            }
        }

        std::cout << "Bank Array Dump: " << (bank_result_array.dump()) << "\n";
        printf("\n");

        // Loop throught the array and parse into values. We only get back an object (the deets)
        std::cout << "banks" << "\n";
        for (bank_array_it = bank_result_array.begin(); bank_array_it != bank_result_array.end(); ++bank_array_it)
        {
            // skip anything that isn't an object

            if (bank_array_it->is_string())
            {
                // Do nothing
            }

            if (bank_array_it->is_object())
            {

                bank_name = "";
                bank_mutable = 0;
                bank_type = "";
                bank_presets = {{""}}; // Enum//     // clear everything
                bank_preset_index = 0;

                //     // std::cout << bank_presets << "\n";
                if ((*bank_array_it)["name"].is_string())
                {
                    bank_name = ((*bank_array_it)["name"].get<nlohmann::json::string_t>());
                }
                if ((*bank_array_it)["mutable"].is_number())
                {
                    bank_mutable = ((*bank_array_it)["mutable"].get<nlohmann::json::number_integer_t>());
                }
                if ((*bank_array_it)["type"].is_string())
                {
                    bank_type = ((*bank_array_it)["type"].get<nlohmann::json::string_t>());
                }
                // dump everything but the presets array
                std::cout << "Bank Name: " << bank_name << "\n";
                std::cout << "  Mutable: " << bank_mutable << "\n";
                std::cout << "     Type: " << bank_type << "\n";
                // passing and dump the presets array
                if ((*bank_array_it)["presets"].is_array())
                {
                    bank_preset_result_array = ((*bank_array_it)["presets"].get<nlohmann::json::array_t>());
                    for (bank_preset_array_it = bank_preset_result_array.begin(); bank_preset_array_it != bank_preset_result_array.end(); ++bank_preset_array_it)
                    {
                        bank_presets[bank_preset_index] = (*bank_preset_array_it);
                        std::cout << "           " << bank_preset_index << ": " << bank_presets[bank_preset_index] << "\n";
                        bank_preset_index++;
                    }
                }
            }
        }




















    }
  }
  catch (const char *error_message) {
    std::cerr << error_message << std::endl;
    exit(-1);
  }
}
