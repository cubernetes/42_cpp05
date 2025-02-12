#include <cstdlib>
#include <exception>
#include <iostream>

#include "AForm.hpp"
#include "Ansi.hpp"
#include "Bureaucrat.hpp"
#include "Constants.hpp"
#include "Logger.hpp"
#include "Options.hpp"
#include "Repr.hpp"

void testJohn(Logger &log) {
    log.debug() << "Trying to initialize a new Bureaucrat with grade " << repr(3) << std::endl;
    Bureaucrat john("John Smith", 3, log);
    log.debug() << "Return value of john.getName():          " << john.getName() << std::endl;
    log.debug() << "Return value of john.getGrade():         " << john.getGrade() << std::endl;
    log.debug() << "Insertion operator (<<) overload output: " << john << std::endl;

    try {
        log.debug() << "Calling first john.incrementGrade()" << std::endl;
        john.incrementGrade();
        log.debug() << "John now: " << john << std::endl << std::endl;
    } catch (const Bureaucrat::GradeTooHighException &gradeTooHigh) {
        Logger::lastInstance().debug() << "Caught GradeTooHighException: " << ansi::red(gradeTooHigh.what()) << ", continuing anyway\n" << std::endl;
    }

    try {
        log.debug() << "Calling second john.incrementGrade()" << std::endl;
        john.incrementGrade();
        log.debug() << "John now: " << john << std::endl << std::endl;
    } catch (const Bureaucrat::GradeTooHighException &gradeTooHigh) {
        Logger::lastInstance().debug() << "Caught GradeTooHighException: " << ansi::red(gradeTooHigh.what()) << ", continuing anyway\n" << std::endl;
    }

    try {
        log.debug() << "Calling third john.incrementGrade()" << std::endl;
        john.incrementGrade();
        log.debug() << "John now: " << john << std::endl << std::endl;
    } catch (const Bureaucrat::GradeTooHighException &gradeTooHigh) {
        Logger::lastInstance().debug() << "Caught GradeTooHighException: " << ansi::red(gradeTooHigh.what()) << ", continuing anyway\n" << std::endl;
    }

    try {
        log.debug() << "Calling fourth john.incrementGrade()" << std::endl;
        john.incrementGrade();
        log.debug() << "John now: " << john << std::endl << std::endl << std::endl;
    } catch (const Bureaucrat::GradeTooHighException &gradeTooHigh) {
        Logger::lastInstance().debug() << "Caught GradeTooHighException: " << ansi::red(gradeTooHigh.what()) << ", continuing anyway\n\n" << std::endl;
    }
}

void testJane(Logger &log) {
    log.debug() << "Trying to initialize a new Bureaucrat with grade " << repr(148) << std::endl;
    Bureaucrat jane("Jane Smith", 148, log);
    log.debug() << "Return value of jane.getName():          " << jane.getName() << std::endl;
    log.debug() << "Return value of jane.getGrade():         " << jane.getGrade() << std::endl;
    log.debug() << "Insertion operator (<<) overload output: " << jane << std::endl;

    try {
        log.debug() << "Calling first jane.decrementGrade()" << std::endl;
        jane.decrementGrade();
        log.debug() << "John now: " << jane << std::endl << std::endl;
    } catch (const Bureaucrat::GradeTooLowException &gradeTooLow) {
        Logger::lastInstance().debug() << "Caught GradeTooLowException: " << ansi::red(gradeTooLow.what()) << ", continuing anyway\n" << std::endl;
    }

    try {
        log.debug() << "Calling second jane.decrementGrade()" << std::endl;
        jane.decrementGrade();
        log.debug() << "John now: " << jane << std::endl << std::endl;
    } catch (const Bureaucrat::GradeTooLowException &gradeTooLow) {
        Logger::lastInstance().debug() << "Caught GradeTooLowException: " << ansi::red(gradeTooLow.what()) << ", continuing anyway\n" << std::endl;
    }

    try {
        log.debug() << "Calling third jane.decrementGrade()" << std::endl;
        jane.decrementGrade();
        log.debug() << "John now: " << jane << std::endl << std::endl;
    } catch (const Bureaucrat::GradeTooLowException &gradeTooLow) {
        Logger::lastInstance().debug() << "Caught GradeTooLowException: " << ansi::red(gradeTooLow.what()) << ", continuing anyway\n" << std::endl;
    }

    try {
        log.debug() << "Calling fourth jane.decrementGrade()" << std::endl;
        jane.decrementGrade();
        log.debug() << "John now: " << jane << std::endl << std::endl << std::endl;
    } catch (const Bureaucrat::GradeTooLowException &gradeTooLow) {
        Logger::lastInstance().debug() << "Caught GradeTooLowException: " << ansi::red(gradeTooLow.what()) << ", continuing anyway\n\n" << std::endl;
    }
}

