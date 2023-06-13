#ifndef FRONTEND_MAINMENU
#define FRONTEND_MAINMENU


#include <memory>

#include "frontend.hpp"
#include "backend.hpp"

#include "cppconsmenu.hpp"



namespace Frontend {
    bool enable_anim = true;



    void MainMenuInherit::anim_chosen(ConsMenu::SelectResult result) {
        if (!enable_anim) return;


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
    void MainMenuInherit::anim_exit_menu() {
        if (!enable_anim) return;
        ConsMenu::SelectMenu::anim_exit_menu();
    }



    void screen_end_anim() {
        if (!enable_anim) return;

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



    void AnimationSetScreen::show() {
        bool anims = Console::Prompt::send_prompt_yn("Would you like to enable (Y) or disable (N) animations? ");
        enable_anim = anims;

        if (enable_anim) {
            std::cout << "Enabled animations." << std::endl;
        } else {
            std::cout << "Disabled animations." << std::endl;
        }

        Console::enter_to_exit();
    }
    AnimationSetChoice::AnimationSetChoice() : ConsMenu::Choice("Enable / Disable Animations") {
        this->set_screen<AnimationSetScreen>();
    }



    void FancyColorsSetScreen::show() {
        std::cout << "Fancy colors can be disabled for better readability for older systems." << std::endl;
        bool enable = Console::Prompt::send_prompt_yn("Would you like to enable (Y) or disable (N) fancy colors? ");
        Shared::enable_fancy_colors = enable;

        if (enable) {
            std::cout << "Enabled fancy colors." << std::endl;
        } else {
            std::cout << "Disabled fancy colors." << std::endl;
        }

        Console::enter_to_exit();
    }
    FancyColorsSetChoice::FancyColorsSetChoice() : ConsMenu::Choice("Enable / Disable Fancy Colors") {
        this->set_screen<FancyColorsSetScreen>();
    }



    ChoiceAssignMan::ChoiceAssignMan() : ConsMenu::Choice("Assignment Manager") {
        this->set_screen<AssignMan::MainMenu>();
    }

    MainMenu::MainMenu() {
        this->is_main_menu = true;
        this->title = "PlannerEd";
        this->desc = "Welcome to PlannerEd!";

        this->add_choice<ChoiceAssignMan>();
        this->add_choice<AnimationSetChoice>();
        this->add_choice<FancyColorsSetChoice>();
        this->add_choice<ShowCreditsChoice>();
    }
}



#endif