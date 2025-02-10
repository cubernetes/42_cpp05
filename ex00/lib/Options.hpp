#pragma once /* Options.hpp */

#include "Logger.hpp"

class Options {
  public:
    Options(int ac, char **av);

    bool printHelp;
    bool printVersion;
    Logger::Level logLevel;
};
