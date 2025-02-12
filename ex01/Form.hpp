#pragma once /* Form.hpp */

#include <cstddef>
#include <ostream>
#include <stdexcept>
#include <string>

#include "Logger.hpp"
#include "MacroMagic.h"
#include "Opt.h"
#include "Reflection.hpp"

class Bureaucrat;

class Form : public Reflection {
    REFLECT(Form, (std::string, _name), (bool, _signed), (std::size_t, _signGrade), (std::size_t, _execGrade));
    Logger &log;
    static void trace_arg_ctor1(const std::string &name, bool signed_, std::size_t signGrade, std::size_t execGrade) CPP98(throw()) CPP23(noexcept);
    static void trace_default_ctor() CPP98(throw()) CPP23(noexcept);
    static void trace_copy_ctor() CPP98(throw()) CPP23(noexcept);

  public:
    class GradeTooHighException : public std::range_error {
      public:
        ~GradeTooHighException() CPP98(throw()) CPP23(noexcept);
        GradeTooHighException(std::size_t grade, std::size_t maxGrade) CPP98(throw()) CPP23(noexcept);
    };
    class GradeTooLowException : public std::range_error {
      public:
        ~GradeTooLowException() CPP98(throw()) CPP23(noexcept);
        GradeTooLowException(std::size_t grade, std::size_t minGrade) CPP98(throw()) CPP23(noexcept);
    };

    ~Form() CPP98(throw()) CPP23(noexcept);
    Form() CPP98(throw(Form::GradeTooHighException, Form::GradeTooLowException)) CPP23(noexcept(false));
    Form(const std::string &name, bool signed_, std::size_t signGrade, std::size_t execGrade, Logger &_log) CPP98(throw(Form::GradeTooHighException, Form::GradeTooLowException))
        CPP23(noexcept(false));
    Form(const Form &other) CPP98(throw(Form::GradeTooHighException, Form::GradeTooLowException)) CPP23(noexcept(false));
    Form &operator=(Form other) CPP98(throw(Form::GradeTooHighException, Form::GradeTooLowException)) CPP23(noexcept(false));
    CPP23(constexpr)
    void swap(Form &other) CPP98(throw(Form::GradeTooHighException, Form::GradeTooLowException)) CPP23(noexcept(false));
    static const char *_class;
    CPP23([[nodiscard]]) const std::string getClass(const Reflection &) const CPP98(throw()) CPP23(noexcept) CPP23(override);

    CPP23([[nodiscard]]) const std::string &getName() const CPP98(throw()) CPP23(noexcept);
    CPP23([[nodiscard]]) const bool &getSigned() const CPP98(throw()) CPP23(noexcept);
    CPP23([[nodiscard]]) const std::size_t &getSignGrade() const CPP98(throw()) CPP23(noexcept);
    CPP23([[nodiscard]]) const std::size_t &getExecGrade() const CPP98(throw()) CPP23(noexcept);

    // @throws: Form::GradeTooLowException
    void beSigned(const Bureaucrat &b) CPP98(throw(Form::GradeTooLowException)) CPP23(noexcept(false));
};

CPP23(constexpr)
void swap(Form &lhs, Form &rhs) CPP98(throw(Form::GradeTooHighException, Form::GradeTooLowException)) CPP23(noexcept(false));

std::ostream &operator<<(std::ostream &os, const Form &val) CPP98(throw()) CPP23(noexcept);
Logger::StreamWrapper &operator<<(Logger::StreamWrapper &os, const Form &val) CPP98(throw()) CPP23(noexcept);
