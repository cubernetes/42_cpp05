#include <cstdlib>
#include <exception>
#include <iostream>

#include "Ansi.hpp"
#include "Bureaucrat.hpp"
#include "Constants.hpp"
#include "Intern.hpp"
#include "Logger.hpp"
#include "Options.hpp"

int main(int ac, char **av) {
    try {
        Options options(ac, av);
        if (options.printHelp || options.printVersion) {
            std::cout << (options.printHelp ? Constants::helpText : "CPP05 ex03 version " + Constants::programVersion) << std::endl;
            return EXIT_SUCCESS;
        }
        Logger log(std::cerr, options.logLevel);

        Intern intern0;

        Bureaucrat gigachadBureaucrat("Gigachad", 1);
        AForm *form;

        form = intern0.makeForm("Shrubbery Creation Form", "Home");

        if (form) {
            gigachadBureaucrat.signForm(*form);
            gigachadBureaucrat.executeForm(*form);
            delete form;
        }
        log.info << std::endl;

        form = intern0.makeForm("Robotomy Request Form", "Dolores");

        if (form) {
            gigachadBureaucrat.signForm(*form);
            gigachadBureaucrat.executeForm(*form);
            delete form;
        }
        log.info << std::endl;

        form = intern0.makeForm("Presidential Pardon Form", "Aaron Swartz");

        if (form) {
            gigachadBureaucrat.signForm(*form);
            gigachadBureaucrat.executeForm(*form);
            delete form;
        }
        log.info << std::endl;

        form = intern0.makeForm("New 42 Hoodie Request Form", "Kars");

        if (form) {
            gigachadBureaucrat.signForm(*form);
            gigachadBureaucrat.executeForm(*form);
            delete form;
        }
        log.info << std::endl;

        log.debug() << "Exiting" << std::endl;
        return EXIT_SUCCESS;
    } catch (const std::exception &exception) {
        Logger::lastInstance().fatal() << ansi::red(exception.what()) << std::endl;
        return EXIT_FAILURE;
    } catch (...) {
        std::cout << "WHAT" << std::endl;
    }
}
