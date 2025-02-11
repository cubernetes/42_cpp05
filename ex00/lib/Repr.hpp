#pragma once /* Repr.hpp */

#include <ctime>
#include <deque>
#include <iostream>
#include <map>
#include <netinet/in.h>
#include <ostream>
#include <set>
#include <sstream>
#include <string>
#include <sys/poll.h>
#include <utility>
#include <vector>

#include "Ansi.hpp"
#include "Constants.hpp"
#include "Logger.hpp"
#include "Opt.h"
#include "Reflection.hpp"
#include "Utils.hpp"

#define ANSI_FG "41;41;41"
#define ANSI_STR "184;187;38"
#define ANSI_CHR "211;134;155"
#define ANSI_KWRD "250;189;47"
#define ANSI_PUNCT "254;128;25"
#define ANSI_FUNC "184;187;38"
#define ANSI_NUM "211;134;155"
#define ANSI_VAR "235;219;178"
#define ANSI_CMT "146;131;116"

using ansi::rgb;
using ansi::rgbBg;

namespace ReprClr {
    CPP23([[nodiscard]]) std::string str(std::string s) CPP98(throw()) CPP23(noexcept);
    CPP23([[nodiscard]]) std::string chr(std::string s) CPP98(throw()) CPP23(noexcept);
    CPP23([[nodiscard]]) std::string kwrd(std::string s) CPP98(throw()) CPP23(noexcept);
    CPP23([[nodiscard]]) std::string punct(std::string s) CPP98(throw()) CPP23(noexcept);
    CPP23([[nodiscard]]) std::string func(std::string s) CPP98(throw()) CPP23(noexcept);
    CPP23([[nodiscard]]) std::string num(std::string s) CPP98(throw()) CPP23(noexcept);
    CPP23([[nodiscard]]) std::string var(std::string s) CPP98(throw()) CPP23(noexcept);
    CPP23([[nodiscard]]) std::string cmt(std::string s) CPP98(throw()) CPP23(noexcept);
} // namespace ReprClr

using ReprClr::chr;
using ReprClr::cmt;
using ReprClr::func;
using ReprClr::kwrd;
using ReprClr::num;
using ReprClr::punct;
using ReprClr::str;
using ReprClr::var;

CPP23([[nodiscard]]) void reprInit() CPP98(throw()) CPP23(noexcept);
CPP23([[nodiscard]]) void reprDone() CPP98(throw()) CPP23(noexcept);

template <typename T> struct ReprWrapper {
    CPP23([[nodiscard]]) static inline std::string repr(const T &value) CPP98(throw()) CPP23(noexcept) { return value.repr(); }
};

template <class T> CPP23([[nodiscard]]) static inline std::string getClass(const T &v) CPP98(throw()) CPP23(noexcept) {
    (void)v;
    return "(unknown)";
}

// convenience wrapper
template <typename T> CPP23([[nodiscard]]) static inline std::string repr(const T &value) CPP98(throw()) CPP23(noexcept) { return ReprWrapper<T>::repr(value); }

// convenience wrapper for arrays with size
template <typename T> CPP23([[nodiscard]]) static inline std::string reprArr(const T *value, std::size_t size) CPP98(throw()) CPP23(noexcept) {
    std::ostringstream oss;
    if (Logger::lastInstance().istrace5())
        oss << "[";
    else if (Logger::lastInstance().istrace4())
        oss << punct("{");
    else
        oss << punct("[");
    for (std::size_t i = 0; i < size; ++i) {
        if (i != 0) {
            if (Logger::lastInstance().istrace5())
                oss << ", ";
            else
                oss << punct(", ");
        }
        oss << ReprWrapper<T>::repr(value[i]);
    }
    if (Logger::lastInstance().istrace5())
        oss << "]";
    else if (Logger::lastInstance().istrace4())
        oss << punct("}");
    else
        oss << punct("]");
    return oss.str();
}

///// repr partial template specializations

#define INT_REPR(T)                                                                                                                                                                                    \
    template <> struct ReprWrapper<T> {                                                                                                                                                                \
        CPP23([[nodiscard]]) static inline std::string repr(const T &value) CPP98(throw()) CPP23(noexcept) {                                                                                           \
            std::ostringstream oss;                                                                                                                                                                    \
            oss << value;                                                                                                                                                                              \
            if (Logger::lastInstance().istrace5())                                                                                                                                                     \
                return oss.str();                                                                                                                                                                      \
            else                                                                                                                                                                                       \
                return num(oss.str());                                                                                                                                                                 \
        }                                                                                                                                                                                              \
    }

