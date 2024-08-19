#include "Cmd.hpp"

#include <iostream>

namespace adapter {

CmdParser::CmdParser(const std::string& raw) : raw(raw) {}

bool CmdParser::isEmpty() {
    for (char c : raw) {
        if (c != ' ') {
            return false;
        }
    }
    return true;
}

bool CmdParser::parse(Cmd* cmd) {
    state = Begin;

    size_t index = 0;
    std::string_view key = "";

    char sep = ' ';
    char eq = '=';

    for (size_t i = 0; i < raw.size(); i++) {
        char c = raw.at(i);

        switch (state) {
            case Begin:
                if (c != sep) {
                    if (c != eq) {
                        index = i;
                        state = Name;
                    } else {
                        return false;
                    }
                }
                break;
            case Name:
                if (c == eq) {
                    return false;
                } else if (c == sep) {
                    cmd->name = raw.substr(index, i - index);
                    state = End;
                }
                break;
            case End:
                if (c != sep) {
                    if (c != eq) {
                        index = i;
                        state = Key;
                    } else {
                        return false;
                    }
                }
                break;
            case Key:
                if (c != sep) {
                    if (c == eq) {
                        key = raw.substr(index, i - index);
                        index = ++i;
                        state = Value;
                    }
                } else {
                    return false;
                }
                break;
            case Value:
                if (c == eq) {
                    return false;
                } else if (c == sep) {
                    cmd->params[key] = raw.substr(index, i - index);
                    state = End;
                }
                break;
        }
    }

    if (state == Name) {
        cmd->name = raw.substr(index, raw.size() - index);
        state = End;
    } else if (state == Value) {
        cmd->params[key] = raw.substr(index, raw.size() - index);
        state = End;
    }

    return state == End;
}

CmdParamValidator::CmdParamValidator(const std::vector<ParamInfo>& infos) 
    : infos(infos)
{}

bool CmdParamValidator::isValid(const Params& params) {
    bool valid = true;
    
    for (auto& info : infos) {
        if (info.required && !params.contains(info.key)) {
            std::cout << "Parameter '" << info.key << "' was not specified, but is required" << std::endl;
            valid = false;
        }
    }

    for (auto& p : params) {
        bool found = false;

        for (auto& info : infos) {
            if (info.key == p.first) {
                found = true;
            }
        }

        if (!found) {
            std::cout << "Unknown parameter '" << p.first << "'" << std::endl;
            valid = false;
        }
    }

    return valid;
}

}