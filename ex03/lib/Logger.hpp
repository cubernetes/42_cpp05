#pragma once /* Logger.hpp */

#include <cstdlib>
#include <iostream>
#include <string>

#include "Opt.h"

class Logger {
    std::ostream &os;

  public:
    enum Level { FATAL, ERROR, WARNING, INFO, DEBUG, TRACE, TRACE2, TRACE3, TRACE4, TRACE5 };
    Level logLevel;

    class StreamWrapper {
      public:
        StreamWrapper(std::ostream &_os, Level _thisLevel, Level &_logLevel) CPP98(throw()) CPP23(noexcept);
        StreamWrapper &operator()(bool printPrefix = true) CPP98(throw()) CPP23(noexcept);

        template <typename T> StreamWrapper &operator<<(const T &value) CPP98(throw()) CPP23(noexcept) {
            if (thisLevel <= logLevel) {
                os << value;
            }
            return *this;
        }

        StreamWrapper &operator<<(std::ostream &(*manip)(std::ostream &)) CPP98(throw()) CPP23(noexcept);
        std::string prefix;

      private:
        std::ostream &os;
        Level thisLevel;
        Level &logLevel;
    };

    ~Logger() CPP98(throw()) CPP23(noexcept);
    Logger(std::ostream &_os, Level _logLevel = INFO) CPP98(throw()) CPP23(noexcept);
    Logger() CPP98(throw()) CPP23(noexcept);
    Logger(const Logger &other) CPP98(throw()) CPP23(noexcept);
    Logger &operator=(Logger &other) CPP98(throw()) CPP23(noexcept);
    void swap(Logger &other) CPP98(throw()) CPP23(noexcept);

    StreamWrapper fatal;
    StreamWrapper error;
    StreamWrapper warning;
    StreamWrapper info;
    StreamWrapper debug;
    StreamWrapper trace;
    StreamWrapper trace2;
    StreamWrapper trace3;
    StreamWrapper trace4;
    StreamWrapper trace5;

    CPP23([[nodiscard]]) bool isfatal() const CPP98(throw()) CPP23(noexcept);
    CPP23([[nodiscard]]) bool iserror() const CPP98(throw()) CPP23(noexcept);
    CPP23([[nodiscard]]) bool iswarn() const CPP98(throw()) CPP23(noexcept);
    CPP23([[nodiscard]]) bool isinfo() const CPP98(throw()) CPP23(noexcept);
    CPP23([[nodiscard]]) bool isdebug() const CPP98(throw()) CPP23(noexcept);
    CPP23([[nodiscard]]) bool istrace() const CPP98(throw()) CPP23(noexcept);
    CPP23([[nodiscard]]) bool istrace2() const CPP98(throw()) CPP23(noexcept);
    CPP23([[nodiscard]]) bool istrace3() const CPP98(throw()) CPP23(noexcept);
    CPP23([[nodiscard]]) bool istrace4() const CPP98(throw()) CPP23(noexcept);
    CPP23([[nodiscard]]) bool istrace5() const CPP98(throw()) CPP23(noexcept);

    static const std::string &fatalPrefix;
    static const std::string &errorPrefix;
    static const std::string &warningPrefix;
    static const std::string &infoPrefix;
    static const std::string &debugPrefix;
    static const std::string &tracePrefix;
    static const std::string &trace2Prefix;
    static const std::string &trace3Prefix;
    static const std::string &trace4Prefix;
    static const std::string &trace5Prefix;

    static Logger fallbackInstance;
    static Logger &lastInstance(Logger *instance = NULL) CPP98(throw()) CPP23(noexcept);
};

void swap(Logger &a, Logger &b) CPP98(throw()) CPP23(noexcept);