void testFailure1(Logger &log) {
    try {
        log.debug() << "Trying to initialize a new Bureaucrat with grade " << repr(1000) << std::endl;
        Bureaucrat failure("Failure Smith", 1000, log);
        log.debug() << "Return value of failure.getName():          " << failure.getName() << std::endl;
        log.debug() << "Return value of failure.getGrade():         " << failure.getGrade() << std::endl;
        log.debug() << "Insertion operator (<<) overload output: " << failure << std::endl;
    } catch (const Bureaucrat::GradeTooHighException &gradeTooHigh) {
        Logger::lastInstance().debug() << "Caught GradeTooHighException: " << ansi::red(gradeTooHigh.what()) << std::endl << std::endl << std::endl;
    } catch (const Bureaucrat::GradeTooLowException &gradeTooLow) {
        Logger::lastInstance().debug() << "Caught GradeTooLowException: " << ansi::red(gradeTooLow.what()) << std::endl << std::endl << std::endl;
    }
}

void testFailure2(Logger &log) {
    try {
        log.debug() << "Trying to initialize a new Bureaucrat with grade " << repr(0) << std::endl;
        Bureaucrat failure("Failure Smith", 0, log);
        log.debug() << "Return value of failure.getName():          " << failure.getName() << std::endl;
        log.debug() << "Return value of failure.getGrade():         " << failure.getGrade() << std::endl;
        log.debug() << "Insertion operator (<<) overload output: " << failure << std::endl;
    } catch (const Bureaucrat::GradeTooHighException &gradeTooHigh) {
        Logger::lastInstance().debug() << "Caught GradeTooHighException: " << ansi::red(gradeTooHigh.what()) << std::endl << std::endl << std::endl;
    } catch (const Bureaucrat::GradeTooLowException &gradeTooLow) {
        Logger::lastInstance().debug() << "Caught GradeTooLowException: " << ansi::red(gradeTooLow.what()) << std::endl << std::endl << std::endl;
    }
}

int main(int ac, char **av) {
    try {
        Options options(ac, av);
        if (options.printHelp || options.printVersion) {
            std::cout << (options.printHelp ? Constants::helpText : "CPP05 ex02 version " + Constants::programVersion) << std::endl;
            return EXIT_SUCCESS;
        }
        Logger log(std::cerr, options.logLevel);

        try {
            AForm fail("28B", false, 160, 20, log);
            log.info << std::endl;
        } catch (const AForm::GradeTooLowException &e) {
            log.warning() << "Caught GradeTooLowException: " << ansi::red(e.what()) << std::endl;
        }
        AForm f("28C", false, 10, 20, log);
        Bureaucrat a("John", 9, log);
        Bureaucrat b("Jane", 80, log);
        log.info << std::endl;
        a.signForm(f);
        log.info << std::endl;
        b.signForm(f);
        log.info << std::endl;
        // testJohn(log);
        // testJane(log);
        // testFailure1(log);
        // testFailure2(log);

        log.info() << "Exiting" << std::endl;
        return EXIT_SUCCESS;
    } catch (const std::exception &exception) {
        Logger::lastInstance().fatal() << ansi::red(exception.what()) << std::endl;
        return EXIT_FAILURE;
    }
}
