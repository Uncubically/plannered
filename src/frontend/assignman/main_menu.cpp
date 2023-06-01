#include <iostream>
#include <windows.h>
#include <commdlg.h>

#include "frontend.hpp"

#include "backend.hpp"
#include "shared.hpp"

#include "cppconsmenu.hpp"



namespace Frontend::AssignMan {
    void OpenPeriodScreen::show() {
        std::cout
            << "Please specify the .json file to open." << std::endl
            << Console::Color::SpecStyle(false, Console::Color::light_black).get_str() << "Opening file explorer..." << std::endl;
    
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


        Backend::AssignMan::Period period;
        try {
            period = Backend::AssignMan::Period::get_from_json_file(file_path);
        } catch (const std::exception& exc) {
            std::cout << "JSON Error." << std::endl << exc.what() << std::endl;
            Console::enter_to_exit();
            return;
        }


        screen_end_anim();
        OpenedPeriod::MainMenu(period, file_path).show();
    }
    OpenPeriodChoice::OpenPeriodChoice() : ConsMenu::Choice("Open Period", Shared::period_important_color) {
        this->set_screen<OpenPeriodScreen>();
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
            << "Created period! "
                << Shared::period_important_color.get_str()
                << "A new file called " << period.name << ".json has appeared in the same folder as the program."
                << Console::Color::SpecStyle(true).get_str() << std::endl
            << std::endl
            << period.get_display_str() << std::endl
            << std::endl;

        Console::enter_to_exit();
        screen_end_anim();
    }
    CreatePeriodChoice::CreatePeriodChoice() : ConsMenu::Choice("Create Period", Shared::period_color) {
        this->set_screen<CreatePeriodScreen>();
    }


    MainMenu::MainMenu() {
        this->title = "Assignment Manager";
        this->desc = "Please select a period to manage.";

        this->add_choice<CreatePeriodChoice>();
        this->add_choice<OpenPeriodChoice>();
    }
}