#include <ostream>
#include <string>
#include <utility>

#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "Constants.hpp"
#include "Logger.hpp"
#include "Opt.h"
#include "Repr.hpp"
#include "ShrubberyCreationForm.hpp"

using std::swap;

const char *ShrubberyCreationForm::_class = "ShrubberyCreationForm";

void ShrubberyCreationForm::trace_arg_ctor1(const std::string &target) CPP98(throw()) CPP23(noexcept) { TRACE_ARG_CTOR_STATIC(const std::string, target); }
void ShrubberyCreationForm::trace_default_ctor() CPP98(throw()) CPP23(noexcept) { TRACE_DEFAULT_CTOR_STATIC; }
void ShrubberyCreationForm::trace_copy_ctor() CPP98(throw()) CPP23(noexcept) { TRACE_COPY_CTOR_STATIC; }

ShrubberyCreationForm::~ShrubberyCreationForm() CPP98(throw()) CPP23(noexcept) { TRACE_DTOR; }

// @throws: AForm::GradeTooHighException, AForm::GradeTooLowException
ShrubberyCreationForm::ShrubberyCreationForm() CPP98(throw(AForm::GradeTooHighException, AForm::GradeTooLowException)) CPP23(noexcept(false)) try
    : AForm((trace_default_ctor(), Constants::shrubberyCreationFormName), Constants::defaultShrubberyCreationFormSigned, Constants::shrubberyCreationFormSignGrade,
            Constants::shrubberyCreationFormExecGrade, Logger::lastInstance()),
      _target(const_cast<std::string &>(Constants::shrubberyCreationFormDefaultTarget)) {
} catch (...) {
    Logger::lastInstance().error() << "Failed to default-construct ShrubberyCreationForm due to exception in member variable initialization" << std::endl;
    throw;
}

// @throws: AForm::GradeTooHighException, AForm::GradeTooLowException
ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target) CPP98(throw(AForm::GradeTooHighException, AForm::GradeTooLowException)) CPP23(noexcept(false)) try
    : AForm((trace_arg_ctor1(target), Constants::shrubberyCreationFormName), Constants::defaultShrubberyCreationFormSigned, Constants::shrubberyCreationFormSignGrade,
            Constants::shrubberyCreationFormExecGrade, Logger::lastInstance()),
      _target(const_cast<std::string &>(target)) {
} catch (...) {
    Logger::lastInstance().error() << "Failed to construct ShrubberyCreationForm due to exception in member variable initialization" << std::endl;
    throw;
}

// @throws: AForm::GradeTooHighException, AForm::GradeTooLowException
ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target, Logger &_log) CPP98(throw(AForm::GradeTooHighException, AForm::GradeTooLowException)) CPP23(noexcept(false)) try
    : AForm((trace_arg_ctor1(target), Constants::shrubberyCreationFormName), Constants::defaultShrubberyCreationFormSigned, Constants::shrubberyCreationFormSignGrade,
            Constants::shrubberyCreationFormExecGrade, _log),
      _target(const_cast<std::string &>(target)) {
} catch (...) {
    Logger::lastInstance().error() << "Failed to construct ShrubberyCreationForm due to exception in member variable initialization" << std::endl;
    throw;
}

// @throws: AForm::GradeTooHighException, AForm::GradeTooLowException
ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &other) CPP98(throw(AForm::GradeTooHighException, AForm::GradeTooLowException)) CPP23(noexcept(false)) try
    : AForm((trace_copy_ctor(), other)), _target(other._target) {
} catch (...) {
    Logger::lastInstance().error() << "Failed to copy-construct ShrubberyCreationForm due to exception in member variable initialization" << std::endl;
    throw;
}

CPP23([[nodiscard]]) ShrubberyCreationForm &ShrubberyCreationForm::operator=(ShrubberyCreationForm other) CPP98(throw()) CPP23(noexcept) {
    TRACE_COPY_ASSIGN_OP;
    ::swap(*this, other);
    return *this;
}

void ShrubberyCreationForm::swap(ShrubberyCreationForm &other) CPP98(throw()) CPP23(noexcept) {
    TRACE_SWAP_BEGIN;
    ::swap(static_cast<AForm &>(*this), static_cast<AForm &>(other));
    ::swap(_target, other._target);
    TRACE_SWAP_END;
}

void swap(ShrubberyCreationForm &lhs, ShrubberyCreationForm &rhs) CPP98(throw()) CPP23(noexcept) { lhs.swap(rhs); }

CPP23([[nodiscard]]) std::string ShrubberyCreationForm::repr() CPP98(throw()) CPP23(noexcept) { return ::repr(*this); }

CPP23([[nodiscard]]) const std::string &ShrubberyCreationForm::get_target() const CPP98(throw()) CPP23(noexcept) { return _target; }

// @throws: AForm::GradeTooLowException
void ShrubberyCreationForm::_fulfil() const CPP98(throw()) CPP23(noexcept) { log.info() << "Creating file " << _target << "_shrubbery with ASCII tree inside" << std::endl; }

std::ostream &operator<<(std::ostream &os, const ShrubberyCreationForm &val) CPP98(throw()) CPP23(noexcept) { return os << repr(val); }
Logger::StreamWrapper &operator<<(Logger::StreamWrapper &os, const ShrubberyCreationForm &val) CPP98(throw()) CPP23(noexcept) { return os << repr(val); }
