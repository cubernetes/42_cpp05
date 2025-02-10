#include <algorithm>
#include <cstddef>
#include <ostream>
#include <string>

#include "Bureaucrat.hpp"
#include "Constants.hpp"
#include "Logger.hpp"
#include "Opt.h"
#include "Reflection.hpp"
#include "Repr.hpp"

using std::swap;

Bureaucrat::~Bureaucrat() CPP98(throw()) CPP23(noexcept) { TRACE_DTOR; }

Bureaucrat::Bureaucrat() CPP98(throw()) CPP23(noexcept)
    : Reflection(), _name(Constants::defaultBureaucratName), _grade(Constants::defaultBureaucratGrade), log(Logger::lastInstance()) {
    reflect();
    TRACE_DEFAULT_CTOR;
}

Bureaucrat::Bureaucrat(const std::string &name, std::size_t grade, Logger &log) CPP98(throw()) CPP23(noexcept)
    : Reflection(), _name(name), _grade(grade), log(log) {
    reflect();
    TRACE_ARG_CTOR(const std::string, name, std::size_t, grade);
}

Bureaucrat::Bureaucrat(const Bureaucrat &other) CPP98(throw()) CPP23(noexcept)
    : Reflection(other), _name(other._name), _grade(other._grade), log(other.log) {
    reflect();
    TRACE_COPY_CTOR;
}

Bureaucrat &Bureaucrat::operator=(Bureaucrat other) CPP98(throw()) CPP23(noexcept) {
    TRACE_COPY_ASSIGN_OP;
    ::swap(*this, other);
    return *this;
}

CPP23(constexpr) void Bureaucrat::swap(Bureaucrat &other) CPP98(throw()) CPP23(noexcept) {
    ::swap(_name, other._name);
    ::swap(_grade, other._grade);
}

CPP23(constexpr) void swap(Bureaucrat &lhs, Bureaucrat &rhs) CPP98(throw()) CPP23(noexcept) { lhs.swap(rhs); }

CPP23([[nodiscard]]) const std::string &Bureaucrat::getName() const CPP98(throw()) CPP23(noexcept) { return _name; }
CPP23([[nodiscard]]) const std::size_t &Bureaucrat::getGrade() const CPP98(throw()) CPP23(noexcept) { return _grade; }

const char *Bureaucrat::GradeTooHighException::what() const throw() { return "GradeTooHighException"; }
const char *Bureaucrat::GradeTooLowException::what() const throw() { return "GradeTooLowException"; }

std::ostream &operator<<(std::ostream &os, const Bureaucrat &val) CPP98(throw()) CPP23(noexcept) { return os << repr(val); }
Logger::StreamWrapper &operator<<(Logger::StreamWrapper &os, const Bureaucrat &val) CPP98(throw()) CPP23(noexcept) {
    return os << repr(val);
}
