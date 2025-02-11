#include <cstdlib>
#include <exception>
#include <iostream>

#include "Ansi.hpp"
#include "Bureaucrat.hpp"
#include "Constants.hpp"
#include "Logger.hpp"
#include "Options.hpp"
#include "Repr.hpp"

void testJohn(Logger &log) {
    log.info() << "Trying to initialize a new Bureaucrat with grade " << repr(3) << std::endl;
    Bureaucrat john("John Smith", 3, log);
    log.info() << "Return value of john.getName():          " << john.getName() << std::endl;
    log.info() << "Return value of john.getGrade():         " << john.getGrade() << std::endl;
    log.info() << "Insertion operator (<<) overload output: " << john << std::endl;

    try {
        log.info() << "Calling first john.incrementGrade()" << std::endl;
        john.incrementGrade();
        log.info() << "John now: " << john << std::endl << std::endl;
    } catch (const Bureaucrat::GradeTooHighException &gradeTooHigh) {
        Logger::lastInstance().error() << "Caught GradeTooHighException: " << ansi::red(gradeTooHigh.what()) << ", continuing anyway\n" << std::endl;
    }

    try {
        log.info() << "Calling second john.incrementGrade()" << std::endl;
        john.incrementGrade();
        log.info() << "John now: " << john << std::endl << std::endl;
    } catch (const Bureaucrat::GradeTooHighException &gradeTooHigh) {
        Logger::lastInstance().error() << "Caught GradeTooHighException: " << ansi::red(gradeTooHigh.what()) << ", continuing anyway\n" << std::endl;
    }

    try {
        log.info() << "Calling third john.incrementGrade()" << std::endl;
        john.incrementGrade();
        log.info() << "John now: " << john << std::endl << std::endl;
    } catch (const Bureaucrat::GradeTooHighException &gradeTooHigh) {
        Logger::lastInstance().error() << "Caught GradeTooHighException: " << ansi::red(gradeTooHigh.what()) << ", continuing anyway\n" << std::endl;
    }

    try {
        log.info() << "Calling fourth john.incrementGrade()" << std::endl;
        john.incrementGrade();
        log.info() << "John now: " << john << std::endl << std::endl << std::endl;
    } catch (const Bureaucrat::GradeTooHighException &gradeTooHigh) {
        Logger::lastInstance().error() << "Caught GradeTooHighException: " << ansi::red(gradeTooHigh.what()) << ", continuing anyway\n\n" << std::endl;
    }
}

void testJane(Logger &log) {
    log.info() << "Trying to initialize a new Bureaucrat with grade " << repr(148) << std::endl;
    Bureaucrat jane("Jane Smith", 148, log);
    log.info() << "Return value of jane.getName():          " << jane.getName() << std::endl;
    log.info() << "Return value of jane.getGrade():         " << jane.getGrade() << std::endl;
    log.info() << "Insertion operator (<<) overload output: " << jane << std::endl;

    try {
        log.info() << "Calling first jane.decrementGrade()" << std::endl;
        jane.decrementGrade();
        log.info() << "John now: " << jane << std::endl << std::endl;
    } catch (const Bureaucrat::GradeTooLowException &gradeTooLow) {
        Logger::lastInstance().error() << "Caught GradeTooLowException: " << ansi::red(gradeTooLow.what()) << ", continuing anyway\n" << std::endl;
    }

    try {
        log.info() << "Calling second jane.decrementGrade()" << std::endl;
        jane.decrementGrade();
        log.info() << "John now: " << jane << std::endl << std::endl;
    } catch (const Bureaucrat::GradeTooLowException &gradeTooLow) {
        Logger::lastInstance().error() << "Caught GradeTooLowException: " << ansi::red(gradeTooLow.what()) << ", continuing anyway\n" << std::endl;
    }

    try {
        log.info() << "Calling third jane.decrementGrade()" << std::endl;
        jane.decrementGrade();
        log.info() << "John now: " << jane << std::endl << std::endl;
    } catch (const Bureaucrat::GradeTooLowException &gradeTooLow) {
        Logger::lastInstance().error() << "Caught GradeTooLowException: " << ansi::red(gradeTooLow.what()) << ", continuing anyway\n" << std::endl;
    }

    try {
        log.info() << "Calling fourth jane.decrementGrade()" << std::endl;
        jane.decrementGrade();
        log.info() << "John now: " << jane << std::endl << std::endl << std::endl;
    } catch (const Bureaucrat::GradeTooLowException &gradeTooLow) {
        Logger::lastInstance().error() << "Caught GradeTooLowException: " << ansi::red(gradeTooLow.what()) << ", continuing anyway\n\n" << std::endl;
    }
}

