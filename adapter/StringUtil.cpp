#include "StringUtil.hpp"

namespace sutil {

std::vector<std::string_view> split(const std::string_view& str, char sep) {
    std::vector<std::string_view> result;
    size_t begin = 0;
    size_t end = 0;

    for (size_t i = 0; i < str.size(); i++) {
        if (str.at(i) == sep) {
            if (begin < end) {
                result.push_back(std::string_view(str).substr(begin, end));
            }
            begin += 1;
        } else {
            if (begin == end) {
                begin = i;
            }
            end += 1;
        }
    }

    return result;
}

}