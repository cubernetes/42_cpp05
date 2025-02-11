#include <bits/types/struct_timeval.h>
#include <cmath>
#include <cstdio>
#include <ctime>
#include <iostream>
#include <ostream>
#include <string>
#include <unistd.h>

#include "Ansi.hpp"
#include "Logger.hpp"
#include "Opt.h"
#include "Repr.hpp"
#include "Utils.hpp"

// using std::swap;

// clang-format off
const std::string &Logger::fatalPrefix = "[ " + ansi::redBg("FATAL") + "   ] ";
const std::string &Logger::errorPrefix = "[ " + ansi::red("ERROR") + "   ] ";
const std::string &Logger::warningPrefix = "[ " + ansi::yellow("WARNING") + " ] ";
const std::string &Logger::infoPrefix = "[ " + ansi::white("INFO") + "    ] ";
const std::string &Logger::debugPrefix = "[ " + ansi::rgbP("DEBUG", 146, 131, 116) + "   ] ";
const std::string &Logger::tracePrefix = "[ " + ansi::rgbP("TRACE", 111, 97, 91) + "   ] ";
const std::string &Logger::trace2Prefix = "[ " + ansi::rgbP("TRACE2", 111, 97, 91) + "  ] "; // print full objects on construction/destruction
const std::string &Logger::trace3Prefix = "[ " + ansi::rgbP("TRACE3", 111, 97, 91) + "  ] "; // print object parameters as keyword-arguments
const std::string &Logger::trace4Prefix = "[ " + ansi::rgbP("TRACE4", 111, 97, 91) + "  ] "; // print aggregrate types verbosely with std:: prefix any everything
const std::string &Logger::trace5Prefix = "[ " + ansi::rgbP("TRACE5", 111, 97, 91) + "  ] "; // print as json (no color)
// clang-format on

CPP23([[nodiscard]]) bool Logger::isfatal() const CPP98(throw()) CPP23(noexcept) { return FATAL <= logLevel; }
CPP23([[nodiscard]]) bool Logger::iserror() const CPP98(throw()) CPP23(noexcept) { return ERROR <= logLevel; }
CPP23([[nodiscard]]) bool Logger::iswarn() const CPP98(throw()) CPP23(noexcept) { return WARNING <= logLevel; }
CPP23([[nodiscard]]) bool Logger::isinfo() const CPP98(throw()) CPP23(noexcept) { return INFO <= logLevel; }
CPP23([[nodiscard]]) bool Logger::isdebug() const CPP98(throw()) CPP23(noexcept) { return DEBUG <= logLevel; }
CPP23([[nodiscard]]) bool Logger::istrace() const CPP98(throw()) CPP23(noexcept) { return TRACE <= logLevel; }
CPP23([[nodiscard]]) bool Logger::istrace2() const CPP98(throw()) CPP23(noexcept) { return TRACE2 <= logLevel; }
CPP23([[nodiscard]]) bool Logger::istrace3() const CPP98(throw()) CPP23(noexcept) { return TRACE3 <= logLevel; }
CPP23([[nodiscard]]) bool Logger::istrace4() const CPP98(throw()) CPP23(noexcept) { return TRACE4 <= logLevel; }
CPP23([[nodiscard]]) bool Logger::istrace5() const CPP98(throw()) CPP23(noexcept) { return TRACE5 <= logLevel; }

Logger::Logger(std::ostream &_os, Level _logLevel) CPP98(throw()) CPP23(noexcept)
    : os(_os), logLevel(_logLevel), fatal(os, FATAL, logLevel), error(os, ERROR, logLevel), warning(os, WARNING, logLevel), info(os, INFO, logLevel), debug(os, DEBUG, logLevel),
      trace(os, TRACE, logLevel), trace2(os, TRACE2, logLevel), trace3(os, TRACE3, logLevel), trace4(os, TRACE4, logLevel), trace5(os, TRACE5, logLevel) {
    debug() << "Initialized Logger with logLevel: ";
    switch (logLevel) {
    case FATAL:
        debug << fatal.prefix;
        break;
    case ERROR:
        debug << error.prefix;
        break;
    case WARNING:
        debug << warning.prefix;
        break;
    case INFO:
        debug << info.prefix;
        break;
    case DEBUG:
        debug << debug.prefix;
        break;
    case TRACE:
        debug << trace.prefix;
        break;
    case TRACE2:
        debug << trace2.prefix;
        break;
    case TRACE3:
        debug << trace3.prefix;
        break;
    case TRACE4:
        debug << trace4.prefix;
        break;
    case TRACE5:
        debug << trace5.prefix;
        break;
    }
    debug << std::endl;

    (void)lastInstance(this);
}

