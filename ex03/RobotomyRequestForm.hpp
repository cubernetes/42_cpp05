#pragma once /* RobotomyRequestForm.hpp */

#include <ostream>
#include <string>

#include "AForm.hpp"
#include "Logger.hpp"
#include "Opt.h"

class RobotomyRequestForm : public AForm {
    static void trace_arg_ctor1(const std::string &target) CPP98(throw()) CPP23(noexcept);
    static void trace_default_ctor() CPP98(throw()) CPP23(noexcept);
    static void trace_copy_ctor() CPP98(throw()) CPP23(noexcept);
    std::string _target;
    static const char *_class;

  public:
    ~RobotomyRequestForm() CPP98(throw()) CPP23(noexcept);
    RobotomyRequestForm() CPP98(throw(RobotomyRequestForm::GradeTooHighException, RobotomyRequestForm::GradeTooLowException)) CPP23(noexcept(false));
    explicit RobotomyRequestForm(const std::string &target) CPP98(throw(RobotomyRequestForm::GradeTooHighException, RobotomyRequestForm::GradeTooLowException)) CPP23(noexcept(false));
    RobotomyRequestForm(const std::string &target, Logger &_log) CPP98(throw(RobotomyRequestForm::GradeTooHighException, RobotomyRequestForm::GradeTooLowException)) CPP23(noexcept(false));
    RobotomyRequestForm(const RobotomyRequestForm &other) CPP98(throw(RobotomyRequestForm::GradeTooHighException, RobotomyRequestForm::GradeTooLowException)) CPP23(noexcept(false));
    CPP23([[nodiscard]]) RobotomyRequestForm &operator=(RobotomyRequestForm other) CPP98(throw()) CPP23(noexcept);
    void swap(RobotomyRequestForm &other) CPP98(throw()) CPP23(noexcept);
    CPP23([[nodiscard]]) std::string repr() CPP98(throw()) CPP23(noexcept override);

    CPP23([[nodiscard]]) const std::string &get_target() const CPP98(throw()) CPP23(noexcept);

    // @throws: AForm::GradeTooLowException
    void _fulfil() const CPP98(throw()) CPP23(noexcept override);
};

void swap(RobotomyRequestForm &lhs, RobotomyRequestForm &rhs) CPP98(throw()) CPP23(noexcept);

CPP23([[nodiscard]]) std::ostream &operator<<(std::ostream &os, const RobotomyRequestForm &val) CPP98(throw()) CPP23(noexcept);
CPP23([[nodiscard]]) Logger::StreamWrapper &operator<<(Logger::StreamWrapper &os, const RobotomyRequestForm &val) CPP98(throw()) CPP23(noexcept);
