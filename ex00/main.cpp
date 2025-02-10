#include <cstdlib>
#include <exception>
#include <iostream>

#include "Ansi.hpp"
#include "Bureaucrat.hpp"
#include "Constants.hpp"
#include "Logger.hpp"
#include "Options.hpp"

int main(int ac, char **av) {
    try {
        Options options(ac, av);
        if (options.printHelp || options.printVersion) {
            std::cout << (options.printHelp ? Constants::helpText : "ex00 version " + Constants::programVersion) << std::endl;
            return EXIT_SUCCESS;
        }
        Logger log(std::cerr, options.logLevel);
        Bureaucrat john("John Smith", 130, log);
        log.info() << "Return value of john.getName():          " << john.getName() << std::endl;
        log.info() << "Return value of john.getGrade():         " << john.getGrade() << std::endl;
        log.info() << "Insertion operator (<<) overload result: ";
        std::cout << john << std::endl;
        return EXIT_SUCCESS;
    } catch (const Bureaucrat::GradeTooHighException &gradeTooHigh) {
        Logger::lastInstance().fatal() << ansi::red(gradeTooHigh.what()) << std::endl;
        return EXIT_FAILURE;
    } catch (const Bureaucrat::GradeTooLowException &gradeTooLow) {
        Logger::lastInstance().fatal() << ansi::red(gradeTooLow.what()) << std::endl;
        return EXIT_FAILURE;
    } catch (const std::exception &exception) {
        Logger::lastInstance().fatal() << ansi::red(exception.what()) << std::endl;
        return EXIT_FAILURE;
    }
}
