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
std::cout << result_array[1] << "\n"; 

// json detail = json::parse(valstring);
// json detail = json::parse(result_array);
std::cout << "Done Parse the Parse \n";

// for (json::iterator that = detail.begin(); that != detail.end(); ++that)
// {

//     std::cout << " - " ;
//     keystring = that.key();

//     if(keystring.find("result") == 0)
//     {
        
//         std::cout << that.key();
//         // std::cout << " : ";
//         std::cout << that.value();
//         std::cout << "\n";
//         valstring = that.value();
//     }
    //   dumps all
    //    std::cout << it.key() << " : " << it.value() << "\n";
// }




printf("End Parsing\n");
}


// STL-like access
// We designed the JSON class to behave just like an STL container. In fact, it satisfies the ReversibleContainer requirement.

// // create an array using push_back
// json j;
// j.push_back("foo");
// j.push_back(1);
// j.push_back(true);

// // also use emplace_back
// j.emplace_back(1.78);

// // iterate the array
// for (json::iterator it = j.begin(); it != j.end(); ++it) {
//   std::cout << *it << '\n';
// }

// // range-based for
// for (auto& element : j) {
//   std::cout << element << '\n';
// }

// // getter/setter
// const auto tmp = j[0].template get<std::string>();
// j[1] = 42;
// bool foo = j.at(2);

// // comparison
// j == R"(["foo", 1, true, 1.78])"_json;  // true

// // other stuff
// j.size();     // 4 entries
// j.empty();    // false
// j.type();     // json::value_t::array
// j.clear();    // the array is empty again

// // convenience type checkers
// j.is_null();
// j.is_boolean();
// j.is_number();
// j.is_object();
// j.is_array();
// j.is_string();

// // create an object
// json o;
// o["foo"] = 23;
// o["bar"] = false;
// o["baz"] = 3.141;

// // also use emplace
// o.emplace("weather", "sunny");

// // special iterator member functions for objects
// for (json::iterator it = o.begin(); it != o.end(); ++it) {
//   std::cout << it.key() << " : " << it.value() << "\n";
// }

// // the same code as range for
// for (auto& el : o.items()) {
//   std::cout << el.key() << " : " << el.value() << "\n";
// }

// // even easier with structured bindings (C++17)
// for (auto& [key, value] : o.items()) {
//   std::cout << key << " : " << value << "\n";
// }

// // find an entry
// if (o.contains("foo")) {
//   // there is an entry with key "foo"
// }

// // or via find and an iterator
// if (o.find("foo") != o.end()) {
//   // there is an entry with key "foo"
// }

// // or simpler using count()
// int foo_present = o.count("foo"); // 1
// int fob_present = o.count("fob"); // 0

// // delete an entry
// o.erase("foo");