#pragma once /* Ansi.hpp */

#include <string>

#include "Opt.h"

// clang-format off
#define ANSI_CSI                 "\x1b\x5b"
#define ANSI_RGB                 "38;2"
#define ANSI_RGB_BG              "48;2"
#define ANSI_RST        ANSI_CSI      "m"
#define ANSI_BLACK      ANSI_CSI "30" "m"
#define ANSI_RED        ANSI_CSI "31" "m"
#define ANSI_GREEN      ANSI_CSI "32" "m"
#define ANSI_YELLOW     ANSI_CSI "33" "m"
#define ANSI_BLUE       ANSI_CSI "34" "m"
#define ANSI_MAGENTA    ANSI_CSI "35" "m"
#define ANSI_CYAN       ANSI_CSI "36" "m"
#define ANSI_WHITE      ANSI_CSI "37" "m"
#define ANSI_BLACK_BG   ANSI_CSI "40" "m"
#define ANSI_RED_BG     ANSI_CSI "41" "m"
#define ANSI_GREEN_BG   ANSI_CSI "42" "m"
#define ANSI_YELLOW_BG  ANSI_CSI "43" "m"
#define ANSI_BLUE_BG    ANSI_CSI "44" "m"
#define ANSI_MAGENTA_BG ANSI_CSI "45" "m"
#define ANSI_CYAN_BG    ANSI_CSI "46" "m"
#define ANSI_WHITE_BG   ANSI_CSI "47" "m"
// clang-format on

namespace ansi {
    CPP23([[nodiscard]]) bool noColor() CPP98(throw()) CPP23(noexcept);
    CPP23([[nodiscard]]) std::string black(std::string s) CPP98(throw()) CPP23(noexcept);
    CPP23([[nodiscard]]) std::string red(std::string s) CPP98(throw()) CPP23(noexcept);
    CPP23([[nodiscard]]) std::string green(std::string s) CPP98(throw()) CPP23(noexcept);
    CPP23([[nodiscard]]) std::string yellow(std::string s) CPP98(throw()) CPP23(noexcept);
    CPP23([[nodiscard]]) std::string blue(std::string s) CPP98(throw()) CPP23(noexcept);
    CPP23([[nodiscard]]) std::string magenta(std::string s) CPP98(throw()) CPP23(noexcept);
    CPP23([[nodiscard]]) std::string cyan(std::string s) CPP98(throw()) CPP23(noexcept);
    CPP23([[nodiscard]]) std::string white(std::string s) CPP98(throw()) CPP23(noexcept);
    CPP23([[nodiscard]]) std::string blackBg(std::string s) CPP98(throw()) CPP23(noexcept);
    CPP23([[nodiscard]]) std::string redBg(std::string s) CPP98(throw()) CPP23(noexcept);
    CPP23([[nodiscard]]) std::string greenBg(std::string s) CPP98(throw()) CPP23(noexcept);
    CPP23([[nodiscard]]) std::string yellowBg(std::string s) CPP98(throw()) CPP23(noexcept);
    CPP23([[nodiscard]]) std::string blueBg(std::string s) CPP98(throw()) CPP23(noexcept);
    CPP23([[nodiscard]]) std::string magentaBg(std::string s) CPP98(throw()) CPP23(noexcept);
    CPP23([[nodiscard]]) std::string cyanBg(std::string s) CPP98(throw()) CPP23(noexcept);
    CPP23([[nodiscard]]) std::string whiteBg(std::string s) CPP98(throw()) CPP23(noexcept);
    CPP23([[nodiscard]]) std::string rgbP(std::string s, int r, int g, int b) CPP98(throw()) CPP23(noexcept);
    CPP23([[nodiscard]]) std::string rgbBgP(std::string s, int r, int g, int b) CPP98(throw()) CPP23(noexcept);
    CPP23([[nodiscard]]) std::string rgb(std::string s, const std::string &rgbSemicolon) CPP98(throw()) CPP23(noexcept);
    CPP23([[nodiscard]]) std::string rgbBg(std::string s, const std::string &rgbSemicolon) CPP98(throw()) CPP23(noexcept);
} // namespace ansi
