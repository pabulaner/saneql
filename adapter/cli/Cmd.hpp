#pragma once

#include <string>
#include <unordered_map>
#include <vector>

namespace adapter {

typedef std::unordered_map<std::string_view, std::string_view> Params;

struct Cmd {
    // The name of the command
    std::string_view name;
    // The command parameters
    Params params;
};

class CmdParser {
    // State of the parser
    enum State {
        Begin,
        Name,
        Key,
        Value,
        End,
    };

    // The raw command
    std::string_view raw;
    // The state of the parser
    State state;

    public:
    // The constructor
    CmdParser(const std::string& raw);
    // Checks if the command is empty
    bool isEmpty();
    // Parse the command
    bool parse(Cmd* cmd);
};

class CmdParamValidator {
    public:
    // The info for the parameter
    struct ParamInfo {
        // The key
        std::string key;
        // Is it required
        bool required;
    };
    private:
    // The parameter infos
    std::vector<ParamInfo> infos;

    public:
    // The constructor
    CmdParamValidator(const std::vector<ParamInfo>& infos);
    // Validate the parameters
    bool isValid(const Params& params);
};

}