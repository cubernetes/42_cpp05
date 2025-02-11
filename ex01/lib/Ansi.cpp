// https://no-color.org/
// NO_COLOR=1 ./ex01 -> no color output

#include <cstdlib>
#include <sstream>
#include <string>

#include "Ansi.hpp"
#include "Constants.hpp"
#include "Opt.h"

CPP23([[nodiscard]]) static inline std::string itoa(int n) CPP98(throw()) CPP23(noexcept) {
    std::ostringstream oss;
    oss << n;
    return oss.str();
}

CPP23([[nodiscard]]) bool ansi::noColor() CPP98(throw()) CPP23(noexcept) {
    if (Constants::forceNoColor)
        return true;
    const char *noColor = std::getenv("NO_COLOR");
    if (noColor == NULL)
        return false;
    else if (noColor[0] == '\0' || (noColor[0] == '0' && noColor[1] == '\0'))
        return false;
    return true;
}

CPP23([[nodiscard]]) std::string ansi::black(std::string s) CPP98(throw()) CPP23(noexcept) {
    if (noColor())
        return s;
    return ANSI_BLACK + s + ANSI_RST;
}

CPP23([[nodiscard]]) std::string ansi::red(std::string s) CPP98(throw()) CPP23(noexcept) {
    if (noColor())
        return s;
    return ANSI_RED + s + ANSI_RST;
}

CPP23([[nodiscard]]) std::string ansi::green(std::string s) CPP98(throw()) CPP23(noexcept) {
    if (noColor())
        return s;
    return ANSI_GREEN + s + ANSI_RST;
}

CPP23([[nodiscard]]) std::string ansi::yellow(std::string s) CPP98(throw()) CPP23(noexcept) {
    if (noColor())
        return s;
    return ANSI_YELLOW + s + ANSI_RST;
}

CPP23([[nodiscard]]) std::string ansi::blue(std::string s) CPP98(throw()) CPP23(noexcept) {
    if (noColor())
        return s;
    return ANSI_BLUE + s + ANSI_RST;
}

CPP23([[nodiscard]]) std::string ansi::magenta(std::string s) CPP98(throw()) CPP23(noexcept) {
    if (noColor())
        return s;
    return ANSI_MAGENTA + s + ANSI_RST;
}

CPP23([[nodiscard]]) std::string ansi::cyan(std::string s) CPP98(throw()) CPP23(noexcept) {
    if (noColor())
        return s;
    return ANSI_CYAN + s + ANSI_RST;
}

CPP23([[nodiscard]]) std::string ansi::white(std::string s) CPP98(throw()) CPP23(noexcept) {
    if (noColor())
        return s;
    return ANSI_WHITE + s + ANSI_RST;
}

CPP23([[nodiscard]]) std::string ansi::blackBg(std::string s) CPP98(throw()) CPP23(noexcept) {
    if (noColor())
        return s;
    return ANSI_BLACK_BG + s + ANSI_RST;
}

CPP23([[nodiscard]]) std::string ansi::redBg(std::string s) CPP98(throw()) CPP23(noexcept) {
    if (noColor())
        return s;
    return ANSI_RED_BG + s + ANSI_RST;
}

CPP23([[nodiscard]]) std::string ansi::greenBg(std::string s) CPP98(throw()) CPP23(noexcept) {
    if (noColor())
        return s;
    return ANSI_BLACK ANSI_GREEN_BG + s + ANSI_RST;
}

CPP23([[nodiscard]]) std::string ansi::yellowBg(std::string s) CPP98(throw()) CPP23(noexcept) {
    if (noColor())
        return s;
    return ANSI_BLACK ANSI_YELLOW_BG + s + ANSI_RST;
}

CPP23([[nodiscard]]) std::string ansi::blueBg(std::string s) CPP98(throw()) CPP23(noexcept) {
    if (noColor())
        return s;
    return ANSI_BLUE_BG + s + ANSI_RST;
}

CPP23([[nodiscard]]) std::string ansi::magentaBg(std::string s) CPP98(throw()) CPP23(noexcept) {
    if (noColor())
        return s;
    return ANSI_MAGENTA_BG + s + ANSI_RST;
}

CPP23([[nodiscard]]) std::string ansi::cyanBg(std::string s) CPP98(throw()) CPP23(noexcept) {
    if (noColor())
        return s;
    return ANSI_BLACK ANSI_CYAN_BG + s + ANSI_RST;
}

CPP23([[nodiscard]]) std::string ansi::whiteBg(std::string s) CPP98(throw()) CPP23(noexcept) {
    if (noColor())
        return s;
    return ANSI_BLACK ANSI_WHITE_BG + s + ANSI_RST;
}

CPP23([[nodiscard]]) std::string ansi::rgbP(std::string s, int r, int g, int b) CPP98(throw()) CPP23(noexcept) {
    if (noColor())
        return s;
    return ANSI_CSI ANSI_RGB ";" + itoa(r) + ";" + itoa(g) + ";" + itoa(b) + "m" + s + ANSI_RST;
}

CPP23([[nodiscard]]) std::string ansi::rgb(std::string s, const std::string &rgbSemicolon) CPP98(throw()) CPP23(noexcept) {
    if (noColor())
        return s;
    return ANSI_CSI ANSI_RGB ";" + rgbSemicolon + "m" + s + ANSI_RST;
}

CPP23([[nodiscard]]) std::string ansi::rgbBgP(std::string s, int r, int g, int b) CPP98(throw()) CPP23(noexcept) {
    if (noColor())
        return s;
    return ANSI_CSI ANSI_RGB_BG ";" + itoa(r) + ";" + itoa(g) + ";" + itoa(b) + "m" + s + ANSI_RST;
}

CPP23([[nodiscard]]) std::string ansi::rgbBg(std::string s, const std::string &rgbSemicolon) CPP98(throw()) CPP23(noexcept) {
    if (noColor())
        return s;
    return ANSI_CSI ANSI_RGB_BG ";" + rgbSemicolon + "m" + s + ANSI_RST;
}
