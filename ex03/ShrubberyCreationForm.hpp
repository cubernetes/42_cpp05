#pragma once /* ShrubberyCreationForm.hpp */

#include <ostream>
#include <string>

#include "AForm.hpp"
#include "Logger.hpp"
#include "Opt.h"

#define ASCII_TREE                                                                                                                                                                                     \
    "                & &&&&\n"                                                                                                                                                                         \
    "          & & && &&&&& &\n"                                                                                                                                                                       \
    "               &  &&&  &&\n"                                                                                                                                                                      \
    "        &          &/|\\   &\n"                                                                                                                                                                   \
    "       &&&&&        |/&&\n"                                                                                                                                                                       \
    "      &&& &&       |/\n"                                                                                                                                                                          \
    "     &&&& & &     /~\n"                                                                                                                                                                           \
    "      && \\&&&&___/|\\\n"                                                                                                                                                                         \
    "           \\_& \\_/|\\\n"                                                                                                                                                                        \
    "                 /~\\\n"                                                                                                                                                                          \
    "                 /~/                 &&\n"                                                                                                                                                        \
    "                /~\\|                  & &\n"                                                                                                                                                     \
    "                   /~/   \\_/ / _/\\|\\|_&&&&\n"                                                                                                                                                  \
    "                  |/~  / __//    //__/&&&&& &\n"                                                                                                                                                  \
    "                /~|/  /|              &&&&\n"                                                                                                                                                     \
    "                |/~ / _/           & &&&&&\n"                                                                                                                                                     \
    "              /~~                   & &\n"                                                                                                                                                        \
    ":___________./~~~\\.___________:\n"                                                                                                                                                               \
    " \\                           /\n"                                                                                                                                                                \
    "  \\_________________________/\n"                                                                                                                                                                 \
    "  (_)                     (_)\n"

class ShrubberyCreationForm : public AForm {
    static void trace_arg_ctor1(const std::string &target) CPP98(throw()) CPP23(noexcept);
    static void trace_default_ctor() CPP98(throw()) CPP23(noexcept);
    static void trace_copy_ctor() CPP98(throw()) CPP23(noexcept);
    std::string _target;
    static const char *_class;

  public:
    ~ShrubberyCreationForm() CPP98(throw()) CPP23(noexcept);
    ShrubberyCreationForm() CPP98(throw(ShrubberyCreationForm::GradeTooHighException, ShrubberyCreationForm::GradeTooLowException)) CPP23(noexcept(false));
    explicit ShrubberyCreationForm(const std::string &target) CPP98(throw(ShrubberyCreationForm::GradeTooHighException, ShrubberyCreationForm::GradeTooLowException)) CPP23(noexcept(false));
    ShrubberyCreationForm(const std::string &target, Logger &_log) CPP98(throw(ShrubberyCreationForm::GradeTooHighException, ShrubberyCreationForm::GradeTooLowException)) CPP23(noexcept(false));
    ShrubberyCreationForm(const ShrubberyCreationForm &other) CPP98(throw(ShrubberyCreationForm::GradeTooHighException, ShrubberyCreationForm::GradeTooLowException)) CPP23(noexcept(false));
    CPP23([[nodiscard]]) ShrubberyCreationForm &operator=(ShrubberyCreationForm other) CPP98(throw()) CPP23(noexcept);
    void swap(ShrubberyCreationForm &other) CPP98(throw()) CPP23(noexcept);
    CPP23([[nodiscard]]) std::string repr() CPP98(throw()) CPP23(noexcept override);

    CPP23([[nodiscard]]) const std::string &get_target() const CPP98(throw()) CPP23(noexcept);

    // @throws: AForm::GradeTooLowException
    void _fulfil() const CPP98(throw()) CPP23(noexcept override);
};

void swap(ShrubberyCreationForm &lhs, ShrubberyCreationForm &rhs) CPP98(throw()) CPP23(noexcept);

CPP23([[nodiscard]]) std::ostream &operator<<(std::ostream &os, const ShrubberyCreationForm &val) CPP98(throw()) CPP23(noexcept);
CPP23([[nodiscard]]) Logger::StreamWrapper &operator<<(Logger::StreamWrapper &os, const ShrubberyCreationForm &val) CPP98(throw()) CPP23(noexcept);
