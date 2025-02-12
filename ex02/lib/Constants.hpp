#pragma once /* Constants.hpp */

#include <cstddef>
#include <string>

namespace Constants {
    extern const std::size_t minGrade;
    extern const std::size_t maxGrade;

    extern const std::string &defaultBureaucratName;
    extern const std::size_t defaultBureaucratGrade;

    extern const std::string &defaultFormName;
    extern const bool defaultFormSigned;
    extern const std::size_t defaultFormSignGrade;
    extern const std::size_t defaultFormExecGrade;

    extern bool forceNoColor;
    extern const std::size_t loggingMaxStringLen;
    extern const std::string &programVersion;
    extern const std::string &helpText;
} // namespace Constants
