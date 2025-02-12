#include <algorithm>
#include <cstddef>
#include <ostream>
#include <stdexcept>
#include <string>

#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "Constants.hpp"
#include "Logger.hpp"
#include "Opt.h"
#include "Reflection.hpp"
#include "Repr.hpp"
#include "Utils.hpp"

using std::swap;

AForm::~AForm() CPP98(throw()) CPP23(noexcept) { TRACE_DTOR; }

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

// @throws: AForm::GradeTooHighException, AForm::GradeTooLowException
AForm::AForm() CPP98(throw(AForm::GradeTooHighException, AForm::GradeTooLowException)) CPP23(noexcept(false)) try
    : Reflection(), _name((trace_default_ctor(), Constants::defaultBureaucratName)), _signed(Constants::defaultFormSigned),
      _signGrade(throwIfGradeOutOfBounds(const_cast<std::size_t &>(Constants::defaultFormSignGrade))), _execGrade(throwIfGradeOutOfBounds(const_cast<std::size_t &>(Constants::defaultFormExecGrade))),
      log(Logger::lastInstance()) {
    reflect();
} catch (...) {
    Logger::lastInstance().error() << "Failed to default-construct AForm due to exception in member variable initialization" << std::endl;
    throw;
}

// @throws: AForm::GradeTooHighException, AForm::GradeTooLowException
AForm::AForm(const std::string &name, bool signed_, std::size_t signGrade, std::size_t execGrade, Logger &_log) CPP98(throw(AForm::GradeTooHighException, AForm::GradeTooLowException))
    CPP23(noexcept(false)) try
    : Reflection(), _name((trace_arg_ctor1(name, signed_, signGrade, execGrade), name)), _signed(signed_), _signGrade(throwIfGradeOutOfBounds(signGrade)),
      _execGrade(throwIfGradeOutOfBounds(execGrade)), log(_log) {
    reflect();
} catch (...) {
    Logger::lastInstance().error() << "Failed to construct AForm due to exception in member variable initialization" << std::endl;
    throw;
}

// @throws: AForm::GradeTooHighException, AForm::GradeTooLowException
AForm::AForm(const AForm &other) CPP98(throw(AForm::GradeTooHighException, AForm::GradeTooLowException)) CPP23(noexcept(false)) try
    : Reflection(other), _name((trace_copy_ctor(), other._name)), _signed(other._signed), _signGrade(throwIfGradeOutOfBounds(const_cast<std::size_t &>(other._signGrade))),
      _execGrade(throwIfGradeOutOfBounds(const_cast<std::size_t &>(other._execGrade))), log(other.log) {
    reflect();
} catch (...) {
    Logger::lastInstance().error() << "Failed to copy-constructor AForm due to exception in member variable initialization" << std::endl;
    throw;
}

CPP23([[nodiscard]]) AForm &AForm::operator=(AForm other) CPP98(throw()) CPP23(noexcept) {
    TRACE_COPY_ASSIGN_OP;
    ::swap(*this, other);
    return *this;
}

CPP23(constexpr) void AForm::swap(AForm &other) CPP98(throw()) CPP23(noexcept) {
    ::swap(_name, other._name);
    ::swap(_signed, other._signed);
    ::swap(_signGrade, other._signGrade);
    ::swap(_execGrade, other._execGrade);
}

CPP23(constexpr) void swap(AForm &lhs, AForm &rhs) CPP98(throw()) CPP23(noexcept) { lhs.swap(rhs); }
CPP23([[nodiscard]]) const std::string AForm::getClass(const Reflection &) const CPP98(throw()) CPP23(noexcept) { return _class; }

CPP23([[nodiscard]]) const std::string &AForm::getName() const CPP98(throw()) CPP23(noexcept) { return _name; }
CPP23([[nodiscard]]) const bool &AForm::getSigned() const CPP98(throw()) CPP23(noexcept) { return _signed; }
CPP23([[nodiscard]]) const std::size_t &AForm::getSignGrade() const CPP98(throw()) CPP23(noexcept) { return _signGrade; }
CPP23([[nodiscard]]) const std::size_t &AForm::getExecGrade() const CPP98(throw()) CPP23(noexcept) { return _execGrade; }

// @throws: AForm::GradeTooLowException
void AForm::beSigned(const Bureaucrat &b) CPP98(throw(AForm::GradeTooLowException)) CPP23(noexcept(false)) {
    if (b.getGrade() > _signGrade)
        throw AForm::GradeTooLowException(b.getGrade(), _signGrade);
    _signed = true;
}

AForm::GradeTooHighException::~GradeTooHighException() CPP98(throw()) CPP23(noexcept){};
AForm::GradeTooHighException::GradeTooHighException(std::size_t grade, std::size_t maxGrade) CPP98(throw()) CPP23(noexcept)
    : std::range_error("Grade is too high: " + Utils::STR(grade) + ", maximum allowed grade is " + Utils::STR(maxGrade)) {}

AForm::GradeTooLowException::~GradeTooLowException() CPP98(throw()) CPP23(noexcept){};
AForm::GradeTooLowException::GradeTooLowException(std::size_t grade, std::size_t minGrade) CPP98(throw()) CPP23(noexcept)
    : std::range_error("Grade is too low: " + Utils::STR(grade) + ", minimum required grade is " + Utils::STR(minGrade)) {}

std::ostream &operator<<(std::ostream &os, const AForm &val) CPP98(throw()) CPP23(noexcept) { return os << repr(val); }
Logger::StreamWrapper &operator<<(Logger::StreamWrapper &os, const AForm &val) CPP98(throw()) CPP23(noexcept) { return os << repr(val); }
