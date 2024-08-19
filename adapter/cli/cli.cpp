#include "Cmd.hpp"

#include <iostream>
#include <unordered_map>
#include <dlfcn.h>

#include "../Database.hpp"

void execCmd(const adapter::Params& p) {
    adapter::CmdParamValidator validator({
        {"file", true},
    });

    if (!validator.isValid(p)) return;

    std::string_view file = p.at("file");
    char* error;

    std::cout << "Compiling query..." << std::endl;
    system("make cquery");
    std::cout << "Finished compiling query!" << std::endl;

    std::cout << "Loading query..." << std::endl;
    dlerror();
    void* query = dlopen("./bin/query", RTLD_LAZY | RTLD_DEEPBIND);

    if (error = dlerror()) {
        std::cout << error << std::endl;
        return;
    }
    std::cout << "Finished loading query!" << std::endl;
    
    std::cout << "Executing query..." << std::endl;
    auto exec = reinterpret_cast<void(*)(void*)>(dlsym(query, "exec"));

    if (error = dlerror()) {
        std::cout << error << std::endl;
        return;
    }
    
    exec(adapter::Database::getInstance());
    std::cout << "Finished executing query!" << std::endl;
}

int main(int argc, char** argv) {
    std::cout << "Initializing DB..." << std::endl;
    adapter::Database::getInstance();
    std::cout << "Finished initializing DB!" << std::endl;

    while (true) {
        std::string in;
        std::getline(std::cin, in);

        adapter::Cmd cmd;
        adapter::CmdParser parser(in);

        if (parser.parse(&cmd)) {
            if (cmd.name == "exec") {
                execCmd(cmd.params);
            } else {
                std::cout << "Unknown command!" << std::endl;
            }
        } else {
            std::cout << "Parsing failed!" << std::endl;
        }
    }
}