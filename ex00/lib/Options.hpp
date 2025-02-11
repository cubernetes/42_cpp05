#pragma once /* Options.hpp */

#include "Logger.hpp"
#include "Opt.h"

class Options {
  public:
    Options(int ac, char **av) CPP98(throw(std::runtime_error)) CPP23(noexcept(false));

    bool printHelp;
    bool printVersion;
    Logger::Level logLevel;
};
