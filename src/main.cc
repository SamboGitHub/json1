#include <stdio.h>
#include "inky.h"
#include <nlohmann/json.hpp>
#include <fstream>



int main(int argc, char**argv)
{
    printf("Begin Parsing\n");
    using json = nlohmann::json;

// ...

std::ifstream f("thefile.json");
json data = json::parse(f);
    printf("End Parsing\n");
}