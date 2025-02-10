#include <algorithm>
#include <cstddef>
#include <ostream>
#include <stdexcept>
#include <string>

#include "Bureaucrat.hpp"
#include "Constants.hpp"
#include "Logger.hpp"
#include "Opt.h"
#include "Reflection.hpp"
#include "Repr.hpp"
#include "Utils.hpp"

using std::swap;

Bureaucrat::~Bureaucrat() CPP98(throw()) CPP23(noexcept) { TRACE_DTOR; }

const char *Bureaucrat::_class = "Bureaucrat";

// @throws: Bureaucrat::GradeTooHighException, Bureaucrat::GradeTooLowException
CPP23([[nodiscard]])
static std::size_t &throwIfGradeOutOfBounds(std::size_t &grade)
    CPP98(throw(Bureaucrat::GradeTooHighException, Bureaucrat::GradeTooLowException)) CPP23(noexcept(false)) {
    if (grade < Constants::bureaucratMinGrade)
        throw Bureaucrat::GradeTooLowException();
    else if (grade > Constants::bureaucratMaxGrade)
        throw Bureaucrat::GradeTooHighException();
    return grade;
}

void Bureaucrat::trace_arg_ctor1(const std::string &name, std::size_t grade) CPP98(throw()) CPP23(noexcept) {
    TRACE_ARG_CTOR_STATIC(const std::string, name, std::size_t, grade);
}

void Bureaucrat::trace_default_ctor() CPP98(throw()) CPP23(noexcept) { TRACE_DEFAULT_CTOR_STATIC; }

void Bureaucrat::trace_copy_ctor() CPP98(throw()) CPP23(noexcept) { TRACE_COPY_CTOR_STATIC; }

// @throws: Bureaucrat::GradeTooHighException, Bureaucrat::GradeTooLowException
Bureaucrat::Bureaucrat() CPP98(throw(Bureaucrat::GradeTooHighException, Bureaucrat::GradeTooLowException)) CPP23(noexcept(false))
    : Reflection(), _name((trace_default_ctor(), Constants::defaultBureaucratName)),
      _grade(throwIfGradeOutOfBounds(const_cast<std::size_t &>(Constants::defaultBureaucratGrade))), log(Logger::lastInstance()) {
    reflect();
    TRACE_DEFAULT_CTOR;
}

// @throws: Bureaucrat::GradeTooHighException, Bureaucrat::GradeTooLowException
Bureaucrat::Bureaucrat(const std::string &name, std::size_t grade, Logger &log)
    CPP98(throw(Bureaucrat::GradeTooHighException, Bureaucrat::GradeTooLowException)) CPP23(noexcept(false)) try
    : Reflection(), _name((trace_arg_ctor1(name, grade), name)), _grade(throwIfGradeOutOfBounds(grade)), log(log) {
    reflect();
} catch (...) {
    throw;
}

// @throws: Bureaucrat::GradeTooHighException, Bureaucrat::GradeTooLowException
Bureaucrat::Bureaucrat(const Bureaucrat &other) CPP98(throw(Bureaucrat::GradeTooHighException, Bureaucrat::GradeTooLowException))
    CPP23(noexcept(false))
    : Reflection(other), _name((trace_copy_ctor(), other._name)), _grade(throwIfGradeOutOfBounds(const_cast<std::size_t &>(other._grade))),
      log(other.log) {
    reflect();
    TRACE_COPY_CTOR;
}

// @throws: Bureaucrat::GradeTooHighException, Bureaucrat::GradeTooLowException
Bureaucrat &Bureaucrat::operator=(Bureaucrat other) CPP98(throw(Bureaucrat::GradeTooHighException, Bureaucrat::GradeTooLowException))
    CPP23(noexcept(false)) {
    TRACE_COPY_ASSIGN_OP;
    ::swap(*this, other);
    return *this;
}

// @throws: Bureaucrat::GradeTooHighException, Bureaucrat::GradeTooLowException
CPP23(constexpr)
void Bureaucrat::swap(Bureaucrat &other) CPP98(throw(Bureaucrat::GradeTooHighException, Bureaucrat::GradeTooLowException))
    CPP23(noexcept(false)) {
    ::swap(_name, other._name);
    ::swap(throwIfGradeOutOfBounds(_grade), throwIfGradeOutOfBounds(other._grade));
}

// @throws: Bureaucrat::GradeTooHighException, Bureaucrat::GradeTooLowException
CPP23(constexpr)
void swap(Bureaucrat &lhs, Bureaucrat &rhs) CPP98(throw(Bureaucrat::GradeTooHighException, Bureaucrat::GradeTooLowException))
    CPP23(noexcept(false)) {
    lhs.swap(rhs);
}

CPP23([[nodiscard]]) const std::string &Bureaucrat::getName() const CPP98(throw()) CPP23(noexcept) { return _name; }
CPP23([[nodiscard]]) const std::size_t &Bureaucrat::getGrade() const CPP98(throw()) CPP23(noexcept) { return _grade; }

// @throws: Bureaucrat::GradeTooHighException
void Bureaucrat::incrementGrade() CPP98(throw(Bureaucrat::GradeTooHighException)) CPP23(noexcept(false)) {
    if (_grade >= Constants::bureaucratMaxGrade)
        throw Bureaucrat::GradeTooHighException();
    ++_grade;
}

// @throws: Bureaucrat::GradeTooLowException
void Bureaucrat::decrementGrade() CPP98(throw(Bureaucrat::GradeTooLowException)) CPP23(noexcept(false)) {
    if (_grade <= Constants::bureaucratMinGrade)
        throw Bureaucrat::GradeTooLowException();
    --_grade;
}

Bureaucrat::GradeTooHighException::~GradeTooHighException() CPP98(throw()) CPP23(noexcept){};
Bureaucrat::GradeTooHighException::GradeTooHighException() CPP98(throw()) CPP23(noexcept)
    : std::range_error("Bureaucrat's grade cannot be higher than " + Utils::STR(Constants::bureaucratMaxGrade)) {}

Bureaucrat::GradeTooLowException::~GradeTooLowException() CPP98(throw()) CPP23(noexcept){};
Bureaucrat::GradeTooLowException::GradeTooLowException() CPP98(throw()) CPP23(noexcept)
    : std::range_error("Bureaucrat's grade cannot be lower than " + Utils::STR(Constants::bureaucratMinGrade)) {}

std::ostream &operator<<(std::ostream &os, const Bureaucrat &val) CPP98(throw()) CPP23(noexcept) { return os << repr(val); }
Logger::StreamWrapper &operator<<(Logger::StreamWrapper &os, const Bureaucrat &val) CPP98(throw()) CPP23(noexcept) {
    return os << repr(val);
}
