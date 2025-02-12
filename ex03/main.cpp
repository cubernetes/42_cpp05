#include <cstdlib>
#include <exception>
#include <iostream>

#include "AForm.hpp"
#include "Ansi.hpp"
#include "Bureaucrat.hpp"
#include "Constants.hpp"
#include "Logger.hpp"
#include "Options.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

void shrubberyTests(Logger &log, Bureaucrat &johnDoe, Bureaucrat &lindaSmith, Bureaucrat &bobRoss, ShrubberyCreationForm &gardenShrubbery, ShrubberyCreationForm &mallShrubbery) {
    log.info() << "The following will fail" << std::endl;
    johnDoe.signForm(gardenShrubbery);
    log.info << std::endl;

    log.info() << "The following 2 will succeed" << std::endl;
    lindaSmith.signForm(gardenShrubbery);
    bobRoss.signForm(mallShrubbery);
    log.info << std::endl;

    log.info() << "The following 3 will fail" << std::endl;
    johnDoe.executeForm(gardenShrubbery);
    johnDoe.executeForm(mallShrubbery);
    lindaSmith.executeForm(mallShrubbery);
    log.info << std::endl;

    log.info() << "The following 2 will succeed" << std::endl;
    bobRoss.executeForm(mallShrubbery);
    bobRoss.executeForm(gardenShrubbery);
    log.info << std::endl;
}

void robotomyTests(Logger &log, Bureaucrat &robertFord, Bureaucrat &bobRoss, Bureaucrat &warrenBuffet, Bureaucrat &elonMusk, RobotomyRequestForm &doloresRobotomy, RobotomyRequestForm &benderRobotomy,
                   RobotomyRequestForm &HAL9000Robotomy) {
    log.info() << "The following 2 will succeed" << std::endl;
    robertFord.signForm(doloresRobotomy);
    robertFord.executeForm(doloresRobotomy);
    log.info << std::endl;

    log.info() << "The following will succeed" << std::endl;
    bobRoss.signForm(benderRobotomy);
    log.info << std::endl;

    log.info() << "The following will fail" << std::endl;
    bobRoss.executeForm(benderRobotomy);
    log.info << std::endl;

    log.info() << "The following will succeed" << std::endl;
    warrenBuffet.executeForm(benderRobotomy);
    log.info << std::endl;

    log.info() << "The following 2 will succeed" << std::endl;
    elonMusk.signForm(HAL9000Robotomy);
    elonMusk.executeForm(HAL9000Robotomy);
    log.info << std::endl;
}

void presidentialPardonTests(Logger &log, Bureaucrat &johnDoe, Bureaucrat &lindaSmith, Bureaucrat &bobRoss, Bureaucrat &warrenBuffet, Bureaucrat &edwardMorra, Bureaucrat &satyaNadella,
                             Bureaucrat &elonMusk, Bureaucrat &robertFord, PresidentialPardonForm &aaronSwartzPardon, PresidentialPardonForm &edwardSnowdenPardon,
                             PresidentialPardonForm &julianAssangePardon, PresidentialPardonForm &johnDoePardon) {
    log.info() << "The following 3 will fail" << std::endl;
    lindaSmith.signForm(aaronSwartzPardon);
    bobRoss.signForm(edwardSnowdenPardon);
    warrenBuffet.signForm(julianAssangePardon);
    log.info << std::endl;

    log.info() << "The following will fail" << std::endl;
    edwardMorra.executeForm(julianAssangePardon);
    log.info << std::endl;

    log.info() << "The following 3 will succeed" << std::endl;
    edwardMorra.signForm(aaronSwartzPardon);
    edwardMorra.signForm(edwardSnowdenPardon);
    edwardMorra.signForm(julianAssangePardon);
    log.info << std::endl;

    log.info() << "The following will fail" << std::endl;
    satyaNadella.executeForm(aaronSwartzPardon);
    log.info << std::endl;

    log.info() << "The following 3 will succeed" << std::endl;
    elonMusk.executeForm(aaronSwartzPardon);
    robertFord.executeForm(edwardSnowdenPardon);
    edwardMorra.executeForm(julianAssangePardon);
    log.info << std::endl;

    log.info() << "The following 3 will fail" << std::endl;
    johnDoe.signForm(johnDoePardon);
    johnDoe.executeForm(johnDoePardon);
    robertFord.executeForm(johnDoePardon);
    log.info << std::endl;
}

int main(int ac, char **av) {
    try {
        Options options(ac, av);
        if (options.printHelp || options.printVersion) {
            std::cout << (options.printHelp ? Constants::helpText : "CPP05 ex02 version " + Constants::programVersion) << std::endl;
            return EXIT_SUCCESS;
        }
        Logger log(std::cerr, options.logLevel);

        ShrubberyCreationForm gardenShrubbery("Garden");
        ShrubberyCreationForm mallShrubbery("Mall");

        RobotomyRequestForm benderRobotomy("Bender");
        RobotomyRequestForm doloresRobotomy("Dolores Abernathy");
        RobotomyRequestForm HAL9000Robotomy("HAL 9000");

        PresidentialPardonForm aaronSwartzPardon("Aaron Swartz");
        PresidentialPardonForm julianAssangePardon("Julian Assange");
        PresidentialPardonForm edwardSnowdenPardon("Edward Snowden");
        PresidentialPardonForm johnDoePardon("John Doe");

        Bureaucrat edwardMorra("Edward Morra", 1);
        Bureaucrat robertFord("Robert Ford", 3);
        Bureaucrat elonMusk("Elon Musk", 4);

        Bureaucrat satyaNadella("Satya Nadella", 15);
        Bureaucrat warrenBuffet("Warren Buffet", 40);
        Bureaucrat bobRoss("Bob Ross", 72);

        Bureaucrat lindaSmith("Linda Smith", 144);
        Bureaucrat johnDoe("John Doe", 150);

        shrubberyTests(log, johnDoe, lindaSmith, bobRoss, gardenShrubbery, mallShrubbery);
        robotomyTests(log, robertFord, bobRoss, warrenBuffet, elonMusk, doloresRobotomy, benderRobotomy, HAL9000Robotomy);
        presidentialPardonTests(log, johnDoe, lindaSmith, bobRoss, warrenBuffet, edwardMorra, satyaNadella, elonMusk, robertFord, aaronSwartzPardon, edwardSnowdenPardon, julianAssangePardon,
                                johnDoePardon);

        log.debug() << "Exiting" << std::endl;
        return EXIT_SUCCESS;
    } catch (const std::exception &exception) {
        Logger::lastInstance().fatal() << ansi::red(exception.what()) << std::endl;
        return EXIT_FAILURE;
    } catch (...) {
        std::cout << "WHAT" << std::endl;
    }
}
