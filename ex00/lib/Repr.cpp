#include <iostream>
#include <string>

#include "Ansi.hpp"
#include "Opt.h"
#include "Repr.hpp"

using ansi::noColor;
using ansi::rgb;
using ansi::rgbBg;

void reprInit() CPP98(throw()) CPP23(noexcept) {
    if (!noColor())
        std::cout << ANSI_FG;
}

void reprDone() CPP98(throw()) CPP23(noexcept) {
    if (!noColor())
        std::cout << ANSI_RST << '\n';
}

CPP23([[nodiscard]]) std::string ReprClr::str(std::string s) CPP98(throw()) CPP23(noexcept) { return rgbBg(rgb(s, ANSI_STR), ANSI_FG); }
CPP23([[nodiscard]]) std::string ReprClr::chr(std::string s) CPP98(throw()) CPP23(noexcept) { return rgbBg(rgb(s, ANSI_CHR), ANSI_FG); }
CPP23([[nodiscard]]) std::string ReprClr::kwrd(std::string s) CPP98(throw()) CPP23(noexcept) { return rgbBg(rgb(s, ANSI_KWRD), ANSI_FG); }
CPP23([[nodiscard]]) std::string ReprClr::punct(std::string s) CPP98(throw()) CPP23(noexcept) { return rgbBg(rgb(s, ANSI_PUNCT), ANSI_FG); }
CPP23([[nodiscard]]) std::string ReprClr::func(std::string s) CPP98(throw()) CPP23(noexcept) { return rgbBg(rgb(s, ANSI_FUNC), ANSI_FG); }
CPP23([[nodiscard]]) std::string ReprClr::num(std::string s) CPP98(throw()) CPP23(noexcept) { return rgbBg(rgb(s, ANSI_NUM), ANSI_FG); }
CPP23([[nodiscard]]) std::string ReprClr::var(std::string s) CPP98(throw()) CPP23(noexcept) { return rgbBg(rgb(s, ANSI_VAR), ANSI_FG); }
CPP23([[nodiscard]]) std::string ReprClr::cmt(std::string s) CPP98(throw()) CPP23(noexcept) { return rgbBg(rgb(s, ANSI_CMT), ANSI_FG); }
