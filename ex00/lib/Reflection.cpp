#include <sstream>
#include <string>
#include <utility>

#include "Logger.hpp"
#include "Reflection.hpp"
#include "Repr.hpp"
#include "Utils.hpp"

using std::swap;

Reflection::~Reflection() CPP98(throw()) CPP23(noexcept) {}
Reflection::Reflection() CPP98(throw()) CPP23(noexcept) : _members() {}
Reflection::Reflection(const Reflection &other) CPP98(throw()) CPP23(noexcept) : _members(other._members) {}
Reflection &Reflection::operator=(Reflection other) CPP98(throw()) CPP23(noexcept) {
    ::swap(*this, other);
    return *this;
}
void Reflection::swap(Reflection &other) CPP98(throw()) CPP23(noexcept) { ::swap(_members, other._members); }
void swap(Reflection &a, Reflection &b) CPP98(throw()) CPP23(noexcept) { a.swap(b); }

const char *Reflection::_class = "";

CPP23([[nodiscard]]) const std::string Reflection::reprStruct(std::string name, Members members) const CPP98(throw()) CPP23(noexcept) {
    std::stringstream out;
    if (Logger::lastInstance().istrace5()) {
        out << "{\"class\":" << Utils::jsonEscape(name);
        for (Members::const_iterator it = members.begin(); it != members.end(); ++it)
            out << ",\"" << it->first << "\":" << (this->*it->second.first)();
        out << "}";
    } else {
        out << kwrd(name) + punct("(");
        int i = 0;
        for (Members::const_iterator it = members.begin(); it != members.end(); ++it) {
            if (i++ != 0)
                out << punct(", ");
            if (Logger::lastInstance().istrace3())
                out << cmt(it->first) << cmt("=");
            out << (this->*it->second.first)();
        }
        out << punct(")");
    }
    return out.str();
}

void Reflection::reflectMember(ReprClosure reprClosure, const char *memberId, const void *memberPtr) CPP98(throw()) CPP23(noexcept) { _members[memberId] = std::make_pair(reprClosure, memberPtr); }

CPP23([[nodiscard]]) std::string Reflection::repr() const CPP98(throw()) CPP23(noexcept) { return reprStruct(getClass(*this), _members); }

CPP23([[nodiscard]]) const std::string Reflection::getClass(const Reflection &) const CPP98(throw()) CPP23(noexcept) { return _class; }
void Reflection::reflect() CPP98(throw()) CPP23(noexcept) {} // empty by default, in case you're inheritin from this class and do
                                                             // the reflection in another (often post-periori, i.e. for another
                                                             // class that does not have reflection) way
