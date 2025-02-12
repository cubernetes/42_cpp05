#pragma once /* Utils.hpp */

#include <cstddef>
#include <ctime>
#include <ios>
#include <sstream>
#include <string>
#include <vector>

#include "MacroMagic.h"
#include "Opt.h"

namespace Utils {
    CPP23([[nodiscard]]) std::string replaceAll(std::string s, const std::string &search, const std::string &replace) CPP98(throw()) CPP23(noexcept);
    CPP23([[nodiscard]]) std::string jsonEscape(const std::string &s) CPP98(throw()) CPP23(noexcept);
    CPP23([[nodiscard]]) std::string escapeExceptNlAndTab(const std::string &s) CPP98(throw()) CPP23(noexcept);
    CPP23([[nodiscard]]) std::string escape(const std::string &s) CPP98(throw()) CPP23(noexcept);
    CPP23([[nodiscard]]) std::string ellipsisize(const std::string &str, std::size_t maxLen) CPP98(throw()) CPP23(noexcept);
    CPP23([[nodiscard]]) std::string formattedTimestamp(std::time_t _t = 0, bool forLogger = false) CPP98(throw()) CPP23(noexcept);
    CPP23([[nodiscard]]) std::string millisecondRemainderSinceEpoch() CPP98(throw()) CPP23(noexcept);

    template <typename T> CPP23([[nodiscard]]) static inline std::vector<T> &getTmpVec() CPP98(throw()) CPP23(noexcept) {
        static std::vector<T> _;
        return _;
    }

    // TODO: @timo: improve repr to specify no color
    template <typename T> CPP23([[nodiscard]]) static inline std::string STR(T x) CPP98(throw()) CPP23(noexcept) {
        std::ostringstream oss;
        oss << std::dec << x;
        return oss.str();
    }
} // namespace Utils

#define TMP_VEC_PUSH_BACK(type, x) Utils::getTmpVec<type>().push_back(x),

// Helper macro to create inplace std::vectors (i.e. passing as an argument), very useful
// sometimes
#define VEC(type, ...) (Utils::getTmpVec<type>().clear(), FOR_EACH_ONE(TMP_VEC_PUSH_BACK, type, __VA_ARGS__) Utils::getTmpVec<type>())
