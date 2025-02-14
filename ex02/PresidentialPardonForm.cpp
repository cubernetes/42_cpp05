#include <cstdlib>
#include <ostream>
#include <string>
#include <utility>

#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "Constants.hpp"
#include "Logger.hpp"
#include "Opt.h"
#include "PresidentialPardonForm.hpp"
#include "Repr.hpp"

using std::swap;

const char *PresidentialPardonForm::_class = "PresidentialPardonForm";

void PresidentialPardonForm::trace_arg_ctor1(const std::string &target) CPP98(throw()) CPP23(noexcept) { TRACE_ARG_CTOR_STATIC(const std::string, target); }
void PresidentialPardonForm::trace_default_ctor() CPP98(throw()) CPP23(noexcept) { TRACE_DEFAULT_CTOR_STATIC; }
void PresidentialPardonForm::trace_copy_ctor() CPP98(throw()) CPP23(noexcept) { TRACE_COPY_CTOR_STATIC; }

PresidentialPardonForm::~PresidentialPardonForm() CPP98(throw()) CPP23(noexcept) { TRACE_DTOR; }

// @throws: AForm::GradeTooHighException, AForm::GradeTooLowException
PresidentialPardonForm::PresidentialPardonForm() CPP98(throw(AForm::GradeTooHighException, AForm::GradeTooLowException)) CPP23(noexcept(false)) try
    : AForm((trace_default_ctor(), Constants::presidentialPardonFormName), Constants::defaultShrubberyCreationFormSigned, Constants::presidentialPardonFormSignGrade,
            Constants::presidentialPardonFormExecGrade, Logger::lastInstance()),
      _target(const_cast<std::string &>(Constants::presidentialPardonFormDefaultTarget)) {
} catch (...) {
    Logger::lastInstance().error() << "Failed to default-construct PresidentialPardonForm due to exception in member variable initialization" << std::endl;
    throw;
}

// @throws: AForm::GradeTooHighException, AForm::GradeTooLowException
PresidentialPardonForm::PresidentialPardonForm(const std::string &target) CPP98(throw(AForm::GradeTooHighException, AForm::GradeTooLowException)) CPP23(noexcept(false)) try
    : AForm((trace_arg_ctor1(target), Constants::presidentialPardonFormName), Constants::defaultShrubberyCreationFormSigned, Constants::presidentialPardonFormSignGrade,
            Constants::presidentialPardonFormExecGrade, Logger::lastInstance()),
      _target(const_cast<std::string &>(target)) {
} catch (...) {
    Logger::lastInstance().error() << "Failed to construct PresidentialPardonForm due to exception in member variable initialization" << std::endl;
    throw;
}

// @throws: AForm::GradeTooHighException, AForm::GradeTooLowException
PresidentialPardonForm::PresidentialPardonForm(const std::string &target, Logger &_log) CPP98(throw(AForm::GradeTooHighException, AForm::GradeTooLowException)) CPP23(noexcept(false)) try
    : AForm((trace_arg_ctor1(target), Constants::presidentialPardonFormName), Constants::defaultShrubberyCreationFormSigned, Constants::presidentialPardonFormSignGrade,
            Constants::presidentialPardonFormExecGrade, _log),
      _target(const_cast<std::string &>(target)) {
} catch (...) {
    Logger::lastInstance().error() << "Failed to construct PresidentialPardonForm due to exception in member variable initialization" << std::endl;
    throw;
}

// @throws: AForm::GradeTooHighException, AForm::GradeTooLowException
PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm &other) CPP98(throw(AForm::GradeTooHighException, AForm::GradeTooLowException)) CPP23(noexcept(false)) try
    : AForm((trace_copy_ctor(), other)), _target(other._target) {
} catch (...) {
    Logger::lastInstance().error() << "Failed to copy-construct PresidentialPardonForm due to exception in member variable initialization" << std::endl;
    throw;
}

CPP23([[nodiscard]]) PresidentialPardonForm &PresidentialPardonForm::operator=(PresidentialPardonForm other) CPP98(throw()) CPP23(noexcept) {
    TRACE_COPY_ASSIGN_OP;
    ::swap(*this, other);
    return *this;
}

void PresidentialPardonForm::swap(PresidentialPardonForm &other) CPP98(throw()) CPP23(noexcept) {
    TRACE_SWAP_BEGIN;
    ::swap(static_cast<AForm &>(*this), static_cast<AForm &>(other));
    ::swap(_target, other._target);
    TRACE_SWAP_END;
}

void swap(PresidentialPardonForm &lhs, PresidentialPardonForm &rhs) CPP98(throw()) CPP23(noexcept) { lhs.swap(rhs); }

CPP23([[nodiscard]]) std::string PresidentialPardonForm::repr() CPP98(throw()) CPP23(noexcept) { return ::repr(*this); }

CPP23([[nodiscard]]) const std::string &PresidentialPardonForm::get_target() const CPP98(throw()) CPP23(noexcept) { return _target; }

// @throws: AForm::GradeTooLowException
void PresidentialPardonForm::_fulfil() const CPP98(throw()) CPP23(noexcept) { log.info() << _target << " has been pardoned by Zaphod Beeblebrox" << std::endl; }

std::ostream &operator<<(std::ostream &os, const PresidentialPardonForm &val) CPP98(throw()) CPP23(noexcept) { return os << repr(val); }
Logger::StreamWrapper &operator<<(Logger::StreamWrapper &os, const PresidentialPardonForm &val) CPP98(throw()) CPP23(noexcept) { return os << repr(val); }
