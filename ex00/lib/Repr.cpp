#include <iostream>
#include <string>

#include "Ansi.hpp"
#include "Repr.hpp"

using ansi::noColor;
using ansi::rgb;
using ansi::rgbBg;

void reprInit() {
    if (!noColor())
        std::cout << ANSI_FG;
}

void reprDone() {
    if (!noColor())
        std::cout << ANSI_RST << '\n';
}

std::string ReprClr::str(std::string s) { return rgbBg(rgb(s, ANSI_STR), ANSI_FG); }

std::string ReprClr::chr(std::string s) { return rgbBg(rgb(s, ANSI_CHR), ANSI_FG); }

std::string ReprClr::kwrd(std::string s) { return rgbBg(rgb(s, ANSI_KWRD), ANSI_FG); }

std::string ReprClr::punct(std::string s) { return rgbBg(rgb(s, ANSI_PUNCT), ANSI_FG); }

std::string ReprClr::func(std::string s) { return rgbBg(rgb(s, ANSI_FUNC), ANSI_FG); }

std::string ReprClr::num(std::string s) { return rgbBg(rgb(s, ANSI_NUM), ANSI_FG); }

std::string ReprClr::var(std::string s) { return rgbBg(rgb(s, ANSI_VAR), ANSI_FG); }

std::string ReprClr::cmt(std::string s) { return rgbBg(rgb(s, ANSI_CMT), ANSI_FG); }
