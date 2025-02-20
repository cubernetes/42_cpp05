#include <cstddef>
#include <string>

#include "Constants.hpp"

// leave in .cpp file
#define HELP_TEXT                                                                                                                                                                                      \
    "Usage: ./ex01 [options]\n"                                                                                                                                                                        \
    "\n"                                                                                                                                                                                               \
    "Options:\n"                                                                                                                                                                                       \
    "    -l LEVEL: Specify loglevel. Supported loglevels are"                                                                                                                                          \
    " FATAL/1, ERROR/2, WARNING/3, INFO/4, DEBUG/5, TRACE/6. "                                                                                                                                         \
    "Default is INFO.\n"                                                                                                                                                                               \
    "    -v: Print version information.\n"                                                                                                                                                             \
    "    -h: Print help information.\n"

namespace Constants {
    const std::size_t minGrade = 150;
    const std::size_t maxGrade = 1;

    const std::string &defaultBureaucratName = "John Smith";
    const std::size_t defaultBureaucratGrade = 42;

    const std::string &defaultFormName = "Sample Form";
    const bool defaultFormSigned = false;
    const std::size_t defaultFormSignGrade = 10;
    const std::size_t defaultFormExecGrade = 20;

    bool forceNoColor = false;
    const std::size_t loggingMaxStringLen = 50;
    const std::string &programVersion = "0.1";
    const std::string &helpText = HELP_TEXT;
} // namespace Constants
