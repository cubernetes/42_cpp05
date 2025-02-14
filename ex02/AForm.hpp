#pragma once /* AForm.hpp */

#include <cstddef>
#include <ostream>
#include <stdexcept>
#include <string>

#include "Logger.hpp"
#include "Opt.h"

class Bureaucrat;

class AForm {
    static void trace_arg_ctor1(const std::string &name, bool signed_, std::size_t signGrade, std::size_t execGrade) CPP98(throw()) CPP23(noexcept);
    static void trace_default_ctor() CPP98(throw()) CPP23(noexcept);
    static void trace_copy_ctor() CPP98(throw()) CPP23(noexcept);
    static const char *_class;

  protected:
    std::string _name;
    bool _signed;
    std::size_t _signGrade;
    std::size_t _execGrade;
    Logger &log;

    // NOTE: NOT pure virtual since we're adopting the copy-swap idiom throughout, which disallows pure functions and relies on object slicing.
    // Going the other route would require inconsistent derived-class implementations (needlessly mixing copy-swap implementation with other copy assignment code)
    // and you would lose the strong exception guarantee, although arguably needless in this project. This project is for learning anyways, so whatever.
    // Note that AForm::_fulfil specifically calls std::terminate. Derived classes must overwrite this method
    virtual void _fulfil() const CPP98(throw()) CPP23(noexcept);

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
    class FormNotSignedException : public std::logic_error {
      public:
        ~FormNotSignedException() CPP98(throw()) CPP23(noexcept);
        FormNotSignedException(const std::string &name) CPP98(throw()) CPP23(noexcept);
    };

    virtual ~AForm() CPP98(throw()) CPP23(noexcept);
    AForm() CPP98(throw(AForm::GradeTooHighException, AForm::GradeTooLowException)) CPP23(noexcept(false));
    AForm(const std::string &name, bool signed_, std::size_t signGrade, std::size_t execGrade) CPP98(throw(AForm::GradeTooHighException, AForm::GradeTooLowException)) CPP23(noexcept(false));
    AForm(const std::string &name, bool signed_, std::size_t signGrade, std::size_t execGrade, Logger &_log) CPP98(throw(AForm::GradeTooHighException, AForm::GradeTooLowException))
        CPP23(noexcept(false));
    AForm(const AForm &other) CPP98(throw(AForm::GradeTooHighException, AForm::GradeTooLowException)) CPP23(noexcept(false));
    CPP23([[nodiscard]]) AForm &operator=(AForm other) CPP98(throw()) CPP23(noexcept);
    void swap(AForm &other) CPP98(throw()) CPP23(noexcept);
    CPP23([[nodiscard]]) virtual std::string repr() CPP98(throw()) CPP23(noexcept);

    CPP23([[nodiscard]]) const std::string &get_name() const CPP98(throw()) CPP23(noexcept);
    CPP23([[nodiscard]]) const bool &get_signed() const CPP98(throw()) CPP23(noexcept);
    CPP23([[nodiscard]]) const std::size_t &get_signGrade() const CPP98(throw()) CPP23(noexcept);
    CPP23([[nodiscard]]) const std::size_t &get_execGrade() const CPP98(throw()) CPP23(noexcept);

    // @throws: AForm::GradeTooLowException
    void beSigned(const Bureaucrat &b) CPP98(throw(AForm::GradeTooLowException)) CPP23(noexcept(false));

    // @throws: AForm::GradeTooLowException, AForm::FormNotSignedException
    void execute(const Bureaucrat &executor) const CPP98(throw(AForm::GradeTooLowException, AForm::FormNotSignedException)) CPP23(noexcept(false));
};

void swap(AForm &lhs, AForm &rhs) CPP98(throw()) CPP23(noexcept);

std::ostream &operator<<(std::ostream &os, const AForm &val) CPP98(throw()) CPP23(noexcept);
Logger::StreamWrapper &operator<<(Logger::StreamWrapper &os, const AForm &val) CPP98(throw()) CPP23(noexcept);
