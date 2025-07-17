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
std::ifstream f("Params.json");

// vars used in the code
std::string keystring = "";
std::string valstring = "";
json result_array = json::array();


// Start to define the class structure
std::string parmtype = "";
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
   
    parmtype = (*it);
    // std::cout << "; parmtype: " << (*it)
    // std::cout << "; parmtype: " << parmtype
            //  << "\n";
    it++;
    }

   if (it->is_object()){

    // clear everything
    id = "";
    name = "";
    group = "";
    desc = "";
    v_type = 0;
    c_type = 0;
    d_flags = 0;
    value = 0;
    std_value = 0;
    do_not_save = 0;        //Bool
    non_controllable = 0;   //Int
    lower = 0;            //Int and Float
    upper = 0;            //Int and Float
    step = 0;             //Float

    // load if valid values
    id = "";
    name = "";
    group = "";
    desc = "";

    if((*it)["Parameter"]["id"].is_string()){
        id = ((*it)["Parameter"]["id"].get<nlohmann::json::string_t>());
    } 
    if((*it)["Parameter"]["name"].is_string()){
        name = ((*it)["Parameter"]["name"].get<nlohmann::json::string_t>());
    } 
        if((*it)["Parameter"]["group"].is_string()){
        group = ((*it)["Parameter"]["group"].get<nlohmann::json::string_t>());
    } 
        if((*it)["Parameter"]["desc"].is_string()){
        desc = ((*it)["Parameter"]["desc"].get<nlohmann::json::string_t>());
    } 
    if((*it)["Parameter"]["v_type"].is_number()){
        v_type = ((*it)["Parameter"]["v_type"].get<nlohmann::json::number_integer_t>());
    } 
    if((*it)["Parameter"]["c_type"].is_number()){
        c_type = ((*it)["Parameter"]["c_type"].get<nlohmann::json::number_integer_t>());
    } 
    if((*it)["Parameter"]["d_flags"].is_number()){
        d_flags = ((*it)["Parameter"]["d_flags"].get<nlohmann::json::number_integer_t>());
    } 
    if((*it)["value"].is_number()){
        value = ((*it)["value"].get<nlohmann::json::number_float_t>());
    }
    if((*it)["std_value"].is_number()){
        std_value = ((*it)["value"].get<nlohmann::json::number_float_t>());
    }  
    if((*it)["Parameter"]["do_not_save"].is_number()){
        do_not_save = ((*it)["Parameter"]["do_not_save"].get<nlohmann::json::number_float_t>());
    }  
    if((*it)["Parameter"]["non_controllable"].is_number()){
        non_controllable = ((*it)["Parameter"]["non_controllable"].get<nlohmann::json::number_integer_t>());
    }  
    if((*it)["lower"].is_number()){
        lower = ((*it)["lower"].get<nlohmann::json::number_float_t>());
    }  
    if((*it)["upper"].is_number()){
        upper = ((*it)["upper"].get<nlohmann::json::number_float_t>());
    }  
    if((*it)["step"].is_number()){
        step = ((*it)["step"].get<nlohmann::json::number_float_t>());
    }  

    // dump the vars
    std::cout   << ";      parmtype: " << parmtype << "\n"
                << ";      id: " << id << "\n"
                << ";      name: " << name << "\n"
                << ";      group: " << group << "\n"
                << ";      desc: " << desc << "\n"
                << ";      v_type: " << v_type << "\n"
                << ";      c_type: " << c_type << "\n"
                << ";      d_flags: " << d_flags << "\n"
                << ";      value: " << value << "\n"
                << ";      std_value: " << std_value << "\n"
                << ";      do_not_save: " << do_not_save << "\n"
                << ";      non_controllable: " << non_controllable << "\n"
                << ";      lower: " << lower << "\n"
                << ";      upper: " << upper << "\n"
                << ";      step: " << step << "\n"
                << "\n";

    value = 0;

    }

 }
printf("End Parsing\n");
}


        // std::cout << ";      group: " << (*it)["Parameter"]["group"] << "\n"  // old out
        //         << "name: " << (*it)["Parameter"]["name"] << "\n"
        //         << ";         id: " << (*it)["Parameter"]["id"] << "\n"
        //         << ";      value: " << (*it)["value"]    << "\n"
        //         << ";      value2: " << value << "\n"
        //         << ";  std_value: " << (*it)["Parameter"]["std_value"] << "\n"
        //         << ";      upper: " << (*it)["Parameter"]["upper"] << "\n"
        //         << ";      lower: " << (*it)["Parameter"]["lower"] << "\n"
        //         << ";value_names: " << (*it)["Parameter"]["value_names"] << "\n"
        //         << "\n";



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
