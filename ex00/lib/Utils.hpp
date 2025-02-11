#pragma once /* Utils.hpp */

#include <cstddef>
#include <ctime>
#include <ios>
#include <sstream>
#include <string>
#include <vector>

#include "MacroMagic.h"

namespace Utils {
    std::string replaceAll(std::string s, const std::string &search, const std::string &replace);
    std::string jsonEscape(const std::string &s);
    std::string escapeExceptNlAndTab(const std::string &s);
    std::string escape(const std::string &s);
    std::string ellipsisize(const std::string &str, std::size_t maxLen);
    std::string formattedTimestamp(std::time_t _t = 0, bool forLogger = false);
    std::string millisecondRemainderSinceEpoch();

    template <typename T> static inline std::vector<T> &getTmpVec() {
        static std::vector<T> _;
        return _;
    }

    // TODO: @timo: improve repr to specify no color
    template <typename T> static inline std::string STR(T x) {
        std::ostringstream oss;
        oss << std::dec << x;
        return oss.str();
    }
} // namespace Utils

#define TMP_VEC_PUSH_BACK(type, x) Utils::getTmpVec<type>().push_back(x),

// Helper macro to create inplace std::vectors (i.e. passing as an argument), very useful
// sometimes
#define VEC(type, ...) (Utils::getTmpVec<type>().clear(), FOR_EACH_ONE(TMP_VEC_PUSH_BACK, type, __VA_ARGS__) Utils::getTmpVec<type>())
