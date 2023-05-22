#include <iostream>
#include <windows.h>
#include <commdlg.h>

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
        void OpenPeriodScreen::show() {
            std::cout << "Please specify the .json file to open." << std::endl;
            std::filesystem::path file_path;
            try {
                file_path = File::open_file_dialog(
                    "Select Period JSON.",
                    {
                        std::make_tuple("JSON", "json")
                    }
                );
            } catch (File::ExcFD exc) {
                std::cout << exc.what() << std::endl;
                Console::enter_to_exit();
                return;
            }

            Backend::AssignMan::Period period = Backend::AssignMan::Period::get_from_json_file(file_path);

            OpenedPeriod::MainMenu(period).show();
        }
        OpenPeriodChoice::OpenPeriodChoice() : ConsMenu::Choice("Open Period") {
            this->screen = std::make_unique<OpenPeriodScreen>(OpenPeriodScreen());
        }




        void CreatePeriodScreen::show() {
            std::cout << "A period is a span of time where you have your subjects. This can be a semester, a school year, etc." << std::endl << std::endl;

            std::string name = Console::Prompt::send_prompt("Input name of period: ").value();
            auto period = Backend::AssignMan::Period(name);

            period.start_date = Datetime::ask_date("Input the start date of the period:");

            bool continue_end_date_input = Console::Prompt::send_prompt_yn("Do you want to input an end date?");
            if (continue_end_date_input) {
                period.end_date = Datetime::ask_date("Input the end date of the period:");
            }

            period.write_json_to_file(File::get_exe_path() / ".." / std::filesystem::path(name + ".json"));

            std::cout << std::endl << std::endl;
            std::cout
                << "Created period! A new file called " << period.name << ".json has appeared in the same folder as the program." << std::endl
                << std::endl
                << period.get_display_str() << std::endl
                << std::endl;

            Console::enter_to_exit();
        }
        CreatePeriodChoice::CreatePeriodChoice() : ConsMenu::Choice("Create Period") {
            this->screen = std::make_unique<CreatePeriodScreen>(CreatePeriodScreen());
        }


        MainMenu::MainMenu() {
            this->add_choice<CreatePeriodChoice>();
            this->add_choice<OpenPeriodChoice>();
        }
    }
}