#include <algorithm>
#include <cstddef>
#include <exception>
#include <ostream>
#include <stdexcept>
#include <string>

#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "Constants.hpp"
#include "Logger.hpp"
#include "Opt.h"
#include "Repr.hpp"
#include "Utils.hpp"

using std::swap;

const char *AForm::_class = "AForm";

// @throws: AForm::GradeTooHighException, AForm::GradeTooLowException
CPP23([[nodiscard]]) static std::size_t &throwIfGradeOutOfBounds(std::size_t &grade) CPP98(throw(AForm::GradeTooHighException, AForm::GradeTooLowException)) CPP23(noexcept(false)) {
    if (grade > Constants::minGrade)
        throw AForm::GradeTooLowException(grade, Constants::minGrade);
    else if (grade < Constants::maxGrade)
        throw AForm::GradeTooHighException(grade, Constants::maxGrade);
    return grade;
}

void AForm::trace_arg_ctor1(const std::string &name, bool signed_, std::size_t signGrade, std::size_t execGrade) CPP98(throw()) CPP23(noexcept) {
    TRACE_ARG_CTOR_STATIC(const std::string, name, bool, signed_, std::size_t, signGrade, std::size_t, execGrade);
}

void AForm::trace_default_ctor() CPP98(throw()) CPP23(noexcept) { TRACE_DEFAULT_CTOR_STATIC; }

void AForm::trace_copy_ctor() CPP98(throw()) CPP23(noexcept) { TRACE_COPY_CTOR_STATIC; }

AForm::~AForm() CPP98(throw()) CPP23(noexcept) { TRACE_DTOR; }

// @throws: AForm::GradeTooHighException, AForm::GradeTooLowException
AForm::AForm() CPP98(throw(AForm::GradeTooHighException, AForm::GradeTooLowException)) CPP23(noexcept(false)) try
    : _name((trace_default_ctor(), const_cast<std::string &>(Constants::defaultBureaucratName))), _signed(Constants::defaultFormSigned),
      _signGrade(throwIfGradeOutOfBounds(const_cast<std::size_t &>(Constants::defaultFormSignGrade))), _execGrade(throwIfGradeOutOfBounds(const_cast<std::size_t &>(Constants::defaultFormExecGrade))),
      log(Logger::lastInstance()) {
} catch (...) {
    Logger::lastInstance().error() << "Failed to default-construct AForm due to exception in member variable initialization" << std::endl;
    throw;
}

// @throws: AForm::GradeTooHighException, AForm::GradeTooLowException
AForm::AForm(const std::string &name, bool signed_, std::size_t signGrade, std::size_t execGrade) CPP98(throw(AForm::GradeTooHighException, AForm::GradeTooLowException)) CPP23(noexcept(false)) try
    : _name((trace_arg_ctor1(name, signed_, signGrade, execGrade), const_cast<std::string &>(name))), _signed(signed_), _signGrade(throwIfGradeOutOfBounds(signGrade)),
      _execGrade(throwIfGradeOutOfBounds(execGrade)), log(Logger::lastInstance()) {
} catch (...) {
    Logger::lastInstance().error() << "Failed to construct AForm due to exception in member variable initialization" << std::endl;
    throw;
}

// @throws: AForm::GradeTooHighException, AForm::GradeTooLowException
AForm::AForm(const std::string &name, bool signed_, std::size_t signGrade, std::size_t execGrade, Logger &_log) CPP98(throw(AForm::GradeTooHighException, AForm::GradeTooLowException))
    CPP23(noexcept(false)) try
    : _name((trace_arg_ctor1(name, signed_, signGrade, execGrade), const_cast<std::string &>(name))), _signed(signed_), _signGrade(throwIfGradeOutOfBounds(signGrade)),
      _execGrade(throwIfGradeOutOfBounds(execGrade)), log(_log) {
} catch (...) {
    Logger::lastInstance().error() << "Failed to construct AForm due to exception in member variable initialization" << std::endl;
    throw;
}

// @throws: AForm::GradeTooHighException, AForm::GradeTooLowException
AForm::AForm(const AForm &other) CPP98(throw(AForm::GradeTooHighException, AForm::GradeTooLowException)) CPP23(noexcept(false)) try
    : _name((trace_copy_ctor(), other._name)), _signed(other._signed), _signGrade(throwIfGradeOutOfBounds(const_cast<std::size_t &>(other._signGrade))),
      _execGrade(throwIfGradeOutOfBounds(const_cast<std::size_t &>(other._execGrade))), log(other.log) {
} catch (...) {
    Logger::lastInstance().error() << "Failed to copy-constructor AForm due to exception in member variable initialization" << std::endl;
    throw;
}

