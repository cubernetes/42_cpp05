#pragma once /* PresidentialPardonForm.hpp */

#include <ostream>
#include <string>

#include "AForm.hpp"
#include "Logger.hpp"
#include "Opt.h"

class PresidentialPardonForm : public AForm {
    static void trace_arg_ctor1(const std::string &target) CPP98(throw()) CPP23(noexcept);
    static void trace_default_ctor() CPP98(throw()) CPP23(noexcept);
    static void trace_copy_ctor() CPP98(throw()) CPP23(noexcept);
    std::string _target;
    static const char *_class;

  public:
    ~PresidentialPardonForm() CPP98(throw()) CPP23(noexcept);
    PresidentialPardonForm() CPP98(throw(PresidentialPardonForm::GradeTooHighException, PresidentialPardonForm::GradeTooLowException)) CPP23(noexcept(false));
    explicit PresidentialPardonForm(const std::string &target) CPP98(throw(PresidentialPardonForm::GradeTooHighException, PresidentialPardonForm::GradeTooLowException)) CPP23(noexcept(false));
    PresidentialPardonForm(const std::string &target, Logger &_log) CPP98(throw(PresidentialPardonForm::GradeTooHighException, PresidentialPardonForm::GradeTooLowException)) CPP23(noexcept(false));
    PresidentialPardonForm(const PresidentialPardonForm &other) CPP98(throw(PresidentialPardonForm::GradeTooHighException, PresidentialPardonForm::GradeTooLowException)) CPP23(noexcept(false));
    CPP23([[nodiscard]]) PresidentialPardonForm &operator=(PresidentialPardonForm other) CPP98(throw()) CPP23(noexcept);
    void swap(PresidentialPardonForm &other) CPP98(throw()) CPP23(noexcept);
    CPP23([[nodiscard]]) std::string repr() CPP98(throw()) CPP23(noexcept override);

    CPP23([[nodiscard]]) const std::string &get_target() const CPP98(throw()) CPP23(noexcept);

    // @throws: AForm::GradeTooLowException
    void _fulfil() const CPP98(throw()) CPP23(noexcept override);

    CPP23([[nodiscard]]) static AForm *createForm(const std::string &target) CPP98(throw()) CPP23(noexcept);
    static const std::string formName;
};

void swap(PresidentialPardonForm &lhs, PresidentialPardonForm &rhs) CPP98(throw()) CPP23(noexcept);

CPP23([[nodiscard]]) std::ostream &operator<<(std::ostream &os, const PresidentialPardonForm &val) CPP98(throw()) CPP23(noexcept);
CPP23([[nodiscard]]) Logger::StreamWrapper &operator<<(Logger::StreamWrapper &os, const PresidentialPardonForm &val) CPP98(throw()) CPP23(noexcept);
