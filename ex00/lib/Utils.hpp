#pragma once /* Utils.hpp */

#include <cstddef>
#include <ctime>
#include <ios>
#include <netinet/in.h>
#include <sstream>
#include <string>
#include <vector>

#include "MacroMagic.h"

using std::vector;

struct sockaddr_in_wrapper {
    struct in_addr sin_addr;
    in_port_t sin_port;
    sockaddr_in_wrapper(sockaddr_in saddr) : sin_addr(saddr.sin_addr), sin_port(saddr.sin_port) {}
    sockaddr_in_wrapper(struct in_addr _sin_addr, in_port_t _sin_port) : sin_addr(_sin_addr), sin_port(_sin_port) {}
    sockaddr_in_wrapper() : sin_addr(), sin_port() {}
};

struct pollevents_helper {
    short events;
    pollevents_helper(short e) : events(e) {}
    pollevents_helper() : events() {}
};

struct in_port_t_helper {
    in_port_t port;
    in_port_t_helper(in_port_t p) : port(p) {}
    in_port_t_helper() : port() {}
};

namespace Utils {
    std::string parseArgs(int ac, char **av);
    bool isPrefix(std::string prefix, std::string longerString);
    std::string strToLower(const std::string &str);
    std::string strToUpper(const std::string &str);
    char decodeTwoHexChars(const char _c1, const char _c2);
    bool isHexDigitNoCase(const char c);
    std::size_t convertSizeToBytes(const std::string &sizeStr);
    std::string replaceAll(std::string s, const std::string &search, const std::string &replace);
    std::string jsonEscape(const std::string &s);
    std::string escapeExceptNlAndTab(const std::string &s);
    std::string escape(const std::string &s);
    bool allUppercase(const std::string &str);
    std::string ellipsisize(const std::string &str, std::size_t maxLen);
    std::string formattedTimestamp(std::time_t _t = 0, bool forLogger = false);
    std::string millisecondRemainderSinceEpoch();
    std::string formatSI(std::size_t size);

    template <typename T> static inline vector<T> &getTmpVec() {
        static vector<T> _;
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

// Helper macro to create inplace vectors (i.e. passing as an argument), very useful
// sometimes
#define VEC(type, ...) (Utils::getTmpVec<type>().clear(), FOR_EACH_ONE(TMP_VEC_PUSH_BACK, type, __VA_ARGS__) Utils::getTmpVec<type>())
