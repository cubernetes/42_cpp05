#pragma once /* Intern.hpp */

#include <string>
#include <utility>

#include "AForm.hpp"
#include "Opt.h"

class Intern {
    static const std::pair<const std::string, AForm *(*)(const std::string &)> _formFactories[];
    static const char *_class;

  public:
    ~Intern() CPP98(throw()) CPP23(noexcept);
    Intern() CPP98(throw()) CPP23(noexcept);
    Intern(const Intern &) CPP98(throw()) CPP23(noexcept);
    CPP23([[nodiscard]]) Intern &operator=(const Intern &) CPP98(throw()) CPP23(noexcept);

    CPP23([[nodiscard]]) AForm *makeForm(const std::string &formName, const std::string &formTarget) const CPP98(throw()) CPP23(noexcept);
};
