#include <iostream>
#include <string>

#include "frontend.hpp"

#include "backend.hpp"



namespace Frontend {
    namespace AssignMan {
        namespace OpenedPeriod {
            std::optional<Backend::AssignMan::Period> current_period = std::nullopt;
            std::optional<std::filesystem::path> current_period_path;



            void ShowSubjectsScreen::show() {
                Backend::AssignMan::Period period = current_period.value();
                if (period.subjects.size() != 0) {
                    std::cout << "These are the subjects available for the period \"" << period.name << "\":";

                    for (Backend::AssignMan::Subject subject : period.subjects) {
                        std::cout << subject.get_display_str() << std::endl << std::endl;
                    }
                } else {
                    std::cout << "There are no subjects in the period." << std::endl;
                }

                std::cout << std::endl;
                Console::enter_to_exit();
            }

            ShowSubjectsChoice::ShowSubjectsChoice() : ConsMenu::Choice("Show All Subjects") {
                this->set_screen<ShowSubjectsScreen>();
            }



            void CreateSubjectScreen::show() {
                std::cout << "Add subject" << std::endl << std::endl;

                std::string subject_name = Console::Prompt::send_prompt("Input the name of the subject: ").value();
                std::string subject_abbr = Console::Prompt::send_prompt("Input the abbreviation of the subject: ").value();
                std::string subject_code = Console::Prompt::send_prompt("Input the subject code: ").value();
                std::optional<std::string> teacher_name = Console::Prompt::send_prompt("Input the name of the teacher: ", true);

                Backend::AssignMan::Subject subject(subject_name, subject_abbr, subject_code, teacher_name);
                current_period.value().subjects.push_back(subject);

                std::cout << std::endl << std::endl;

                std::cout
                    << "Created subject!" << std::endl
                    << subject.get_display_str() << std::endl
                    << std::endl;

                Console::enter_to_exit();
            }

            CreateSubjectChoice::CreateSubjectChoice() : ConsMenu::Choice("Create Subject") {
                this->set_screen<CreateSubjectScreen>();
            }



            void SaveScreen::show() {
                std::cout << "Saving period \"" << current_period.value().name << "\"..." << std::endl << std::endl;

                current_period.value().write_json_to_file(current_period_path.value());

                std::cout << "Saved!" << std::endl;
                Console::enter_to_exit();
            }

            SaveChoice::SaveChoice() : ConsMenu::Choice("Save") {
                this->set_screen<SaveScreen>();
            }



            MainMenu::MainMenu(Backend::AssignMan::Period _period, std::filesystem::path _period_path) {
                current_period = _period;
                current_period_path = _period_path;
                this->title = std::string("Opened period: ") + _period.name;
                this->desc = "Welcome to the Assignment Manager.";

                this->add_choice<CreateSubjectChoice>();
                this->add_choice<SaveChoice>();
            };
            void MainMenu::show() {
                ConsMenu::SelectMenu::show();
            }
        }
    }
}