void testFailure1(Logger &log) {
    try {
        log.info() << "Trying to initialize a new Bureaucrat with grade " << repr(1000) << std::endl;
        Bureaucrat failure("Failure Smith", 1000, log);
        log.info() << "Return value of failure.getName():          " << failure.getName() << std::endl;
        log.info() << "Return value of failure.getGrade():         " << failure.getGrade() << std::endl;
        log.info() << "Insertion operator (<<) overload output: " << failure << std::endl;
    } catch (const Bureaucrat::GradeTooHighException &gradeTooHigh) {
        Logger::lastInstance().error() << "Caught GradeTooHighException: " << ansi::red(gradeTooHigh.what()) << std::endl << std::endl << std::endl;
    } catch (const Bureaucrat::GradeTooLowException &gradeTooLow) {
        Logger::lastInstance().error() << "Caught GradeTooLowException: " << ansi::red(gradeTooLow.what()) << std::endl << std::endl << std::endl;
    }
}

void testFailure2(Logger &log) {
    try {
        log.info() << "Trying to initialize a new Bureaucrat with grade " << repr(0) << std::endl;
        Bureaucrat failure("Failure Smith", 0, log);
        log.info() << "Return value of failure.getName():          " << failure.getName() << std::endl;
        log.info() << "Return value of failure.getGrade():         " << failure.getGrade() << std::endl;
        log.info() << "Insertion operator (<<) overload output: " << failure << std::endl;
    } catch (const Bureaucrat::GradeTooHighException &gradeTooHigh) {
        Logger::lastInstance().error() << "Caught GradeTooHighException: " << ansi::red(gradeTooHigh.what()) << std::endl << std::endl << std::endl;
    } catch (const Bureaucrat::GradeTooLowException &gradeTooLow) {
        Logger::lastInstance().error() << "Caught GradeTooLowException: " << ansi::red(gradeTooLow.what()) << std::endl << std::endl << std::endl;
    }
}

int main(int ac, char **av) {
    try {
        Options options(ac, av);
        if (options.printHelp || options.printVersion) {
            std::cout << (options.printHelp ? Constants::helpText : "CPP05 ex01 version " + Constants::programVersion) << std::endl;
            return EXIT_SUCCESS;
        }
        Logger log(std::cerr, options.logLevel);

        testJohn(log);
        testJane(log);
        testFailure1(log);
        testFailure2(log);

        log.info() << "Exiting" << std::endl;
        return EXIT_SUCCESS;
    } catch (const Bureaucrat::GradeTooHighException &gradeTooHigh) {
        Logger::lastInstance().fatal() << "Caught fatal GradeTooHighException: " << ansi::red(gradeTooHigh.what()) << std::endl;
        return EXIT_FAILURE;
    } catch (const Bureaucrat::GradeTooLowException &gradeTooLow) {
        Logger::lastInstance().fatal() << "Caught fatal GradeTooLowException: " << ansi::red(gradeTooLow.what()) << std::endl;
        return EXIT_FAILURE;
    } catch (const std::exception &exception) {
        Logger::lastInstance().fatal() << ansi::red(exception.what()) << std::endl;
        return EXIT_FAILURE;
    }
}
