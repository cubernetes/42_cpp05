#include <algorithm>
#include <cstddef>
#include <ostream>
#include <stdexcept>
#include <string>

#include "AForm.hpp"
#include "Ansi.hpp"
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
static std::size_t &throwIfGradeOutOfBounds(std::size_t &grade) CPP98(throw(Bureaucrat::GradeTooHighException, Bureaucrat::GradeTooLowException)) CPP23(noexcept(false)) {
    if (grade > Constants::minGrade)
        throw Bureaucrat::GradeTooLowException(grade);
    else if (grade < Constants::maxGrade)
        throw Bureaucrat::GradeTooHighException(grade);
    return grade;
}

void Bureaucrat::trace_arg_ctor1(const std::string &name, std::size_t grade) CPP98(throw()) CPP23(noexcept) { TRACE_ARG_CTOR_STATIC(const std::string, name, std::size_t, grade); }

void Bureaucrat::trace_default_ctor() CPP98(throw()) CPP23(noexcept) { TRACE_DEFAULT_CTOR_STATIC; }

void Bureaucrat::trace_copy_ctor() CPP98(throw()) CPP23(noexcept) { TRACE_COPY_CTOR_STATIC; }

// @throws: Bureaucrat::GradeTooHighException, Bureaucrat::GradeTooLowException
Bureaucrat::Bureaucrat() CPP98(throw(Bureaucrat::GradeTooHighException, Bureaucrat::GradeTooLowException)) CPP23(noexcept(false)) try
    : Reflection(), _name((trace_default_ctor(), Constants::defaultBureaucratName)), _grade(throwIfGradeOutOfBounds(const_cast<std::size_t &>(Constants::defaultBureaucratGrade))),
      log(Logger::lastInstance()) {
    reflect();
} catch (...) {
    Logger::lastInstance().error() << "Failed to default-construct Bureaucrat due to exception in member variable initialization" << std::endl;
    throw;
}

// @throws: Bureaucrat::GradeTooHighException, Bureaucrat::GradeTooLowException
Bureaucrat::Bureaucrat(const std::string &name, std::size_t grade, Logger &_log) CPP98(throw(Bureaucrat::GradeTooHighException, Bureaucrat::GradeTooLowException)) CPP23(noexcept(false)) try
    : Reflection(), _name((trace_arg_ctor1(name, grade), name)), _grade(throwIfGradeOutOfBounds(grade)), log(_log) {
    reflect();
} catch (...) {
    Logger::lastInstance().error() << "Failed to construct Bureaucrat due to exception in member variable initialization" << std::endl;
    throw;
}

// @throws: Bureaucrat::GradeTooHighException, Bureaucrat::GradeTooLowException
Bureaucrat::Bureaucrat(const Bureaucrat &other) CPP98(throw(Bureaucrat::GradeTooHighException, Bureaucrat::GradeTooLowException)) CPP23(noexcept(false)) try
    : Reflection(other), _name((trace_copy_ctor(), other._name)), _grade(throwIfGradeOutOfBounds(const_cast<std::size_t &>(other._grade))), log(other.log) {
    reflect();
} catch (...) {
    Logger::lastInstance().error() << "Failed to copy-constructor Bureaucrat due to exception in member variable initialization" << std::endl;
    throw;
}

CPP23([[nodiscard]]) Bureaucrat &Bureaucrat::operator=(Bureaucrat other) CPP98(throw()) CPP23(noexcept) {
    TRACE_COPY_ASSIGN_OP;
    ::swap(*this, other);
    return *this;
}

CPP23(constexpr)
void Bureaucrat::swap(Bureaucrat &other) CPP98(throw()) CPP23(noexcept) {
    ::swap(_name, other._name);
    ::swap(_grade, other._grade);
}

CPP23(constexpr)
void swap(Bureaucrat &lhs, Bureaucrat &rhs) CPP98(throw()) CPP23(noexcept) { lhs.swap(rhs); }
CPP23([[nodiscard]]) const std::string Bureaucrat::getClass(const Reflection &) const CPP98(throw()) CPP23(noexcept) { return _class; }

CPP23([[nodiscard]]) const std::string &Bureaucrat::getName() const CPP98(throw()) CPP23(noexcept) { return _name; }
CPP23([[nodiscard]]) const std::size_t &Bureaucrat::getGrade() const CPP98(throw()) CPP23(noexcept) { return _grade; }

// @throws: Bureaucrat::GradeTooHighException
void Bureaucrat::incrementGrade() CPP98(throw(Bureaucrat::GradeTooHighException)) CPP23(noexcept(false)) {
    if (_grade <= Constants::maxGrade)
        throw Bureaucrat::GradeTooHighException(_grade);
    --_grade;
}

// @throws: Bureaucrat::GradeTooLowException
void Bureaucrat::decrementGrade() CPP98(throw(Bureaucrat::GradeTooLowException)) CPP23(noexcept(false)) {
    if (_grade >= Constants::minGrade)
        throw Bureaucrat::GradeTooLowException(_grade);
    ++_grade;
}

void Bureaucrat::signForm(AForm &f) CPP98(throw()) CPP23(noexcept) {
    try {
        f.beSigned(*this);
        log.info() << "Signing success: " << *this << " signed " << f << std::endl;
    } catch (const AForm::GradeTooLowException &e) {
        log.warning() << "Signing failure: " << *this << " could NOT sign " << f << "." << std::endl;
        log.info() << "Signing failure reason: " << ansi::red(e.what()) << std::endl;
    }
}

Bureaucrat::GradeTooHighException::~GradeTooHighException() CPP98(throw()) CPP23(noexcept){};
Bureaucrat::GradeTooHighException::GradeTooHighException(std::size_t grade) CPP98(throw()) CPP23(noexcept)
    : std::range_error("Bureaucrat's grade cannot be set to " + Utils::STR(grade) + ", maximum grade allowed is " + Utils::STR(Constants::maxGrade)) {}

Bureaucrat::GradeTooLowException::~GradeTooLowException() CPP98(throw()) CPP23(noexcept){};
Bureaucrat::GradeTooLowException::GradeTooLowException(std::size_t grade) CPP98(throw()) CPP23(noexcept)
    : std::range_error("Bureaucrat's grade cannot be set to " + Utils::STR(grade) + ", minimum grade allowed is " + Utils::STR(Constants::minGrade)) {}

std::ostream &operator<<(std::ostream &os, const Bureaucrat &val) CPP98(throw()) CPP23(noexcept) { return os << repr(val); }
Logger::StreamWrapper &operator<<(Logger::StreamWrapper &os, const Bureaucrat &val) CPP98(throw()) CPP23(noexcept) { return os << repr(val); }
