#include <stdio.h>
#include "inky.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <cassert>
#include <iomanip>

using namespace std;
enum test_type
{
    parms,
    banks,
    rackorder,
    all
};

int main(int argc, char **argv)
{
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

    json::iterator rack_it;
    json rack_result_array = json::array();
    json::iterator rack_array_it;
    json rack_preset_result_array = json::array();
    json::iterator rack_preset_array_it;

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
    int do_not_save = 0;                               // Bool
    int non_controllable = 0;                          // Int
    float lower = 0;                                   // Int and Float
    float upper = 0;                                   // Int and Float
    float step = 0;                                    // Float
    std::array<string, 20> value_names = {{"a", "b"}}; // Enum

    // Start to define the class structure
    std::string bank_name = "";
    int bank_mutable = 0;
    std::string bank_type = "";
    std::array<string, 20> bank_presets = {{""}}; // Enum
    int bank_preset_index = 0;

    // Start to define the class structure
    std::array<string, 20> rack_presets = {{""}}; // Enum
    int rack_preset_index = 0;

    printf("Begin Reading Params File\n");
    std::ifstream f("Params.json");
    printf("Begin Reading Banks File\n");
    std::ifstream f_banks("Banks.json");
    printf("Begin Reading racks File\n");
    std::ifstream f_racks("GetRackUnitOrder.json");

    json data;
    json bank_data;
    json rack_data;

    test_type test = rackorder;

    switch (test)
    {
    case parms:
        // params.json parsing
        //...
        printf("Begin First Parm Parsing\n");
        data = json::parse(f);

        printf("Begin Iterating Parse 1 \n");
        for (parm_it = data.begin(); parm_it != data.end(); ++parm_it)
        {
            printf("Inside Parse 1 For Loop \n");

            keystring = parm_it.key();
            std::cout << keystring << " - ";

            if (keystring.find("result") == 0)
            {
                parm_result_array = parm_it.value();
            }
        }

        // Loop throught the array and parse into values. We get back a string (parameter type) and an object (the deets)
        std::cout << "IDs" << "\n";
        for (parm_array_it = parm_result_array.begin(); parm_array_it != parm_result_array.end(); ++parm_array_it)
        {
            // skip anything that isn't an object

            if (parm_array_it->is_string())
            {

                parmtype = (*parm_array_it);
                // std::cout << "; parmtype: " << (*parm_array_it)
                // std::cout << "; parmtype: " << parmtype
                //  << "\n";
                // Jump to next iterator to get to the associated object for this type
                parm_array_it++;
            }

            if (parm_array_it->is_object())
            {

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
                do_not_save = 0;      // Bool
                non_controllable = 0; // Int
                lower = 0;            // Int and bank_dataFloat
                upper = 0;            // Int and Float
                step = 0;             // Float

                // load if valid values
                id = "";
                name = "";
                group = "";
                desc = "";

                if ((*parm_array_it)["Parameter"]["id"].is_string())
                {
                    id = ((*parm_array_it)["Parameter"]["id"].get<nlohmann::json::string_t>());
                }
                if ((*parm_array_it)["Parameter"]["name"].is_string())
                {
                    name = ((*parm_array_it)["Parameter"]["name"].get<nlohmann::json::string_t>());
                }
                if ((*parm_array_it)["Parameter"]["group"].is_string())
                {
                    group = ((*parm_array_it)["Parameter"]["group"].get<nlohmann::json::string_t>());
                }
                if ((*parm_array_it)["Parameter"]["desc"].is_string())
                {
                    desc = ((*parm_array_it)["Parameter"]["desc"].get<nlohmann::json::string_t>());
                }
                if ((*parm_array_it)["Parameter"]["v_type"].is_number())
                {
                    v_type = ((*parm_array_it)["Parameter"]["v_type"].get<nlohmann::json::number_integer_t>());
                }
                if ((*parm_array_it)["Parameter"]["c_type"].is_number())
                {
                    c_type = ((*parm_array_it)["Parameter"]["c_type"].get<nlohmann::json::number_integer_t>());
                }
                if ((*parm_array_it)["Parameter"]["d_flags"].is_number())
                {
                    d_flags = ((*parm_array_it)["Parameter"]["d_flags"].get<nlohmann::json::number_integer_t>());
                }
                if ((*parm_array_it)["value"].is_number())
                {
                    value = ((*parm_array_it)["value"].get<nlohmann::json::number_float_t>());
                }
                if ((*parm_array_it)["std_value"].is_number())
                {
                    std_value = ((*parm_array_it)["value"].get<nlohmann::json::number_float_t>());
                }
                if ((*parm_array_it)["Parameter"]["do_not_save"].is_number())
                {
                    do_not_save = ((*parm_array_it)["Parameter"]["do_not_save"].get<nlohmann::json::number_float_t>());
                }
                if ((*parm_array_it)["Parameter"]["non_controllable"].is_number())
                {
                    non_controllable = ((*parm_array_it)["Parameter"]["non_controllable"].get<nlohmann::json::number_integer_t>());
                }
                if ((*parm_array_it)["lower"].is_number())
                {
                    lower = ((*parm_array_it)["lower"].get<nlohmann::json::number_float_t>());
                }
                if ((*parm_array_it)["upper"].is_number())
                {
                    upper = ((*parm_array_it)["upper"].get<nlohmann::json::number_float_t>());
                }
                if ((*parm_array_it)["step"].is_number())
                {
                    step = ((*parm_array_it)["step"].get<nlohmann::json::number_float_t>());
                }

                // dump the vars
                std::cout << "      parmtype: " << parmtype << "\n"
                          << "      id: " << id << "\n"
                          << "      name: " << name << "\n"
                          << "      group: " << group << "\n"
                          << "      desc: " << desc << "\n"
                          << "      v_type: " << v_type << "\n"
                          << "      c_type: " << c_type << "\n"
                          << "      d_flags: " << d_flags << "\n"
                          << "      value: " << value << "\n"
                          << "      std_value: " << std_value << "\n"
                          << "      do_not_save: " << do_not_save << "\n"
                          << "      non_controllable: " << non_controllable << "\n"
                          << "      lower: " << lower << "\n"
                          << "      upper: " << upper << "\n"
                          << "      step: " << step << "\n"
                          << "\n";

                value = 0;
            }
        }
        printf("End Parsing Params\n");
        break;

    case banks:

        printf("Begin First Bank Parsing\n");
        bank_data = json::parse(f_banks);

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
        break;

    case rackorder:

        printf("Begin First rack Parsing\n");
        rack_data = json::parse(f_racks);

        printf("Begin Iterating Parse 1 \n");
        for (rack_it = rack_data.begin(); rack_it != rack_data.end(); ++rack_it)
        {
            keystring = rack_it.key();
            std::cout << keystring << " - ";

            if (keystring.find("result") == 0)
            {
                rack_result_array = rack_it.value();
            }
        }

        std::cout << "Rack Array Dump: " << (rack_result_array.dump()) << "\n";
        printf("\n");

        // Loop throught the array and parse into values. We only get back an object (the deets)
        rack_preset_index = 0;
        std::cout << "Racks" << "\n";
        for (rack_array_it = rack_result_array.begin(); rack_array_it != rack_result_array.end(); ++rack_array_it)
        {
            // skip anything that isn't an object

            if (rack_array_it->is_string())
            {
                rack_presets[rack_preset_index] = (*rack_array_it);
                std::cout << rack_preset_index << ": " << rack_presets[rack_preset_index] << "\n";
                rack_preset_index++;
            }

            if (rack_array_it->is_object())
            {
                printf("is object");
            }
        }
        break;
    }
}
