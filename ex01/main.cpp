#include <cstdlib>
#include <exception>
#include <iostream>

#include "Ansi.hpp"
#include "Bureaucrat.hpp"
#include "Constants.hpp"
#include "Form.hpp"
#include "Logger.hpp"
#include "Options.hpp"

int main(int ac, char **av) {
    try {
        Options options(ac, av);
        if (options.printHelp || options.printVersion) {
            std::cout << (options.printHelp ? Constants::helpText : "CPP05 ex01 version " + Constants::programVersion) << std::endl;
            return EXIT_SUCCESS;
        }
        Logger log(std::cerr, options.logLevel);

        try {
            Form fail("28B", false, 160, 20, log);
            log.info << std::endl;
        } catch (const Form::GradeTooLowException &e) {
            log.warning() << "Caught GradeTooLowException: " << ansi::red(e.what()) << std::endl;
        }
        Form f("28C", false, 10, 20, log);
        Bureaucrat a("John", 9, log);
        Bureaucrat b("Jane", 80, log);
        log.info << std::endl;
        a.signForm(f);
        log.info << std::endl;
        b.signForm(f);
        log.info << std::endl;

        log.debug() << "Exiting" << std::endl;
        return EXIT_SUCCESS;
    } catch (const std::exception &exception) {
        Logger::lastInstance().fatal() << ansi::red(exception.what()) << std::endl;
        return EXIT_FAILURE;
    }
}
