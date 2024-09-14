#include "StringUtil.hpp"

namespace sutil {

std::vector<std::string_view> split(const std::string_view& str, char sep) {
    std::vector<std::string_view> result;
    size_t begin = 0;
    size_t size = 0;

    for (size_t i = 0; i < str.size(); i++) {
        if (str.at(i) == sep) {
            if (size > 0) {
                result.push_back(std::string_view(str).substr(begin, size));
            }
            begin = i + 1;
            size = 0;
        } else {
            size += 1;
        }
    }

    if (size > 0) {
        result.push_back(std::string_view(str).substr(begin, size));
    }

    return result;
}

}