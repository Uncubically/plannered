#include <iostream>
#include <string>

#include "frontend.hpp"

#include "backend.hpp"



namespace Frontend {
    namespace AssignMan {
        namespace OpenedPeriod {
            CreateSubjectScreen::CreateSubjectScreen(Backend::AssignMan::Period& _period) : period(_period) {}

            void CreateSubjectScreen::show() {
                std::cout << "Add subject" << std::endl << std::endl;

                std::string subject_name = Console::Prompt::send_prompt("Input the name of the subject: ").value();
                std::string subject_abbr = Console::Prompt::send_prompt("Input the abbreviation of the subject: ").value();
                std::string subject_code = Console::Prompt::send_prompt("Input the subject code: ").value();
                std::optional<std::string> teacher_name = Console::Prompt::send_prompt("Input the name of the teacher: ", true);

                Backend::AssignMan::Subject subject(subject_name, subject_abbr, subject_code, teacher_name);
                this->period.subjects.push_back(subject);

                std::cout << std::endl << std::endl;

                std::cout
                    << "Created subject!" << std::endl
                    << subject.get_display_str() << std::endl
                    << std::endl;

                Console::enter_to_exit();
            }

            CreateSubjectChoice::CreateSubjectChoice(Backend::AssignMan::Period& _period) : ConsMenu::Choice("Create Subject") {
                this->set_screen<CreateSubjectScreen>(_period);
            }



            


            MainMenu::MainMenu(Backend::AssignMan::Period _period) {
                this->period = _period;
                this->title = std::string("Opened period: ") + _period.name;
                this->desc = "Welcome to the Assignment Manager.";

                this->add_choice<CreateSubjectChoice>(_period);
            };
            void MainMenu::show() {
                ConsMenu::SelectMenu::show();
            }
        }
    }
}