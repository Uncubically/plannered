#ifndef FRONTEND_MAINMENU
#define FRONTEND_MAINMENU


#include <memory>

#include "frontend.hpp"
#include "backend.hpp"

#include "cppconsmenu.hpp"



namespace Frontend {
    void MainMenuInherit::anim_chosen(ConsMenu::SelectResult result) {
        Console::Color::SpecStyle bar_specstyle = Console::Color::SpecStyle(
            false,
            Console::Color::green,
            Console::Color::black,
            true
        );
        Console::Anim::BarHighlight(0.1, result.row, result.width - 1, "=", bar_specstyle).run();

        sleep(1);

        Console::Color::SpecStyle wipe1_specstyle = Console::Color::SpecStyle(
            false,
            Console::Color::blue,
            Console::Color::blue,
            true
        );
        Console::Anim::CornerPixelate(0.001, wipe1_specstyle).run();

        Console::Color::SpecStyle wipe2_specstyle = Console::Color::SpecStyle(
            false,
            Console::Color::black,
            Console::Color::black,
            true
        );
        Console::Anim::CornerPixelate(0.001, wipe2_specstyle).run();
    }



    ChoiceAssignMan::ChoiceAssignMan() : ConsMenu::Choice("Assignment Manager") {
        this->set_screen<AssignMan::MainMenu>();
    }

    MainMenu::MainMenu() {
        this->is_main_menu = true;
        this->title = "Welcome to the main menu!";
        this->desc = "Wawa.";

        this->add_choice<ChoiceAssignMan>();
    }
}



#endif