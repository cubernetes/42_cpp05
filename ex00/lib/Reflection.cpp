#include <sstream>
#include <string>
#include <utility>

#include "Logger.hpp"
#include "Reflection.hpp"
#include "Repr.hpp"
#include "Utils.hpp"

using std::swap;

Reflection::Reflection() : _members() {}
Reflection::Reflection(const Reflection &other) : _members(other._members) {}
Reflection &Reflection::operator=(Reflection other) {
    ::swap(*this, other);
    return *this;
}
void Reflection::swap(Reflection &other) /* noexcept */ { ::swap(_members, other._members); }
void swap(Reflection &a, Reflection &b) { a.swap(b); }

const char *Reflection::_class = "";

std::string Reflection::reprStruct(std::string name, Members members) const {
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

void Reflection::reflectMember(ReprClosure reprClosure, const char *memberId, const void *memberPtr) { _members[memberId] = std::make_pair(reprClosure, memberPtr); }

std::string Reflection::repr() const { return reprStruct(getClass(*this), _members); }
