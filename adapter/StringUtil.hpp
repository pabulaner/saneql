#pragma once

#include <vector>
#include <string>

namespace sutil {

std::vector<std::string_view> split(const std::string& str, char sep);

}