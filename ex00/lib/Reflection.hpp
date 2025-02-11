#pragma once /* Reflection.hpp */

#include <map>
#include <string>
#include <utility>

class Reflection;

typedef std::string (Reflection::*ReprClosure)() const;
typedef std::pair<ReprClosure, const void *> Member;
typedef std::map<const char *, Member> Members;

class Reflection {
  public:
    // due to -Weffc++
    virtual ~Reflection() {}
    Reflection();
    Reflection(const Reflection &other);
    Reflection &operator=(Reflection other);
    void swap(Reflection &other);

    // set by the REFLECT macro
    static const char *_class;
    virtual const std::string getClass(const Reflection &) const { return _class; }

    // populated by the REFELECT macro
    Members _members;

    // generate a std::string representation of the class from _members by iterating over
    // it and using _memberToString to serialize it member by member
    std::string repr() const;

  protected:
    // is implemented automatically in the derived class by the REFLECT macro from
    // MacroMagic.h
    void reflect() {} // empty by default, in case you're inheritin from this class and do
                      // the reflection in another (often post-periori, i.e. for another
                      // class that does not have reflection) way

    // Each DECL macro from MacroMagic.h will generate 2 functions with deterministic
    // names. One of them is a closure that calls ::repr() for the specific member. The
    // other one is also a closure that calls reflectMember() with the required
    // parameters. The automatically implemented reflect() function (which is also a
    // closure, in a way) in the derived class will call those closures which call
    // reflectMember(), which in turn adds the repr closures to the internal map of
    // member.
    void reflectMember(ReprClosure reprClosure, const char *memberId, const void *memberPtr);

    // return the std::string representation of a member
    std::string _memberToStr(const Member &member) const;

    std::string reprStruct(std::string name, Members members) const;
};
void swap(Reflection &a, Reflection &b) /* noexcept */;

#include "MacroMagic.h" // IWYU pragma: export
#include "Repr.hpp"     // IWYU pragma: export
