#pragma once /* Constants.hpp */

#include <cstddef>
#include <string>

using std::string;

namespace Constants {
    extern const std::string &defaultBureaucratName;
    extern const std::size_t defaultBureaucratGrade;
    extern bool forceNoColor;
    extern const size_t loggingMaxStringLen;
    extern const string &programVersion;
    extern const string &helpText;
} // namespace Constants