INT_REPR(int);
INT_REPR(short);
INT_REPR(long);
INT_REPR(unsigned int);
INT_REPR(unsigned short);
INT_REPR(unsigned long);
INT_REPR(float);
INT_REPR(double);
INT_REPR(long double);

template <> struct ReprWrapper<bool> {
    CPP23([[nodiscard]]) static inline std::string repr(const bool &value) CPP98(throw()) CPP23(noexcept) {
        if (Logger::lastInstance().istrace5())
            return value ? "true" : "false";
        else
            return num(value ? "true" : "false");
    }
};

template <> struct ReprWrapper<std::string> {
    CPP23([[nodiscard]]) static inline std::string repr(const std::string &value) CPP98(throw()) CPP23(noexcept) {
        if (Logger::lastInstance().istrace5())
            return Utils::jsonEscape(value);
        else {
            if (Logger::lastInstance().istrace4())
                return str(Utils::escapeExceptNlAndTab(value)) + (Logger::lastInstance().istrace4() ? punct("s") : "");
            else if (Logger::lastInstance().istrace2())
                return str(Utils::jsonEscape(value)) + (Logger::lastInstance().istrace4() ? punct("s") : "");
            else // for trace, debug, info, warning, error, fatal -> we don't want to see the
                 // whole (possibly huge) std::string
                return str(Utils::jsonEscape(Utils::ellipsisize(value, Constants::loggingMaxStringLen))) + (Logger::lastInstance().istrace4() ? punct("s") : "");
        }
    }
};

// print generic pointers
template <typename T> struct ReprWrapper<T *> {
    CPP23([[nodiscard]]) static inline std::string repr(const T *const &value) CPP98(throw()) CPP23(noexcept) {
        std::ostringstream oss;
        if (value)
            oss << value;
        else
            oss << num("NULL");
        if (Logger::lastInstance().istrace5())
            return oss.str();
        else
            return num(oss.str());
    }
};

template <> struct ReprWrapper<char *> {
    CPP23([[nodiscard]]) static inline std::string repr(const char *const &value) CPP98(throw()) CPP23(noexcept) {
        if (Logger::lastInstance().istrace5()) {
            if (value)
                return Utils::jsonEscape(value);
            else
                return ReprWrapper<const void *>::repr(value);
        } else {
            if (value) {
                if (Logger::lastInstance().istrace4())
                    return str(Utils::escapeExceptNlAndTab(value));
                else if (Logger::lastInstance().istrace2())
                    return str(Utils::jsonEscape(value));
                else // for trace, debug, info, warning, error, fatal -> we don't want to see
                     // the whole (possibly huge) std::string
                    return str(Utils::jsonEscape(Utils::ellipsisize(value, Constants::loggingMaxStringLen)));
            } else
                return ReprWrapper<const void *>::repr(value);
        }
    }
};

// TODO: @timo: escape for char literal
#define CHAR_REPR(T)                                                                                                                                                                                   \
    template <> struct ReprWrapper<T> {                                                                                                                                                                \
        CPP23([[nodiscard]]) static inline std::string repr(const T &value) CPP98(throw()) CPP23(noexcept) {                                                                                           \
            if (Logger::lastInstance().istrace5())                                                                                                                                                     \
                return std::string("\"") + Utils::jsonEscape(std::string(1, static_cast<char>(value))) + "\"";                                                                                         \
            else                                                                                                                                                                                       \
                return chr(std::string("'") + (value == '\\' ? "\\\\" : value == '\'' ? "\\'" : std::string(1, static_cast<char>(value))) + "'");                                                      \
        }                                                                                                                                                                                              \
    }

CHAR_REPR(char);
CHAR_REPR(unsigned char);
CHAR_REPR(signed char);

#define MAKE_MEMBER_INIT_LIST(_, name) , name()
#define MAKE_DECL(type, name) type name;
#define MAKE_REPR_FN(_, name)                                                                                                                                                                          \
    std::string CAT(repr_, name)() const { return ::repr(name); }
