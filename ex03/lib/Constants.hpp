#pragma once /* Constants.hpp */

#include <cstddef>
#include <string>

#define SHRUBBERY_CREATION_FORM_NAME "Shrubbery Creation Form"
#define ROBOTOMY_REQUEST_FORM_NAME "Robotomy Request Form"
#define PRESIDENTIAL_PARDON_FORM_NAME "Presidential Pardon Form"

namespace Constants {
    extern const std::size_t minGrade;
    extern const std::size_t maxGrade;

    extern const std::string &defaultBureaucratName;
    extern const std::size_t defaultBureaucratGrade;

    extern const std::string &defaultFormName;
    extern const bool defaultFormSigned;
    extern const std::size_t defaultFormSignGrade;
    extern const std::size_t defaultFormExecGrade;

    extern const std::string &shrubberyCreationFormName;
    extern const bool defaultShrubberyCreationFormSigned;
    extern const std::size_t shrubberyCreationFormSignGrade;
    extern const std::size_t shrubberyCreationFormExecGrade;
    extern const std::string &shrubberyCreationFormDefaultTarget;

    extern const std::string &robotomyRequestFormName;
    extern const bool defaultRobotomyRequestFormSigned;
    extern const std::size_t robotomyRequestFormSignGrade;
    extern const std::size_t robotomyRequestFormExecGrade;
    extern const std::string &robotomyRequestFormDefaultTarget;

    extern const std::string &presidentialPardonFormName;
    extern const bool defaultPresidentialPardonFormSigned;
    extern const std::size_t presidentialPardonFormSignGrade;
    extern const std::size_t presidentialPardonFormExecGrade;
    extern const std::string &presidentialPardonFormDefaultTarget;

    extern bool forceNoColor;
    extern const std::size_t loggingMaxStringLen;
    extern const std::string &programVersion;
    extern const std::string &helpText;
} // namespace Constants
