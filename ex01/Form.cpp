#include <algorithm>
#include <cstddef>
#include <ostream>
#include <stdexcept>
#include <string>

#include "Bureaucrat.hpp"
#include "Constants.hpp"
#include "Form.hpp"
#include "Logger.hpp"
#include "Opt.h"
#include "Reflection.hpp"
#include "Repr.hpp"
#include "Utils.hpp"

using std::swap;

Form::~Form() CPP98(throw()) CPP23(noexcept) { TRACE_DTOR; }

const char *Form::_class = "Form";

// @throws: Form::GradeTooHighException, Form::GradeTooLowException
CPP23([[nodiscard]]) static std::size_t &throwIfGradeOutOfBounds(std::size_t &grade) CPP98(throw(Form::GradeTooHighException, Form::GradeTooLowException)) CPP23(noexcept(false)) {
    if (grade > Constants::minGrade)
        throw Form::GradeTooLowException(grade, Constants::minGrade);
    else if (grade < Constants::maxGrade)
        throw Form::GradeTooHighException(grade, Constants::maxGrade);
    return grade;
}

void Form::trace_arg_ctor1(const std::string &name, bool signed_, std::size_t signGrade, std::size_t execGrade) CPP98(throw()) CPP23(noexcept) {
    TRACE_ARG_CTOR_STATIC(const std::string, name, bool, signed_, std::size_t, signGrade, std::size_t, execGrade);
}

void Form::trace_default_ctor() CPP98(throw()) CPP23(noexcept) { TRACE_DEFAULT_CTOR_STATIC; }

void Form::trace_copy_ctor() CPP98(throw()) CPP23(noexcept) { TRACE_COPY_CTOR_STATIC; }

// @throws: Form::GradeTooHighException, Form::GradeTooLowException
Form::Form() CPP98(throw(Form::GradeTooHighException, Form::GradeTooLowException)) CPP23(noexcept(false)) try
    : Reflection(), _name((trace_default_ctor(), Constants::defaultBureaucratName)), _signed(Constants::defaultFormSigned),
      _signGrade(throwIfGradeOutOfBounds(const_cast<std::size_t &>(Constants::defaultFormSignGrade))), _execGrade(throwIfGradeOutOfBounds(const_cast<std::size_t &>(Constants::defaultFormExecGrade))),
      log(Logger::lastInstance()) {
    reflect();
} catch (...) {
    Logger::lastInstance().error() << "Failed to default-construct Form due to exception in member variable initialization" << std::endl;
    throw;
}

// @throws: Form::GradeTooHighException, Form::GradeTooLowException
Form::Form(const std::string &name, bool signed_, std::size_t signGrade, std::size_t execGrade, Logger &_log) CPP98(throw(Form::GradeTooHighException, Form::GradeTooLowException))
    CPP23(noexcept(false)) try
    : Reflection(), _name((trace_arg_ctor1(name, signed_, signGrade, execGrade), name)), _signed(signed_), _signGrade(throwIfGradeOutOfBounds(signGrade)),
      _execGrade(throwIfGradeOutOfBounds(execGrade)), log(_log) {
    reflect();
} catch (...) {
    Logger::lastInstance().error() << "Failed to construct Form due to exception in member variable initialization" << std::endl;
    throw;
}

// @throws: Form::GradeTooHighException, Form::GradeTooLowException
Form::Form(const Form &other) CPP98(throw(Form::GradeTooHighException, Form::GradeTooLowException)) CPP23(noexcept(false)) try
    : Reflection(other), _name((trace_copy_ctor(), other._name)), _signed(other._signed), _signGrade(throwIfGradeOutOfBounds(const_cast<std::size_t &>(other._signGrade))),
      _execGrade(throwIfGradeOutOfBounds(const_cast<std::size_t &>(other._execGrade))), log(other.log) {
    reflect();
} catch (...) {
    Logger::lastInstance().error() << "Failed to copy-constructor Form due to exception in member variable initialization" << std::endl;
    throw;
}

CPP23([[nodiscard]]) Form &Form::operator=(Form other) CPP98(throw()) CPP23(noexcept) {
    TRACE_COPY_ASSIGN_OP;
    ::swap(*this, other);
    return *this;
}

CPP23(constexpr) void Form::swap(Form &other) CPP98(throw()) CPP23(noexcept) {
    ::swap(_name, other._name);
    ::swap(_signed, other._signed);
    ::swap(_signGrade, other._signGrade);
    ::swap(_execGrade, other._execGrade);
}

CPP23(constexpr) void swap(Form &lhs, Form &rhs) CPP98(throw()) CPP23(noexcept) { lhs.swap(rhs); }
CPP23([[nodiscard]]) const std::string Form::getClass(const Reflection &) const CPP98(throw()) CPP23(noexcept) { return _class; }

CPP23([[nodiscard]]) const std::string &Form::getName() const CPP98(throw()) CPP23(noexcept) { return _name; }
CPP23([[nodiscard]]) const bool &Form::getSigned() const CPP98(throw()) CPP23(noexcept) { return _signed; }
CPP23([[nodiscard]]) const std::size_t &Form::getSignGrade() const CPP98(throw()) CPP23(noexcept) { return _signGrade; }
CPP23([[nodiscard]]) const std::size_t &Form::getExecGrade() const CPP98(throw()) CPP23(noexcept) { return _execGrade; }

// @throws: Form::GradeTooLowException
void Form::beSigned(const Bureaucrat &bureaucrat) CPP98(throw(Form::GradeTooLowException)) CPP23(noexcept(false)) {
    if (bureaucrat.getGrade() > _signGrade)
        throw Form::GradeTooLowException(bureaucrat.getGrade(), _signGrade);
    _signed = true;
}

Form::GradeTooHighException::~GradeTooHighException() CPP98(throw()) CPP23(noexcept){};
Form::GradeTooHighException::GradeTooHighException(std::size_t grade, std::size_t maxGrade) CPP98(throw()) CPP23(noexcept)
    : std::range_error("Grade is too high: " + Utils::STR(grade) + ", maximum allowed grade is " + Utils::STR(maxGrade)) {}

Form::GradeTooLowException::~GradeTooLowException() CPP98(throw()) CPP23(noexcept){};
Form::GradeTooLowException::GradeTooLowException(std::size_t grade, std::size_t minGrade) CPP98(throw()) CPP23(noexcept)
    : std::range_error("Grade is too low: " + Utils::STR(grade) + ", minimum required grade is " + Utils::STR(minGrade)) {}

std::ostream &operator<<(std::ostream &os, const Form &val) CPP98(throw()) CPP23(noexcept) { return os << repr(val); }
Logger::StreamWrapper &operator<<(Logger::StreamWrapper &os, const Form &val) CPP98(throw()) CPP23(noexcept) { return os << repr(val); }