#define MAKE_ASSIGN_GETTER(_, name) singleton.name = value.CAT(get, name)();
#define MAKE_ASSIGN_MEMBER(_, name) singleton.name = value.name;
#define MAKE_REFLECT(_, name) members[#name] = std::make_std::pair(static_cast<ReprClosure>(&ReprWrapper::CAT(repr_, name)), &singleton.name);
#define POST_REFLECT_GETTER(clsId, ...)                                                                                                                                                                \
    CPP23([[nodiscard]]) static inline std::string getClass(const clsId &v) CPP98(throw()) CPP23(noexcept) {                                                                                           \
        (void)v;                                                                                                                                                                                       \
        return #clsId;                                                                                                                                                                                 \
    }                                                                                                                                                                                                  \
    template <> struct ReprWrapper<clsId> : public Reflection {                                                                                                                                        \
        void reflect() CPP98(throw()) CPP23(noexcept) {}                                                                                                                                               \
        ReprWrapper() CPP98(throw()) CPP23(noexcept) : uniqueNameMustComeFirst() FOR_EACH_PAIR(MAKE_MEMBER_INIT_LIST, __VA_ARGS__) {}                                                                  \
        int uniqueNameMustComeFirst;                                                                                                                                                                   \
        FOR_EACH_PAIR(MAKE_DECL, __VA_ARGS__)                                                                                                                                                          \
        FOR_EACH_PAIR(MAKE_REPR_FN, __VA_ARGS__)                                                                                                                                                       \
        CPP23([[nodiscard]]) static inline std::string repr(const clsId &value) CPP98(throw()) CPP23(noexcept) {                                                                                       \
            (void)value;                                                                                                                                                                               \
            static ReprWrapper<clsId> singleton;                                                                                                                                                       \
            FOR_EACH_PAIR(MAKE_ASSIGN_GETTER, __VA_ARGS__)                                                                                                                                             \
            Members members;                                                                                                                                                                           \
            FOR_EACH_PAIR(MAKE_REFLECT, __VA_ARGS__)                                                                                                                                                   \
            return singleton.reprStruct(#clsId, members);                                                                                                                                              \
        }                                                                                                                                                                                              \
    }
#define POST_REFLECT_MEMBER(clsId, ...)                                                                                                                                                                \
    CPP23([[nodiscard]]) static inline std::string getClass(const clsId &v) CPP98(throw()) CPP23(noexcept) {                                                                                           \
        (void)v;                                                                                                                                                                                       \
        return #clsId;                                                                                                                                                                                 \
    }                                                                                                                                                                                                  \
    template <> struct ReprWrapper<clsId> : public Reflection {                                                                                                                                        \
        void reflect() CPP98(throw()) CPP23(noexcept) {}                                                                                                                                               \
        ReprWrapper() CPP98(throw()) CPP23(noexcept) : uniqueNameMustComeFirst() FOR_EACH_PAIR(MAKE_MEMBER_INIT_LIST, __VA_ARGS__) {}                                                                  \
        ReprWrapper(const ReprWrapper &other) CPP98(throw()) CPP23(noexcept) : Reflection(other), uniqueNameMustComeFirst() FOR_EACH_PAIR(MAKE_MEMBER_INIT_LIST, __VA_ARGS__) {}                       \
        ReprWrapper &operator=(const ReprWrapper &) CPP98(throw()) CPP23(noexcept) { return *this; }                                                                                                   \
        int uniqueNameMustComeFirst;                                                                                                                                                                   \
        FOR_EACH_PAIR(MAKE_DECL, __VA_ARGS__)                                                                                                                                                          \
        FOR_EACH_PAIR(MAKE_REPR_FN, __VA_ARGS__)                                                                                                                                                       \
        CPP23([[nodiscard]]) static inline std::string repr(const clsId &value) CPP98(throw()) CPP23(noexcept) {                                                                                       \
            (void)value;                                                                                                                                                                               \
            static ReprWrapper<clsId> singleton;                                                                                                                                                       \
            FOR_EACH_PAIR(MAKE_ASSIGN_MEMBER, __VA_ARGS__)                                                                                                                                             \
            Members members;                                                                                                                                                                           \
            FOR_EACH_PAIR(MAKE_REFLECT, __VA_ARGS__)                                                                                                                                                   \
            return singleton.reprStruct(#clsId, members);                                                                                                                                              \
        }                                                                                                                                                                                              \
    }

// for std::vector
template <typename T> struct ReprWrapper<std::vector<T> > {
    CPP23([[nodiscard]]) static inline std::string repr(const std::vector<T> &value) CPP98(throw()) CPP23(noexcept) {
        std::ostringstream oss;
        if (Logger::lastInstance().istrace5())
            oss << "[";
        else if (Logger::lastInstance().istrace4())
            oss << kwrd("std") + punct("::") + kwrd("std::vector") + punct("{");
        else
            oss << punct("[");
        for (std::size_t i = 0; i < value.size(); ++i) {
            if (i != 0) {
                if (Logger::lastInstance().istrace5())
                    oss << ", ";
                else
                    oss << punct(", ");
            }
            oss << ReprWrapper<T>::repr(value[i]);
        }
        if (Logger::lastInstance().istrace5())
            oss << "]";
        else if (Logger::lastInstance().istrace4())
            oss << punct("}");
        else
            oss << punct("]");
        return oss.str();
    }
};

template <typename T> struct ReprWrapper<std::deque<T> > {
    CPP23([[nodiscard]]) static inline std::string repr(const std::deque<T> &value) CPP98(throw()) CPP23(noexcept) {
        std::ostringstream oss;
        if (Logger::lastInstance().istrace5())
            oss << "[";
        else if (Logger::lastInstance().istrace4())
            oss << kwrd("std") + punct("::") + kwrd("std::deque") + punct("{");
        else
            oss << punct("[");
        for (std::size_t i = 0; i < value.size(); ++i) {
            if (i != 0) {
                if (Logger::lastInstance().istrace5())
                    oss << ", ";
                else
                    oss << punct(", ");
            }
            oss << ReprWrapper<T>::repr(value[i]);
        }
        if (Logger::lastInstance().istrace5())
            oss << "]";
        else if (Logger::lastInstance().istrace4())
            oss << punct("}");
        else
            oss << punct("]");
        return oss.str();
    }
};

// for std::map
template <typename K, typename V> struct ReprWrapper<std::map<K, V> > {
    CPP23([[nodiscard]]) static inline std::string repr(const std::map<K, V> &value) CPP98(throw()) CPP23(noexcept) {
        std::ostringstream oss;
        if (Logger::lastInstance().istrace5())
            oss << "{";
        else if (Logger::lastInstance().istrace4())
            oss << kwrd("std") + punct("::") + kwrd("std::map") + punct("{");
        else
            oss << punct("{");
        int i = 0;
        for (typename std::map<K, V>::const_iterator it = value.begin(); it != value.end(); ++it) {
            if (i != 0) {
                if (Logger::lastInstance().istrace5())
                    oss << ", ";
                else
                    oss << punct(", ");
            }
            oss << ReprWrapper<K>::repr(it->first);
            if (Logger::lastInstance().istrace5())
                oss << ": ";
            else
                oss << punct(": ");
            oss << ReprWrapper<V>::repr(it->second);
            ++i;
        }
        if (Logger::lastInstance().istrace5())
            oss << "}";
        else if (Logger::lastInstance().istrace4())
            oss << punct("}");
        else
            oss << punct("}");
        return oss.str();
    }
};

// for std::map with comparison function
template <typename K, typename V, typename C> struct ReprWrapper<std::map<K, V, C> > {
    CPP23([[nodiscard]]) static inline std::string repr(const std::map<K, V, C> &value) CPP98(throw()) CPP23(noexcept) {
        std::ostringstream oss;
        if (Logger::lastInstance().istrace5())
            oss << "{";
        else if (Logger::lastInstance().istrace4())
            oss << kwrd("std") + punct("::") + kwrd("std::map") + punct("{");
        else
            oss << punct("{");
        int i = 0;
        for (typename std::map<K, V, C>::const_iterator it = value.begin(); it != value.end(); ++it) {
            if (i != 0) {
                if (Logger::lastInstance().istrace5())
                    oss << ", ";
                else
                    oss << punct(", ");
            }
            oss << ReprWrapper<K>::repr(it->first);
            if (Logger::lastInstance().istrace5())
                oss << ": ";
            else
                oss << punct(": ");
            oss << ReprWrapper<V>::repr(it->second);
            ++i;
        }
        if (Logger::lastInstance().istrace5())
            oss << "}";
        else if (Logger::lastInstance().istrace4())
            oss << punct("}");
        else
            oss << punct("}");
        return oss.str();
    }
};

// for std::multimap
template <typename K, typename V> struct ReprWrapper<std::multimap<K, V> > {
    CPP23([[nodiscard]]) static inline std::string repr(const std::multimap<K, V> &value) CPP98(throw()) CPP23(noexcept) {
        std::ostringstream oss;
        if (Logger::lastInstance().istrace5())
            oss << "{";
        else if (Logger::lastInstance().istrace4())
            oss << kwrd("std") + punct("::") + kwrd("std::multimap") + punct("{");
        else
            oss << punct("{");
        int i = 0;
        for (typename std::multimap<K, V>::const_iterator it = value.begin(); it != value.end(); ++it) {
            if (i != 0) {
                if (Logger::lastInstance().istrace5())
                    oss << ", ";
                else
                    oss << punct(", ");
            }
            oss << ReprWrapper<K>::repr(it->first);
            if (Logger::lastInstance().istrace5())
                oss << ": ";
            else
                oss << punct(": ");
            oss << ReprWrapper<V>::repr(it->second);
            ++i;
        }
        if (Logger::lastInstance().istrace5())
            oss << "}";
        else if (Logger::lastInstance().istrace4())
            oss << punct("}");
        else
            oss << punct("}");
        return oss.str();
    }
};

// for std::pair
template <typename F, typename S> struct ReprWrapper<std::pair<F, S> > {
    CPP23([[nodiscard]]) static inline std::string repr(const std::pair<F, S> &value) CPP98(throw()) CPP23(noexcept) {
        std::ostringstream oss;
        if (Logger::lastInstance().istrace5())
            oss << "[";
        else if (Logger::lastInstance().istrace4())
            oss << kwrd("std") + punct("::") + kwrd("std::pair") + punct("(");
        else
            oss << punct("(");
        oss << ReprWrapper<F>::repr(value.first) << (Logger::lastInstance().istrace5() ? ", " : punct(", ")) << ReprWrapper<S>::repr(value.second);
        if (Logger::lastInstance().istrace5())
            oss << "]";
        else
            oss << punct(")");
        return oss.str();
    }
};

// for std::set
template <typename T> struct ReprWrapper<std::set<T> > {
    CPP23([[nodiscard]]) static inline std::string repr(const std::set<T> &value) CPP98(throw()) CPP23(noexcept) {
        std::ostringstream oss;
        if (Logger::lastInstance().istrace5())
            oss << "[";
        else if (Logger::lastInstance().istrace4())
            oss << kwrd("std") + punct("::") + kwrd("std::set") + punct("{");
        else
            oss << punct("{");
        int i = -1;
        for (typename std::set<T>::const_iterator it = value.begin(); it != value.end(); ++it) {
            if (++i != 0) {
                if (Logger::lastInstance().istrace5())
                    oss << ", ";
                else
                    oss << punct(", ");
            }
            oss << ReprWrapper<T>::repr(*it);
        }
        if (Logger::lastInstance().istrace5())
            oss << "]";
        else if (Logger::lastInstance().istrace4())
            oss << punct("}");
        else
            oss << punct("}");
        return oss.str();
    }
};

// to print using `std::cout << ...' or `Logger::StreamWrapper << ...'
template <typename T> static inline std::ostream &operator<<(std::ostream &os, const std::vector<T> &val) CPP98(throw()) CPP23(noexcept) { return os << repr(val); }
template <typename T> static inline std::ostream &operator<<(std::ostream &os, const std::deque<T> &val) CPP98(throw()) CPP23(noexcept) { return os << repr(val); }
template <typename K, typename V> static inline std::ostream &operator<<(std::ostream &os, const std::map<K, V> &val) CPP98(throw()) CPP23(noexcept) { return os << repr(val); }
template <typename K, typename V, typename C> static inline std::ostream &operator<<(std::ostream &os, const std::map<K, V, C> &val) CPP98(throw()) CPP23(noexcept) { return os << repr(val); }
template <typename K, typename V> static inline std::ostream &operator<<(std::ostream &os, const std::multimap<K, V> &val) CPP98(throw()) CPP23(noexcept) { return os << repr(val); }
template <typename F, typename S> static inline std::ostream &operator<<(std::ostream &os, const std::pair<F, S> &val) CPP98(throw()) CPP23(noexcept) { return os << repr(val); }
template <typename T> static inline std::ostream &operator<<(std::ostream &os, const std::set<T> &val) CPP98(throw()) CPP23(noexcept) { return os << repr(val); }

// kinda belongs into Logger, but can't do that because it makes things SUPER ugly
// (circular dependencies and so on) extern stuff
#include <string>

#include "MacroMagic.h"

#define CURRENT_TRACE_STREAM                                                                                                                                                                           \
    (log.istrace5() ? log.trace5() : (log.istrace4() ? log.trace4() : (log.istrace3() ? log.trace3() : (log.istrace2() ? log.trace2() : (log.istrace() ? log.trace() : log.trace())))))

#define TRACE_COPY_ASSIGN_OP                                                                                                                                                                           \
    do {                                                                                                                                                                                               \
        Logger::StreamWrapper &oss = CURRENT_TRACE_STREAM;                                                                                                                                             \
        oss << "Calling copy assignment operator: ";                                                                                                                                                   \
        if (log.istrace5())                                                                                                                                                                            \
            oss << "{\"event\":\"copy assignment operator\",\"other object\":" << ::repr(other) << "}\n";                                                                                              \
        else if (log.istrace2())                                                                                                                                                                       \
            oss << kwrd(getClass(*this)) + punct("& ") + kwrd(getClass(*this)) + punct("::") + func("operator") + punct("=(") << ::repr(other) << punct(")") + '\n';                                   \
        else                                                                                                                                                                                           \
            oss << func("operator") + punct("=(const " + kwrd(getClass(*this)) + "&)") + '\n';                                                                                                         \
    } while (false)

#define TRACE_COPY_CTOR                                                                                                                                                                                \
    do {                                                                                                                                                                                               \
        Logger::StreamWrapper &oss = CURRENT_TRACE_STREAM;                                                                                                                                             \
        oss << "Calling copy constructor: ";                                                                                                                                                           \
        if (log.istrace5())                                                                                                                                                                            \
            oss << "{\"event\":\"copy constructor\",\"other object\":" << ::repr(other) << ",\"this object\":" << ::repr(*this) << "}\n";                                                              \
        else if (log.istrace2())                                                                                                                                                                       \
            oss << kwrd(getClass(*this)) + punct("::") + kwrd(getClass(*this)) + punct("(") << ::repr(other) << punct(") -> ") << ::repr(*this) << '\n';                                               \
        else                                                                                                                                                                                           \
            oss << kwrd(getClass(*this)) + punct("(const ") << kwrd(getClass(*this)) << punct("&)") << '\n';                                                                                           \
    } while (false)

#define GEN_NAMES_FIRST(type, name) << #type << " " << #name

#define GEN_NAMES(type, name) << (log.istrace5() ? ", " : punct(", ")) << #type << " " << #name

#define GEN_REPRS_FIRST(type, name) << (log.istrace2() ? (log.istrace3() ? cmt(#name) : "") + (log.istrace3() ? cmt("=") : "") + ::repr(name) : cmt(std::string(#type) + " " + #name))

#define GEN_REPRS(type, name) << (log.istrace2() ? punct(", ") + (log.istrace3() ? cmt(#name) : "") + (log.istrace3() ? cmt("=") : "") + ::repr(name) : cmt(std::string(", ") + #type + " " + #name))

#define TRACE_ARG_CTOR(...)                                                                                                                                                                            \
    do {                                                                                                                                                                                               \
        Logger::StreamWrapper &oss = CURRENT_TRACE_STREAM;                                                                                                                                             \
        IF(IS_EMPTY(__VA_ARGS__))                                                                                                                                                                      \
        (oss << "Calling default constructor: ", oss << "Calling " << NARG(__VA_ARGS__) / 2 << "-ary constructor: ");                                                                                  \
        if (log.istrace5())                                                                                                                                                                            \
            IF(IS_EMPTY(__VA_ARGS__))                                                                                                                                                                  \
        (oss << "{\"event\":\"default constructor\",\"this object\":" << ::repr(*this) << "}\n",                                                                                                       \
         oss << "{\"event\":\"(" EXPAND(DEFER(GEN_NAMES_FIRST)(HEAD2(__VA_ARGS__))) FOR_EACH_PAIR(GEN_NAMES, TAIL2(__VA_ARGS__)) << ") constructor\",\"this object\":" << ::repr(*this) << "}\n");     \
        else if (log.istrace2()) IF(IS_EMPTY(__VA_ARGS__))(oss << kwrd(getClass(*this)) + punct("() -> ") << ::repr(*this) << '\n',                                                                    \
                                                           oss << kwrd(getClass(*this)) + punct("(") EXPAND(DEFER(GEN_REPRS_FIRST)(HEAD2(__VA_ARGS__))) FOR_EACH_PAIR(GEN_REPRS, TAIL2(__VA_ARGS__))   \
                                                               << punct(") -> ") << ::repr(*this) << '\n');                                                                                            \
        else IF(IS_EMPTY(__VA_ARGS__))(oss << kwrd(getClass(*this)) + punct("()") << '\n',                                                                                                             \
                                       oss << kwrd(getClass(*this)) + punct("(") EXPAND(DEFER(GEN_REPRS_FIRST)(HEAD2(__VA_ARGS__))) FOR_EACH_PAIR(GEN_REPRS, TAIL2(__VA_ARGS__)) << punct(")")         \
                                           << '\n');                                                                                                                                                   \
    } while (false)

#define TRACE_DEFAULT_CTOR TRACE_ARG_CTOR()

#define TRACE_DTOR                                                                                                                                                                                     \
    do {                                                                                                                                                                                               \
        Logger::StreamWrapper &oss = CURRENT_TRACE_STREAM;                                                                                                                                             \
        oss << "Calling destructor: ";                                                                                                                                                                 \
        if (log.istrace5())                                                                                                                                                                            \
            oss << "{\"event\":\"destructor\",\"this object\":" << ::repr(*this) << "}\n";                                                                                                             \
        else if (log.istrace2())                                                                                                                                                                       \
            oss << punct("~") << ::repr(*this) << '\n';                                                                                                                                                \
        else                                                                                                                                                                                           \
            oss << punct("~") + kwrd(getClass(*this)) + punct("()") << '\n';                                                                                                                           \
    } while (false)

#define TRACE_SWAP_BEGIN                                                                                                                                                                               \
    do {                                                                                                                                                                                               \
        Logger::StreamWrapper &oss = CURRENT_TRACE_STREAM;                                                                                                                                             \
        oss << "Starting swap operation: ";                                                                                                                                                            \
        if (log.istrace5()) {                                                                                                                                                                          \
            oss << "{\"event\":\"object swap\",\"this object\":" << ::repr(*this) << ",\"other object\":" << ::repr(other) << "}\n";                                                                   \
        } else if (log.istrace2()) {                                                                                                                                                                   \
            oss << cmt("<Swapping " + std::string(getClass(*this)) + " *this:") + '\n';                                                                                                                \
            oss << ::repr(*this) << '\n';                                                                                                                                                              \
            oss << cmt("with the following" + std::string(getClass(*this)) + "object:") + '\n';                                                                                                        \
            oss << ::repr(other) << '\n';                                                                                                                                                              \
        } else {                                                                                                                                                                                       \
            oss << cmt("<Swapping " + std::string(getClass(*this)) + " with another " + std::string(getClass(*this))) + '\n';                                                                          \
        }                                                                                                                                                                                              \
    } while (false)

#define TRACE_SWAP_END                                                                                                                                                                                 \
    do {                                                                                                                                                                                               \
        Logger::StreamWrapper &oss = CURRENT_TRACE_STREAM;                                                                                                                                             \
        if (!log.istrace5())                                                                                                                                                                           \
            oss << cmt(std::string(getClass(*this)) + " swap done>") + '\n';                                                                                                                           \
    } while (false)

// static trace functions
#define CURRENT_TRACE_STREAM_STATIC                                                                                                                                                                    \
    (Logger::lastInstance().istrace5()                                                                                                                                                                 \
         ? Logger::lastInstance().trace5()                                                                                                                                                             \
         : (Logger::lastInstance().istrace4()                                                                                                                                                          \
                ? Logger::lastInstance().trace4()                                                                                                                                                      \
                : (Logger::lastInstance().istrace3() ? Logger::lastInstance().trace3()                                                                                                                 \
                                                     : (Logger::lastInstance().istrace2() ? Logger::lastInstance().trace2()                                                                            \
                                                                                          : (Logger::lastInstance().istrace() ? Logger::lastInstance().trace() : Logger::lastInstance().trace())))))

#define TRACE_COPY_CTOR_STATIC                                                                                                                                                                         \
    do {                                                                                                                                                                                               \
        Logger::StreamWrapper &oss = CURRENT_TRACE_STREAM_STATIC;                                                                                                                                      \
        oss << "Calling copy constructor: ";                                                                                                                                                           \
        if (Logger::lastInstance().istrace5())                                                                                                                                                         \
            oss << "{\"event\":\"" << _class << "() copy constructor\"}\n";                                                                                                                            \
        else if (Logger::lastInstance().istrace2())                                                                                                                                                    \
            oss << kwrd(_class) + punct("(const ") << kwrd(_class) << punct("&)") << '\n';                                                                                                             \
        else                                                                                                                                                                                           \
            oss << kwrd(_class) + punct("(const ") << kwrd(_class) << punct("&)") << '\n';                                                                                                             \
    } while (false)

#define GEN_NAMES_STATIC(type, name) << (Logger::lastInstance().istrace5() ? ", " : punct(", ")) << #type << " " << #name

#define GEN_REPRS_FIRST_STATIC(type, name)                                                                                                                                                             \
    << (Logger::lastInstance().istrace2() ? (Logger::lastInstance().istrace3() ? cmt(#name) : "") + (Logger::lastInstance().istrace3() ? cmt("=") : "") + ::repr(name)                                 \
                                          : cmt(std::string(#type) + " " + #name))

#define GEN_REPRS_STATIC(type, name)                                                                                                                                                                   \
    << (Logger::lastInstance().istrace2() ? punct(", ") + (Logger::lastInstance().istrace3() ? cmt(#name) : "") + (Logger::lastInstance().istrace3() ? cmt("=") : "") + ::repr(name)                   \
                                          : cmt(std::string(", ") + #type + " " + #name))

#define TRACE_ARG_CTOR_STATIC(...)                                                                                                                                                                     \
    do {                                                                                                                                                                                               \
        Logger::StreamWrapper &oss = CURRENT_TRACE_STREAM_STATIC;                                                                                                                                      \
        IF(IS_EMPTY(__VA_ARGS__))                                                                                                                                                                      \
        (oss << "Calling default constructor: ", oss << "Calling " << NARG(__VA_ARGS__) / 2 << "-ary constructor: ");                                                                                  \
        if (Logger::lastInstance().istrace5())                                                                                                                                                         \
            IF(IS_EMPTY(__VA_ARGS__))                                                                                                                                                                  \
        (oss << "{\"event\":\"" << _class << "() default constructor\"}\n", oss << "{\"event\":\"" << _class                                                                                           \
                                                                                << "(" EXPAND(DEFER(GEN_NAMES_FIRST)(HEAD2(__VA_ARGS__))) FOR_EACH_PAIR(GEN_NAMES_STATIC, TAIL2(__VA_ARGS__)) ") "     \
                                                                                << NARG(__VA_ARGS__) / 2 << "-ary constructor\"}\n");                                                                  \
        else if (Logger::lastInstance().istrace2()) IF(IS_EMPTY(__VA_ARGS__))(                                                                                                                         \
            oss << kwrd(_class) + punct("()") << '\n',                                                                                                                                                 \
            oss << kwrd(_class) + punct("(") EXPAND(DEFER(GEN_REPRS_FIRST_STATIC)(HEAD2(__VA_ARGS__))) FOR_EACH_PAIR(GEN_REPRS_STATIC, TAIL2(__VA_ARGS__)) << punct(")") << '\n');                     \
        else IF(IS_EMPTY(__VA_ARGS__))(oss << kwrd(_class) + punct("()") << '\n',                                                                                                                      \
                                       oss << kwrd(_class) + punct("(") EXPAND(DEFER(GEN_REPRS_FIRST_STATIC)(HEAD2(__VA_ARGS__))) FOR_EACH_PAIR(GEN_REPRS_STATIC, TAIL2(__VA_ARGS__)) << punct(")")    \
                                           << '\n');                                                                                                                                                   \
    } while (false)

#define TRACE_DEFAULT_CTOR_STATIC TRACE_ARG_CTOR_STATIC()

#define TRACE_DTOR_STATIC                                                                                                                                                                              \
    do {                                                                                                                                                                                               \
        Logger::StreamWrapper &oss = CURRENT_TRACE_STREAM_STATIC;                                                                                                                                      \
        oss << "Calling destructor: ";                                                                                                                                                                 \
        if (Logger::lastInstance().istrace5())                                                                                                                                                         \
            oss << "{\"event\":\"" << _class << "() destructor\"}\n";                                                                                                                                  \
        else if (Logger::lastInstance().istrace2())                                                                                                                                                    \
            oss << punct("~") + kwrd(_class) + punct("()") << '\n';                                                                                                                                    \
        else                                                                                                                                                                                           \
            oss << punct("~") + kwrd(_class) + punct("()") << '\n';                                                                                                                                    \
    } while (false)
