#include <cstddef>
#include <exception>
#include <ostream>
#include <string>
#include <utility>

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

// const std::pair<const std::string &, AForm *(*)(const std::string &)> Intern::_formFactories[] = {std::make_pair(ShrubberyCreationForm::formName, ShrubberyCreationForm::createForm),
//                                                                                                   std::make_pair(RobotomyRequestForm::formName, RobotomyRequestForm::createForm),
//                                                                                                   std::make_pair(PresidentialPardonForm::formName, PresidentialPardonForm::createForm)};

const std::pair<const std::string, AForm *(*)(const std::string &)> Intern::_formFactories[] = {std::make_pair(SHRUBBERY_CREATION_FORM_NAME, ShrubberyCreationForm::createForm),
                                                                                                std::make_pair(ROBOTOMY_REQUEST_FORM_NAME, RobotomyRequestForm::createForm),
                                                                                                std::make_pair(PRESIDENTIAL_PARDON_FORM_NAME, PresidentialPardonForm::createForm)};

CPP23([[nodiscard]]) AForm *Intern::makeForm(const std::string &formName, const std::string &formTarget) const CPP98(throw()) CPP23(noexcept) {
    CPP23(constexpr) std::size_t nForms = sizeof(_formFactories) / sizeof(_formFactories[0]);
    std::size_t i = 0;
    for (; i < nForms; ++i) {
        if (_formFactories[i].first == formName) {
            try {
                return _formFactories[i].second(formTarget);
            } catch (const std::exception &e) {
                Logger::lastInstance().warning() << "Intern can't create form because an exception occured during form creation: " << e.what() << std::endl;
                return NULL;
            }
        }
    }
    Logger::lastInstance().warning() << "Intern can't create form with invalid name " << repr(formName) << std::endl;
    return NULL;
}
