#pragma once /* Bureaucrat.hpp */

#include <cstddef>
#include <ostream>
#include <stdexcept>
#include <string>

#include "Logger.hpp"
#include "MacroMagic.h"
#include "Opt.h"
#include "Reflection.hpp"

class Bureaucrat : public Reflection {
    REFLECT(Bureaucrat, (std::string, _name), (std::size_t, _grade));
    Logger &log;

  public:
    ~Bureaucrat() CPP98(throw()) CPP23(noexcept);
    Bureaucrat() CPP98(throw()) CPP23(noexcept);
    Bureaucrat(const std::string &name, size_t grade, Logger &log) CPP98(throw()) CPP23(noexcept);
    Bureaucrat(const Bureaucrat &) CPP98(throw()) CPP23(noexcept);
    Bureaucrat &operator=(Bureaucrat) CPP98(throw()) CPP23(noexcept);
    CPP23(constexpr) void swap(Bureaucrat &other) CPP98(throw()) CPP23(noexcept);

    CPP23([[nodiscard]]) const std::string &getName() const CPP98(throw()) CPP23(noexcept);
    CPP23([[nodiscard]]) const size_t &getGrade() const CPP98(throw()) CPP23(noexcept);

    class GradeTooHighException : public std::range_error {
      public:
        const char *what() const CPP98(throw()) CPP23(noexcept);
    };
    class GradeTooLowException : public std::range_error {
      public:
        const char *what() const CPP98(throw()) CPP23(noexcept);
    };
};

CPP23(constexpr) void swap(Bureaucrat &lhs, Bureaucrat &rhs) CPP98(throw()) CPP23(noexcept);

std::ostream &operator<<(std::ostream &os, const Bureaucrat &val) CPP98(throw()) CPP23(noexcept);
Logger::StreamWrapper &operator<<(Logger::StreamWrapper &os, const Bureaucrat &val) CPP98(throw()) CPP23(noexcept);
