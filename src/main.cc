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
    printf("Begin Parsing\n");
    using json = nlohmann::json;

// ...

std::ifstream f("thefile.json");
json data = json::parse(f);

string s = data.dump();

cout << "serialization with pretty printing: " << data.dump(4) << endl;


    printf("End Parsing\n");
}