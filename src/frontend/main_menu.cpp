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

        sleep(0.5);
    }



    void screen_end_anim() {
        Console::Anim::FillMiddleThenWipe(1).run();
        Console::Anim::FillMiddleThenWipe(1, Console::Color::SpecStyle(false, Console::Color::black, Console::Color::black)).run();
        sleep(0.5);
    }



    void ShowCreditsScreen::show() {
        std::string credits = File::read_str_file("./assets/credits.txt");

        Console::Anim::Typewriter(1, credits).run();

        std::cout << std::endl << std::endl << std::endl;
        Console::enter_to_exit();
    }
    ShowCreditsChoice::ShowCreditsChoice() : ConsMenu::Choice("Credits") {
        this->set_screen<ShowCreditsScreen>();
    }



    ChoiceAssignMan::ChoiceAssignMan() : ConsMenu::Choice("Assignment Manager") {
        this->set_screen<AssignMan::MainMenu>();
    }

    MainMenu::MainMenu() {
        this->is_main_menu = true;
        this->title = "PlannerEd";
        this->desc = "Welcome to PlannerEd!";

        this->add_choice<ChoiceAssignMan>();
        this->add_choice<ShowCreditsChoice>();
    }
}



#endif