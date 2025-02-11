#include <stdexcept>
#include <string>

#include "Logger.hpp"
#include "Options.hpp"

static Logger::Level convertStringToLogLevel(const char *str) {
    std::string s(str);
    if (s == "FATAL" || s == "1")
        return Logger::FATAL;
    else if (s == "ERROR" || s == "2")
        return Logger::ERROR;
    else if (s == "WARNING" || s == "3")
        return Logger::WARNING;
    else if (s == "INFO" || s == "4")
        return Logger::INFO;
    else if (s == "DEBUG" || s == "5")
        return Logger::DEBUG;
    else if (s == "TRACE" || s == "6")
        return Logger::TRACE;
    else if (s == "TRACE2" || s == "7")
        return Logger::TRACE2;
    else if (s == "TRACE3" || s == "8")
        return Logger::TRACE3;
    else if (s == "TRACE4" || s == "9")
        return Logger::TRACE4;
    else if (s == "TRACE5" || s == "10")
        return Logger::TRACE5;
    else
        throw std::runtime_error("Option parsing error: Invalid logLevel argument to "
                                 "`-l' option. Run with -h for more information.");
}

Options::Options(int ac, char **av) : printHelp(), printVersion(), logLevel(Logger::INFO) {
    (void)ac;
    ++av;
    while (*av) {
        std::string arg(*av);
        if (arg == "-h")
            printHelp = true;
        else if (arg == "-v")
            printVersion = true;
        else if (arg == "-l") {
            if (av[1]) {
                logLevel = convertStringToLogLevel(av[1]);
                ++av;
            } else {
                throw std::runtime_error("Option parsing error: Excpected loglevel "
                                         "argument to `-l' option. Run with "
                                         "-h for more information.");
            }
        } else if (arg[0] == '-') {
            throw std::runtime_error("Option parsing error: Unknown option: " + arg);
        } else {
            throw std::runtime_error("Option parsing error: program takes no arguments");
        }
        ++av;
    }
}