CPP23([[nodiscard]]) AForm &AForm::operator=(AForm other) CPP98(throw()) CPP23(noexcept) {
    TRACE_COPY_ASSIGN_OP;
    ::swap(*this, other);
    return *this;
}

void AForm::swap(AForm &other) CPP98(throw()) CPP23(noexcept) {
    TRACE_SWAP_BEGIN;
    ::swap(_name, other._name);
    ::swap(_signed, other._signed);
    ::swap(_signGrade, other._signGrade);
    ::swap(_execGrade, other._execGrade);
    TRACE_SWAP_END;
}

void swap(AForm &lhs, AForm &rhs) CPP98(throw()) CPP23(noexcept) { lhs.swap(rhs); }

CPP23([[nodiscard]]) std::string AForm::repr() CPP98(throw()) CPP23(noexcept) { return ::repr(*this); }

CPP23([[nodiscard]]) const std::string &AForm::get_name() const CPP98(throw()) CPP23(noexcept) { return _name; }
CPP23([[nodiscard]]) const bool &AForm::get_signed() const CPP98(throw()) CPP23(noexcept) { return _signed; }
CPP23([[nodiscard]]) const std::size_t &AForm::get_signGrade() const CPP98(throw()) CPP23(noexcept) { return _signGrade; }
CPP23([[nodiscard]]) const std::size_t &AForm::get_execGrade() const CPP98(throw()) CPP23(noexcept) { return _execGrade; }

// @throws: AForm::GradeTooLowException
void AForm::beSigned(const Bureaucrat &b) CPP98(throw(AForm::GradeTooLowException)) CPP23(noexcept(false)) {
    if (b.getGrade() > _signGrade)
        throw AForm::GradeTooLowException(b.getGrade(), _signGrade);
    _signed = true;
}

// NOTE: as AForm::_fulfil, it will call std::terminate
void AForm::_fulfil() const CPP98(throw()) CPP23(noexcept) { std::terminate(); }

// @throws: AForm::GradeTooLowException, AForm::FormNotSignedException
void AForm::execute(const Bureaucrat &executor) const CPP98(throw(AForm::GradeTooLowException, AForm::FormNotSignedException)) CPP23(noexcept(false)) {
    if (!_signed)
        throw AForm::FormNotSignedException(_name);
    else if (executor.getGrade() > _execGrade)
        throw AForm::GradeTooLowException(executor.getGrade(), _execGrade);
    _fulfil();
}

CPP23([[nodiscard]]) AForm *AForm::createForm(const std::string &) CPP98(throw()) CPP23(noexcept) { std::terminate(); }
const std::string &AForm::formName = "Abstract Form";

AForm::GradeTooHighException::~GradeTooHighException() CPP98(throw()) CPP23(noexcept) {};
AForm::GradeTooHighException::GradeTooHighException(std::size_t grade, std::size_t maxGrade) CPP98(throw()) CPP23(noexcept)
    : std::range_error("Grade is too high: " + Utils::STR(grade) + ", maximum allowed grade is " + Utils::STR(maxGrade)) {}

AForm::GradeTooLowException::~GradeTooLowException() CPP98(throw()) CPP23(noexcept) {};
AForm::GradeTooLowException::GradeTooLowException(std::size_t grade, std::size_t minGrade) CPP98(throw()) CPP23(noexcept)
    : std::range_error("Grade is too low: " + Utils::STR(grade) + ", minimum required grade is " + Utils::STR(minGrade)) {}

AForm::FormNotSignedException::~FormNotSignedException() CPP98(throw()) CPP23(noexcept) {};
AForm::FormNotSignedException::FormNotSignedException(const std::string &name) CPP98(throw()) CPP23(noexcept) : std::logic_error("Form " + name + " is not signed, cannot execute") {}

std::ostream &operator<<(std::ostream &os, const AForm &val) CPP98(throw()) CPP23(noexcept) { return os << repr(val); }
Logger::StreamWrapper &operator<<(Logger::StreamWrapper &os, const AForm &val) CPP98(throw()) CPP23(noexcept) { return os << repr(val); }
