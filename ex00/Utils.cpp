#include <bits/types/struct_timeval.h>
#include <cctype>
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>
#include <sys/time.h>

#include "Constants.hpp"
#include "Repr.hpp"
#include "Utils.hpp"

using std::string;

string Utils::replaceAll(string s, const string &search, const string &replace) {
    size_t pos = 0;
    while ((pos = s.find(search, pos)) != string::npos) {
        s.replace(pos, search.length(), replace);
        pos += replace.length();
    }
    return s;
}

string Utils::jsonEscape(const string &s) {
    string replaced = s;
    replaced = Utils::replaceAll(s, "\\", "\\\\");
    replaced = Utils::replaceAll(replaced, "\"", "\\\"");
    replaced = Utils::replaceAll(replaced, "\b", "\\b");
    replaced = Utils::replaceAll(replaced, "\t", "\\t");
    replaced = Utils::replaceAll(replaced, "\n", "\\n");
    replaced = Utils::replaceAll(replaced, "\v", "\\v");
    replaced = Utils::replaceAll(replaced, "\f", "\\f");
    replaced = Utils::replaceAll(replaced, "\r", "\\r");
    return "\"" + replaced + "\"";
}

string Utils::escapeExceptNlAndTab(const string &s) {
    string replaced = s;
    replaced = Utils::replaceAll(s, "\\", "\\\\");
    replaced = Utils::replaceAll(replaced, "\"", "\\\"");
    replaced = Utils::replaceAll(replaced, "\b", "\\b");
    replaced = Utils::replaceAll(replaced, "\v", "\\v");
    replaced = Utils::replaceAll(replaced, "\f", "\\f");
    replaced = Utils::replaceAll(replaced, "\r", "\\r");
    return "\"" + replaced + "\"";
}

string Utils::ellipsisize(const string &str, size_t maxLen) {
    if (str.length() <= maxLen)
        return str;
    else if (maxLen == 2)
        return "..";
    else if (maxLen == 1)
        return ".";
    else if (maxLen == 0)
        return "";
    size_t prefixLen = (maxLen - 2) / 2;
    size_t suffixLen = (maxLen - 3) / 2;
    return str.substr(0, prefixLen + 1) + "..." + str.substr(str.length() - suffixLen);
}

string Utils::millisecondRemainderSinceEpoch() {
    int millisec;
    struct timeval tv;

    // TODO: use clock_gettime() instead
    ::gettimeofday(&tv, NULL);

    millisec = static_cast<int>(std::floor(static_cast<double>(tv.tv_usec) / 1000 + .5)); // Round to nearest millisec
    if (millisec >= 1000) {                                                               // Allow for rounding up to nearest second
        millisec -= 1000;
        tv.tv_sec++;
    }

    // ignore tv.tv_sec
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(3) << millisec;
    return oss.str();
}

string Utils::formattedTimestamp(std::time_t _t, bool forLogger) {
    std::time_t t;
    char date[BUFSIZ];
    char time[BUFSIZ];

    if (_t == 0)
        t = std::time(NULL);
    else
        t = _t;
    if (forLogger) {
        if (std::strftime(date, sizeof(date), " %Y-%m-%d ", std::localtime(&t)) &&
            std::strftime(time, sizeof(time), "%H:%M:%S.", std::localtime(&t)))
            return string("[") + cmt(date) + kwrd(time) + kwrd(millisecondRemainderSinceEpoch() + " ") + "] ";
        return "[" + cmt(" N/A date, N/A time ") + "] ";
    } else {
        if (std::strftime(date, sizeof(date), "%Y-%m-%d %H:%M:%S", std::localtime(&t)))
            return date;
        return "1970-01-01 00:00:00";
    }
}
