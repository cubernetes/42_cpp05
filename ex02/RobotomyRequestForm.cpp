#include <cstdlib>
#include <ostream>
#include <string>
#include <utility>

#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "Constants.hpp"
#include "Logger.hpp"
#include "Opt.h"
#include "Repr.hpp"
#include "RobotomyRequestForm.hpp"

using std::swap;

const char *RobotomyRequestForm::_class = "RobotomyRequestForm";

void RobotomyRequestForm::trace_arg_ctor1(const std::string &target) CPP98(throw()) CPP23(noexcept) { TRACE_ARG_CTOR_STATIC(const std::string, target); }
void RobotomyRequestForm::trace_default_ctor() CPP98(throw()) CPP23(noexcept) { TRACE_DEFAULT_CTOR_STATIC; }
void RobotomyRequestForm::trace_copy_ctor() CPP98(throw()) CPP23(noexcept) { TRACE_COPY_CTOR_STATIC; }

RobotomyRequestForm::~RobotomyRequestForm() CPP98(throw()) CPP23(noexcept) { TRACE_DTOR; }

// @throws: AForm::GradeTooHighException, AForm::GradeTooLowException
RobotomyRequestForm::RobotomyRequestForm() CPP98(throw(AForm::GradeTooHighException, AForm::GradeTooLowException)) CPP23(noexcept(false)) try
    : AForm((trace_default_ctor(), Constants::robotomyRequestFormName), Constants::defaultShrubberyCreationFormSigned, Constants::robotomyRequestFormSignGrade, Constants::robotomyRequestFormExecGrade,
            Logger::lastInstance()),
      _target(const_cast<std::string &>(Constants::robotomyRequestFormDefaultTarget)) {
} catch (...) {
    Logger::lastInstance().error() << "Failed to default-construct RobotomyRequestForm due to exception in member variable initialization" << std::endl;
    throw;
}

// @throws: AForm::GradeTooHighException, AForm::GradeTooLowException
RobotomyRequestForm::RobotomyRequestForm(const std::string &target) CPP98(throw(AForm::GradeTooHighException, AForm::GradeTooLowException)) CPP23(noexcept(false)) try
    : AForm((trace_arg_ctor1(target), Constants::robotomyRequestFormName), Constants::defaultShrubberyCreationFormSigned, Constants::robotomyRequestFormSignGrade,
            Constants::robotomyRequestFormExecGrade, Logger::lastInstance()),
      _target(const_cast<std::string &>(target)) {
} catch (...) {
    Logger::lastInstance().error() << "Failed to construct RobotomyRequestForm due to exception in member variable initialization" << std::endl;
    throw;
}

// @throws: AForm::GradeTooHighException, AForm::GradeTooLowException
RobotomyRequestForm::RobotomyRequestForm(const std::string &target, Logger &_log) CPP98(throw(AForm::GradeTooHighException, AForm::GradeTooLowException)) CPP23(noexcept(false)) try
    : AForm((trace_arg_ctor1(target), Constants::robotomyRequestFormName), Constants::defaultShrubberyCreationFormSigned, Constants::robotomyRequestFormSignGrade,
            Constants::robotomyRequestFormExecGrade, _log),
      _target(const_cast<std::string &>(target)) {
} catch (...) {
    Logger::lastInstance().error() << "Failed to construct RobotomyRequestForm due to exception in member variable initialization" << std::endl;
    throw;
}

// @throws: AForm::GradeTooHighException, AForm::GradeTooLowException
RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &other) CPP98(throw(AForm::GradeTooHighException, AForm::GradeTooLowException)) CPP23(noexcept(false)) try
    : AForm((trace_copy_ctor(), other)), _target(other._target) {
} catch (...) {
    Logger::lastInstance().error() << "Failed to copy-construct RobotomyRequestForm due to exception in member variable initialization" << std::endl;
    throw;
}

CPP23([[nodiscard]]) RobotomyRequestForm &RobotomyRequestForm::operator=(RobotomyRequestForm other) CPP98(throw()) CPP23(noexcept) {
    TRACE_COPY_ASSIGN_OP;
    ::swap(*this, other);
    return *this;
}

void RobotomyRequestForm::swap(RobotomyRequestForm &other) CPP98(throw()) CPP23(noexcept) {
    TRACE_SWAP_BEGIN;
    ::swap(static_cast<AForm &>(*this), static_cast<AForm &>(other));
    ::swap(_target, other._target);
    TRACE_SWAP_END;
}

void swap(RobotomyRequestForm &lhs, RobotomyRequestForm &rhs) CPP98(throw()) CPP23(noexcept) { lhs.swap(rhs); }

CPP23([[nodiscard]]) std::string RobotomyRequestForm::repr() CPP98(throw()) CPP23(noexcept) { return ::repr(*this); }

CPP23([[nodiscard]]) const std::string &RobotomyRequestForm::get_target() const CPP98(throw()) CPP23(noexcept) { return _target; }

// @throws: AForm::GradeTooLowException
void RobotomyRequestForm::_fulfil() const CPP98(throw()) CPP23(noexcept) {
    log.info() << "Drilling noises..." << std::endl;
    std::srand(static_cast<unsigned int>(std::time(NULL)));
    if (std::rand() % 2)
        log.warning() << "Oh no! Failed to robotomize " << _target << std::endl;
    else
        log.info() << "Successfully robotomized " << _target << std::endl;
}

std::ostream &operator<<(std::ostream &os, const RobotomyRequestForm &val) CPP98(throw()) CPP23(noexcept) { return os << repr(val); }
Logger::StreamWrapper &operator<<(Logger::StreamWrapper &os, const RobotomyRequestForm &val) CPP98(throw()) CPP23(noexcept) { return os << repr(val); }