Logger Logger::fallbackInstance;

CPP23([[nodiscard]]) Logger &Logger::lastInstance(Logger *instance) CPP98(throw()) CPP23(noexcept) {
    static Logger *last_instance = &fallbackInstance;

    if (instance) {
        last_instance = instance;
    }

    return *last_instance;
}

Logger::~Logger() CPP98(throw()) CPP23(noexcept) { (void)lastInstance(&fallbackInstance); }

Logger::Logger() CPP98(throw()) CPP23(noexcept)
    : os(std::cout), logLevel(INFO), fatal(os, FATAL, logLevel), error(os, ERROR, logLevel), warning(os, WARNING, logLevel), info(os, INFO, logLevel), debug(os, DEBUG, logLevel),
      trace(os, TRACE, logLevel), trace2(os, TRACE2, logLevel), trace3(os, TRACE3, logLevel), trace4(os, TRACE4, logLevel), trace5(os, TRACE5, logLevel) {}

Logger::Logger(const Logger &other) CPP98(throw()) CPP23(noexcept)
    : os(other.os), logLevel(other.logLevel), fatal(other.fatal), error(other.error), warning(other.warning), info(other.info), debug(other.debug), trace(other.trace), trace2(other.trace2),
      trace3(other.trace3), trace4(other.trace4), trace5(other.trace5) {}

Logger &Logger::operator=(Logger &other) CPP98(throw()) CPP23(noexcept) {
    (void)other;
    // ::swap(*this, other);
    return *this;
}

void Logger::swap(Logger &other) CPP98(throw()) CPP23(noexcept) {
    (void)other;
    // kinda wrong, but can't swap stream in c++98, so yeah, just to make it compile
}

Logger::StreamWrapper::StreamWrapper(std::ostream &_os, Level _thisLevel, Level &_logLevel) CPP98(throw()) CPP23(noexcept) : prefix(), os(_os), thisLevel(_thisLevel), logLevel(_logLevel) {
    switch (thisLevel) {
    case FATAL:
        prefix = fatalPrefix;
        break;
    case ERROR:
        prefix = errorPrefix;
        break;
    case WARNING:
        prefix = warningPrefix;
        break;
    case INFO:
        prefix = infoPrefix;
        break;
    case DEBUG:
        prefix = debugPrefix;
        break;
    case TRACE:
        prefix = tracePrefix;
        break;
    case TRACE2:
        prefix = trace2Prefix;
        break;
    case TRACE3:
        prefix = trace3Prefix;
        break;
    case TRACE4:
        prefix = trace4Prefix;
        break;
    case TRACE5:
        prefix = trace5Prefix;
        break;
    }
}

CPP23([[nodiscard]]) static std::string formattedPid() CPP98(throw()) CPP23(noexcept) { return "[" + cmt(" ") + repr(getpid()) + cmt(" ") + "] "; }

Logger::StreamWrapper &Logger::StreamWrapper::operator()(bool printPrefix) CPP98(throw()) CPP23(noexcept) {
    if (printPrefix)
        return *this << prefix << Utils::formattedTimestamp(0, true) << formattedPid();
    else
        return *this;
}

Logger::StreamWrapper &Logger::StreamWrapper::operator<<(std::ostream &(*manip)(std::ostream &)) CPP98(throw()) CPP23(noexcept) {
    if (thisLevel <= logLevel) {
        os << manip;
    }
    return *this;
}

void swap(Logger &a, Logger &b) CPP98(throw()) CPP23(noexcept) { a.swap(b); }
