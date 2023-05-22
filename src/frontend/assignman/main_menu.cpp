#include <iostream>

#include "frontend.hpp"
#include "backend.hpp"

#include "cppconsmenu.hpp"



namespace Frontend {
    namespace AssignMan {
        /*
        class AddSubjectScreen : public ConsMenu::Screen {
            public:
                void show() override {
                    std::string subject_name, subject_abbr, subject_code;
                    std::optional<std::string> teacher_name;

                    std::cout << "Create a subject: " << std::endl;
                    subject_name = Console::prompt_user_safe<std::string>("Enter name of subject: ");
                    subject_abbr = Console::prompt_user_safe<std::string>("Enter abbreviation of subject: ");
                    subject_code = Console::prompt_user_safe<std::string>("Enter subject code of subject: ");
                    teacher_name = Console::prompt_user_safe_optional<std::string>("Enter name of teacher: ");

                    auto subject = AssignMan::Subject(subject_name, subject_abbr, subject_code, teacher_name);

                    std::cout << "\n\n";

                    std::cout
                        << "Subject created!" << std::endl
                        << subject.get_display_str() << std::endl
                        << std::endl;

                    Console::enter_to_exit();
                }
        };
        class AddSubjectChoice : public ConsMenu::Choice {
            public:
                AddSubjectChoice() : ConsMenu::Choice("Add Subject") {
                    this->screen = std::make_unique<AddSubjectScreen>(AddSubjectScreen());
                }
        };
        */



        void CreatePeriodScreen::show() {
            std::cout << "A period is a span of time where you have your subjects. This can be a semester, a school year, etc." << std::endl << std::endl;

            std::cout << "The index is used for ordering your periods." << std::endl;
            int index = Console::Prompt::send_prompt<int>(
                "Input index (1 for 1st, 2 for 2nd, etc.): ",
                Console::Prompt::conv_int
            ).value();
            auto period = Backend::AssignMan::Period(index);

            period.start_date = Datetime::ask_date("Input the start date of the period:");

            bool continue_end_date_input = Console::Prompt::send_prompt_yn("Do you want to input an end date?");
            if (continue_end_date_input) {
                period.end_date = Datetime::ask_date("Input the end date of the period:");
            }

            std::cout << std::endl << std::endl;
            std::cout
                << "Created period!" << std::endl
                << std::endl
                << period.get_display_str() << std::endl
                << std::endl;

            Console::enter_to_exit();
        }


        CreatePeriodChoice::CreatePeriodChoice() : ConsMenu::Choice("Create Period") {
            this->screen = std::make_unique<CreatePeriodScreen>(CreatePeriodScreen());
        }


        MainMenu::MainMenu() {
            this->choices.push_back(std::make_unique<CreatePeriodChoice>(CreatePeriodChoice()));
        }
    }
}