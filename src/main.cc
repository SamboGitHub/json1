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

// vars used in the code
std::string keystring = "";
std::string valstring = "";
json result_array = json::array();


// Start to define the class structure
std::string ParmType = "";
std::string id = "";
std::string name = "";
std::string group = "";
std::string desc = "";
int v_type = 0;
int c_type = 0;
int d_flags = 0;
float value = 0;
float std_value = 0;
int do_not_save = 0;        //Bool
int non_controllable = 0;   //Int
float lower = 0;            //Int and Float
float upper = 0;            //Int and Float
float step = 0;             //Float
std::array<string,20> value_names = {{"a", "b"}};   //Enum



printf("Begin First Parsing\n");
    json data = json::parse(f);

printf("Begin Iterating Parse 1 \n");
for (json::iterator it = data.begin(); it != data.end(); ++it)
{
    printf("Inside Parse 1 For Loop \n");

    keystring = it.key();
    std::cout << keystring << " - " ;

    if(keystring.find("result") == 0)
    {
        result_array = it.value();
    }
}

// Loop throught the array and parse into values. We get back a string (parameter type) and an object (the deets)
 std::cout << "IDs" << "\n";
 for (json::iterator it = result_array.begin(); it != result_array.end(); ++it) {
   // skip anything that isn't an object

   if (it->is_string()){
     
   std::cout << "; Type: " << (*it)
             << "\n";
    }

   if (it->is_object()){
        

            if((*it)["value"].is_number()){
                value = ((*it)["value"].get<nlohmann::json::number_float_t>());

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


// // Original working code below: 

//  // Loop throught the array and parse into values. We get back a string (parameter type) and an object (the deets)
//  std::cout << "IDs" << "\n";
//  for (json::iterator it = result_array.begin(); it != result_array.end(); ++it) {
//    // skip anything that isn't an object

//    if (it->is_string()){
     
//    std::cout << "; Type: " << (*it)
//              << "\n";
//     }

//    if (it->is_object()){
        

//             if((*it)["value"].is_number()){
//                 value = ((*it)["value"].get<nlohmann::json::number_float_t>());

//             }    
//         std::cout << ";      group: " << (*it)["Parameter"]["group"] << "\n"
//                 << "name: " << (*it)["Parameter"]["name"] << "\n"
//                 << ";         id: " << (*it)["Parameter"]["id"] << "\n"
//                 << ";      value: " << (*it)["value"]    << "\n"
//                 << ";      value2: " << value << "\n"
//                 << ";  std_value: " << (*it)["Parameter"]["std_value"] << "\n"
//                 << ";      upper: " << (*it)["Parameter"]["upper"] << "\n"
//                 << ";      lower: " << (*it)["Parameter"]["lower"] << "\n"
//                 << ";value_names: " << (*it)["Parameter"]["value_names"] << "\n"
//                 << "\n";
//     }
//     value = 0;
//  }
// printf("End Parsing\n");
// }

// // Loop throught the array and parse into values. We get back a string (parameter type) and an object (the deets)
//  std::cout << "IDs" << "\n";
//  for (json::iterator it = result_array.begin(); it != result_array.end(); ++it) {
//    // skip anything that isn't an object

//    if (it->is_string()){
     
//    std::cout << "; Type: " << (*it)
//              << "\n";
//     }

//    if (it->is_object()){
        

//             if((*it)["value"].is_number()){
//                 value = ((*it)["value"].get<nlohmann::json::number_float_t>());

//             }    
//         std::cout << ";      group: " << (*it)["Parameter"]["group"] << "\n"
//                 << "name: " << (*it)["Parameter"]["name"] << "\n"
//                 << ";         id: " << (*it)["Parameter"]["id"] << "\n"
//                 << ";      value: " << (*it)["value"]    << "\n"
//                 << ";      value2: " << value << "\n"
//                 << ";  std_value: " << (*it)["Parameter"]["std_value"] << "\n"
//                 << ";      upper: " << (*it)["Parameter"]["upper"] << "\n"
//                 << ";      lower: " << (*it)["Parameter"]["lower"] << "\n"
//                 << ";value_names: " << (*it)["Parameter"]["value_names"] << "\n"
//                 << "\n";
//     }
//     value = 0;
//  }
// printf("End Parsing\n");
// }






// 1) pipe json into a string and dump it
//   string s = data.dump();
//   cout << "serialization with pretty printing: " << data.dump(4) << endl;

// 2) special iterator member functions for objects
// for (json::iterator it = data.begin(); it != data.end(); ++it) {
//   std::cout << it.key() << " : " << it.value() << "\n";
// }

// std::cout << "Parse the Array \n";
// //   dumps all
// //    std::cout << it.key() << " : " << it.value() << "\n";
// // std::cout << result_array.dump() << "\n \n \n"; 
// // std::cout << result_array[1] << "\n"; 
// // 


// //  DUMP BELOW
// // the (4) makes it pretty-print.
// //  std::cout << result_array.dump(4) << "\n";
