#include <cstddef>
#include <ostream>
#include <string>

#include "AForm.hpp"
#include "Constants.hpp"
#include "Intern.hpp"
#include "Logger.hpp"
#include "Opt.h"
#include "PresidentialPardonForm.hpp"
#include "Repr.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

Intern::~Intern() CPP98(throw()) CPP23(noexcept) {}
Intern::Intern() CPP98(throw()) CPP23(noexcept) {}
Intern::Intern(const Intern &) CPP98(throw()) CPP23(noexcept) {}
CPP23([[nodiscard]]) Intern &Intern::operator=(const Intern &) CPP98(throw()) CPP23(noexcept) { return *this; }

const std::string Intern::_forms[] = {Constants::shrubberyCreationFormName, Constants::robotomyRequestFormName, Constants::presidentialPardonFormName};

CPP23([[nodisacrd]]) AForm *Intern::makeForm(const std::string &formName, const std::string &formTarget) const CPP98(throw()) CPP23(noexcept) {
    size_t nForms = sizeof(_forms) / sizeof(_forms[0]);
    std::size_t i = 0;
    for (; i < nForms; ++i) {
        if (_forms[i] == formName)
            break;
    }
    if (i == nForms + 1) {
        Logger::lastInstance().warning() << "Intern can't create form with invalid name " << repr(formName) << std::endl;
        return NULL;
    }
    try {
        switch (i) {
        case 0:
            return new ShrubberyCreationForm(formTarget);
        case 1:
            return new RobotomyRequestForm(formTarget);
        case 2:
            return new PresidentialPardonForm(formTarget);
        default:
            return NULL;
        }
    } catch (...) {
        return NULL;
    }
}
