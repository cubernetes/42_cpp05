#include <cstddef>
#include <exception>
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

const char *Intern::_class = "Intern";

Intern::~Intern() CPP98(throw()) CPP23(noexcept) { TRACE_DTOR_STATIC; }
Intern::Intern() CPP98(throw()) CPP23(noexcept) { TRACE_DEFAULT_CTOR_STATIC; }
Intern::Intern(const Intern &) CPP98(throw()) CPP23(noexcept) { TRACE_COPY_CTOR_STATIC; }
CPP23([[nodiscard]]) Intern &Intern::operator=(const Intern &) CPP98(throw()) CPP23(noexcept) {
    TRACE_COPY_ASSIGN_OP_STATIC;
    return *this;
}

const std::string Intern::_forms[] = {SHRUBBERY_CREATION_FORM_NAME, ROBOTOMY_REQUEST_FORM_NAME, PRESIDENTIAL_PARDON_FORM_NAME};

CPP23([[nodisacrd]]) AForm *Intern::makeForm(const std::string &formName, const std::string &formTarget) const CPP98(throw()) CPP23(noexcept) {
    CPP23(constexpr) std::size_t nForms = sizeof(_forms) / sizeof(_forms[0]);
    std::size_t i = 0;
    for (; i < nForms; ++i) {
        if (_forms[i] == formName)
            break;
    }
    if (i == nForms) {
        Logger::lastInstance().warning() << "Intern can't create form with invalid name " << repr(formName) << std::endl;
        return NULL;
    }
    try {
        switch (i) {
        case 0:
            Logger::lastInstance().info() << "Intern creates " << SHRUBBERY_CREATION_FORM_NAME << std::endl;
            return new ShrubberyCreationForm(formTarget);
        case 1:
            Logger::lastInstance().info() << "Intern creates " << ROBOTOMY_REQUEST_FORM_NAME << std::endl;
            return new RobotomyRequestForm(formTarget);
        case 2:
            Logger::lastInstance().info() << "Intern creates " << PRESIDENTIAL_PARDON_FORM_NAME << std::endl;
            return new PresidentialPardonForm(formTarget);
        default:
            Logger::lastInstance().warning() << "Intern can't create form because they don't know how to create the form with index " << i << std::endl;
            return NULL;
        }
    } catch (const std::exception &e) {
        Logger::lastInstance().warning() << "Intern can't create form because an exception occured during form creation: " << e.what() << std::endl;
        return NULL;
    }
}
