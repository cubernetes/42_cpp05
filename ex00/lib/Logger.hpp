#pragma once /* Logger.hpp */

#include <cstdlib>
#include <iostream>
#include <string>

class Logger {
    std::ostream &os;

  public:
    enum Level { FATAL, ERROR, WARNING, INFO, DEBUG, TRACE, TRACE2, TRACE3, TRACE4, TRACE5 };
    Level logLevel;

    class StreamWrapper {
      public:
        StreamWrapper(std::ostream &_os, Level _thisLevel, Level &_logLevel);
        StreamWrapper &operator()(bool printPrefix = true);

        template <typename T> StreamWrapper &operator<<(const T &value) {
            if (thisLevel <= logLevel) {
                os << value;
            }
            return *this;
        }

        StreamWrapper &operator<<(std::ostream &(*manip)(std::ostream &));
        std::string prefix;

      private:
        std::ostream &os;
        Level thisLevel;
        Level &logLevel;
    };

    ~Logger();
    Logger(std::ostream &_os, Level _logLevel = INFO);
    Logger();
    Logger(const Logger &other);
    Logger &operator=(Logger &other);
    void swap(Logger &other) /* noexcept */;

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

    bool isfatal();
    bool iserror();
    bool iswarn();
    bool isinfo();
    bool isdebug();
    bool istrace();
    bool istrace2();
    bool istrace3();
    bool istrace4();
    bool istrace5();

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
    static Logger &lastInstance(Logger *instance = NULL);
};

void swap(Logger &a, Logger &b) /* noexcept */;
