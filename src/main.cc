#include <stdio.h>
#include "inky.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <cassert>
#include <iomanip>


using namespace std;

int main(int argc, char**argv)
{
    printf("Begin Set Up\n");
    using json = nlohmann::json;

// ...
    printf("Begin Reading File\n");
std::ifstream f("thefile.json");
std::string keystring = "";
std::string valstring = "";

double value = 0.0;

json result_array = json::array();

    printf("Begin First Parsing\n");
json data = json::parse(f);

// 1) pipe json into a string and dump it
//   string s = data.dump();
//   cout << "serialization with pretty printing: " << data.dump(4) << endl;

// 2) special iterator member functions for objects
// for (json::iterator it = data.begin(); it != data.end(); ++it) {
//   std::cout << it.key() << " : " << it.value() << "\n";
// }

// 3) or via find and an iterator
    printf("Begin Iterating Parse 1 \n");
for (json::iterator it = data.begin(); it != data.end(); ++it)
{
    printf("Inside Parse 1 For Loop \n");

    keystring = it.key();
    std::cout << keystring << " - " ;

    // result_array = it.key();
    // std::cout << result_array << " - " ;


    if(keystring.find("result") == 0)
    {
        // this works
        // std::cout << it.key();
        // // std::cout << " : ";
        // std::cout << it.value();
        // std::cout << "\n";
        // valstring = it.value();
        result_array = it.value();
    }

}


std::cout << "Parse the Array \n";
//   dumps all
//    std::cout << it.key() << " : " << it.value() << "\n";
// std::cout << result_array.dump() << "\n \n \n"; 
// std::cout << result_array[1] << "\n"; 
// 


//  DUMP BELOW
// the (4) makes it pretty-print.
//  std::cout << result_array.dump(4) << "\n";

 // dump the ids
 std::cout << "IDs" << "\n";
 for (json::iterator it = result_array.begin(); it != result_array.end(); ++it) {
   // skip anything that isn't an object

   if (it->is_string()){
     
   std::cout << "; Type: " << (*it)
             << "\n";
    }

   if (it->is_object()){
        
            std::cout << "Set Numeric Value" << "\n";
            if((*it)["value"].is_number()){
                std::cout << "Set Numeric Value" << "\n";
                value = ((*it)["value"].get<nlohmann::json::number_float_t>());
                std::cout << "Numeric Value Set" << "\n";
            }    
        std::cout << ";      group: " << (*it)["Parameter"]["group"] << "\n"
                << "name: " << (*it)["Parameter"]["name"] << "\n"
                << ";         id: " << (*it)["Parameter"]["id"] << "\n"
                << ";      value: " << (*it)["value"]    << "\n"
                << ";      value2: " << value << "\n"
                << ";  std_value: " << (*it)["Parameter"]["std_value"] << "\n"
                << ";      upper: " << (*it)["Parameter"]["upper"] << "\n"
                << ";      lower: " << (*it)["Parameter"]["lower"] << "\n"
                << ";value_names: " << (*it)["Parameter"]["value_names"] << "\n"
                << "\n";
    }
    value = 0;
 }

printf("End Parsing\n");
}
