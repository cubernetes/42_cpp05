#pragma once /* Reflection.hpp */

#include <map>
#include <string>
#include <utility>

#include "Opt.h"

class Reflection;

typedef std::string (Reflection::*ReprClosure)() const;
typedef std::pair<ReprClosure, const void *> Member;
typedef std::map<const char *, Member> Members;

class Reflection {
  public:
    virtual ~Reflection() CPP98(throw()) CPP23(noexcept);
    Reflection() CPP98(throw()) CPP23(noexcept);
    Reflection(const Reflection &other) CPP98(throw()) CPP23(noexcept);
    Reflection &operator=(Reflection other) CPP98(throw()) CPP23(noexcept);
    void swap(Reflection &other) CPP98(throw()) CPP23(noexcept);

    // set by the REFLECT macro
    static const char *_class;
    CPP23([[nodiscard]]) virtual const std::string getClass(const Reflection &) const CPP98(throw()) CPP23(noexcept);

    // populated by the REFELECT macro
    Members _members;

    // generate a std::string representation of the class from _members
    CPP23([[nodiscard]]) std::string repr() const CPP98(throw()) CPP23(noexcept);

  protected:
    // is implemented automatically in the derived class by the REFLECT macro from
    // MacroMagic.h
    void reflect() CPP98(throw()) CPP23(noexcept);

    // Each DECL macro from MacroMagic.h will generate 2 functions with deterministic
    // names. One of them is a closure that calls ::repr() for the specific member. The
    // other one is also a closure that calls reflectMember() with the required
    // parameters. The automatically implemented reflect() function (which is also a
    // closure, in a way) in the derived class will call those closures which call
    // reflectMember(), which in turn adds the repr closures to the internal map of
    // member.
    void reflectMember(ReprClosure reprClosure, const char *memberId, const void *memberPtr) CPP98(throw()) CPP23(noexcept);

    CPP23([[nodiscard]]) const std::string reprStruct(std::string name, Members members) const CPP98(throw()) CPP23(noexcept);
};
void swap(Reflection &a, Reflection &b) CPP98(throw()) CPP23(noexcept);

#include "MacroMagic.h" // IWYU pragma: export
#include "Repr.hpp"     // IWYU pragma: export
