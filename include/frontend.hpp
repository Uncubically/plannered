#pragma once


#include "backend.hpp"



namespace Frontend {
    class ChoiceAssignMan : public ConsMenu::Choice {
        public:
            ChoiceAssignMan();
    };
    // Represents the main menu.
    class MainMenu : public ConsMenu::SelectMenu {
        public:
            MainMenu();
    };


    namespace FAssignMan {
        class CreatePeriodScreen : public ConsMenu::Screen {
            public:
                void show() override {
                    std::cout << "A period is a span of time where you have your subjects. This can be a semester, a school year, etc." << std::endl << std::endl;

                    std::cout << "The index is used for ordering your periods." << std::endl;
                    int index = Console::Prompt::send_prompt<int>(
                        "Input index (1 for 1st, 2 for 2nd, etc.): ",
                        Console::Prompt::conv_int
                    ).value();
                    auto period = AssignMan::Period(index);

                    period.start_date = Datetime::ask_date("Input the start date of the period:");

                    bool continue_end_date_input = Console::Prompt::send_prompt_yn("Do you want to input an end date?");
                    if (continue_end_date_input) {
                        period.end_date = Datetime::ask_date("Input the end date of the period:");
                    }

                    std::cout << std::endl << std::endl;
                    std::cout
                        << "Created period!" << std::endl
                        << period.get_display_str() << std::endl;

                    Console::enter_to_exit();
                }
        };

        class CreatePeriodChoice : public ConsMenu::Choice {
            public:
                CreatePeriodChoice() : ConsMenu::Choice("Create Period") {
                    this->screen = std::make_unique<CreatePeriodScreen>(CreatePeriodScreen());
                }
        };


        class MainMenu : public ConsMenu::SelectMenu {
            public:
                MainMenu() {
                    this->choices.push_back(std::make_unique<CreatePeriodChoice>(CreatePeriodChoice()));
                }
        };
    }

}



