#pragma once /* Bureaucrat.hpp */

#include <cstddef>
#include <ostream>
#include <stdexcept>
#include <string>

#include "Logger.hpp"
#include "MacroMagic.h"
#include "Opt.h"
#include "Reflection.hpp"

class Form;

class Bureaucrat : public Reflection {
    REFLECT(Bureaucrat, (std::string, _name), (std::size_t, _grade));
    Logger &log;
    static void trace_arg_ctor1(const std::string &name, std::size_t grade) CPP98(throw()) CPP23(noexcept);
    static void trace_default_ctor() CPP98(throw()) CPP23(noexcept);
    static void trace_copy_ctor() CPP98(throw()) CPP23(noexcept);

  public:
    class GradeTooHighException : public std::range_error {
      public:
        ~GradeTooHighException() CPP98(throw()) CPP23(noexcept);
        GradeTooHighException(std::size_t grade) CPP98(throw()) CPP23(noexcept);
    };
    class GradeTooLowException : public std::range_error {
      public:
        ~GradeTooLowException() CPP98(throw()) CPP23(noexcept);
        GradeTooLowException(std::size_t grade) CPP98(throw()) CPP23(noexcept);
    };

    ~Bureaucrat() CPP98(throw()) CPP23(noexcept);
    Bureaucrat() CPP98(throw(Bureaucrat::GradeTooHighException, Bureaucrat::GradeTooLowException)) CPP23(noexcept(false));
    Bureaucrat(const std::string &name, std::size_t grade, Logger &_log) CPP98(throw(Bureaucrat::GradeTooHighException, Bureaucrat::GradeTooLowException)) CPP23(noexcept(false));
    Bureaucrat(const Bureaucrat &other) CPP98(throw(Bureaucrat::GradeTooHighException, Bureaucrat::GradeTooLowException)) CPP23(noexcept(false));
    CPP23([[nodiscard]]) Bureaucrat &operator=(Bureaucrat other) CPP98(throw()) CPP23(noexcept);
    CPP23(constexpr) void swap(Bureaucrat &other) CPP98(throw()) CPP23(noexcept);
    static const char *_class;
    CPP23([[nodiscard]]) const std::string getClass(const Reflection &) const CPP98(throw()) CPP23(noexcept override);

    CPP23([[nodiscard]]) const std::string &getName() const CPP98(throw()) CPP23(noexcept);
    CPP23([[nodiscard]]) const std::size_t &getGrade() const CPP98(throw()) CPP23(noexcept);

    // @throws: Bureaucrat::GradeTooHighException
    void incrementGrade() CPP98(throw(Bureaucrat::GradeTooHighException)) CPP23(noexcept(false));

    // @throws: Bureaucrat::GradeTooLowException
    void decrementGrade() CPP98(throw(Bureaucrat::GradeTooLowException)) CPP23(noexcept(false));

    void signForm(Form &f) CPP98(throw()) CPP23(noexcept);
};

CPP23(constexpr) void swap(Bureaucrat &lhs, Bureaucrat &rhs) CPP98(throw()) CPP23(noexcept);

std::ostream &operator<<(std::ostream &os, const Bureaucrat &val) CPP98(throw()) CPP23(noexcept);
Logger::StreamWrapper &operator<<(Logger::StreamWrapper &os, const Bureaucrat &val) CPP98(throw()) CPP23(noexcept);
