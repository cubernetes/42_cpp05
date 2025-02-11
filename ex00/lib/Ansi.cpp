// https://no-color.org/
// NO_COLOR=1 ./ex00 -> no color output

#include <cstdlib>
#include <sstream>
#include <string>

#include "Ansi.hpp"
#include "Constants.hpp"

static inline std::string itoa(int n) {
    std::ostringstream oss;
    oss << n;
    return oss.str();
}

bool ansi::noColor() {
    if (Constants::forceNoColor)
        return true;
    const char *noColor = std::getenv("NO_COLOR");
    if (noColor == NULL)
        return false;
    else if (noColor[0] == '\0' || (noColor[0] == '0' && noColor[1] == '\0'))
        return false;
    return true;
}

std::string ansi::black(std::string s) {
    if (noColor())
        return s;
    return ANSI_BLACK + s + ANSI_RST;
}

std::string ansi::red(std::string s) {
    if (noColor())
        return s;
    return ANSI_RED + s + ANSI_RST;
}

std::string ansi::green(std::string s) {
    if (noColor())
        return s;
    return ANSI_GREEN + s + ANSI_RST;
}

std::string ansi::yellow(std::string s) {
    if (noColor())
        return s;
    return ANSI_YELLOW + s + ANSI_RST;
}

std::string ansi::blue(std::string s) {
    if (noColor())
        return s;
    return ANSI_BLUE + s + ANSI_RST;
}

std::string ansi::magenta(std::string s) {
    if (noColor())
        return s;
    return ANSI_MAGENTA + s + ANSI_RST;
}

std::string ansi::cyan(std::string s) {
    if (noColor())
        return s;
    return ANSI_CYAN + s + ANSI_RST;
}

std::string ansi::white(std::string s) {
    if (noColor())
        return s;
    return ANSI_WHITE + s + ANSI_RST;
}

std::string ansi::blackBg(std::string s) {
    if (noColor())
        return s;
    return ANSI_BLACK_BG + s + ANSI_RST;
}

std::string ansi::redBg(std::string s) {
    if (noColor())
        return s;
    return ANSI_RED_BG + s + ANSI_RST;
}

std::string ansi::greenBg(std::string s) {
    if (noColor())
        return s;
    return ANSI_BLACK ANSI_GREEN_BG + s + ANSI_RST;
}

std::string ansi::yellowBg(std::string s) {
    if (noColor())
        return s;
    return ANSI_BLACK ANSI_YELLOW_BG + s + ANSI_RST;
}

std::string ansi::blueBg(std::string s) {
    if (noColor())
        return s;
    return ANSI_BLUE_BG + s + ANSI_RST;
}

std::string ansi::magentaBg(std::string s) {
    if (noColor())
        return s;
    return ANSI_MAGENTA_BG + s + ANSI_RST;
}

std::string ansi::cyanBg(std::string s) {
    if (noColor())
        return s;
    return ANSI_BLACK ANSI_CYAN_BG + s + ANSI_RST;
}

std::string ansi::whiteBg(std::string s) {
    if (noColor())
        return s;
    return ANSI_BLACK ANSI_WHITE_BG + s + ANSI_RST;
}

std::string ansi::rgbP(std::string s, int r, int g, int b) {
    if (noColor())
        return s;
    return ANSI_CSI ANSI_RGB ";" + itoa(r) + ";" + itoa(g) + ";" + itoa(b) + "m" + s + ANSI_RST;
}

std::string ansi::rgb(std::string s, const std::string &rgbSemicolon) {
    if (noColor())
        return s;
    return ANSI_CSI ANSI_RGB ";" + rgbSemicolon + "m" + s + ANSI_RST;
}

std::string ansi::rgbBgP(std::string s, int r, int g, int b) {
    if (noColor())
        return s;
    return ANSI_CSI ANSI_RGB_BG ";" + itoa(r) + ";" + itoa(g) + ";" + itoa(b) + "m" + s + ANSI_RST;
}

std::string ansi::rgbBg(std::string s, const std::string &rgbSemicolon) {
    if (noColor())
        return s;
    return ANSI_CSI ANSI_RGB_BG ";" + rgbSemicolon + "m" + s + ANSI_RST;
}
