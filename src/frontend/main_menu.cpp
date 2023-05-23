#ifndef FRONTEND_MAINMENU
#define FRONTEND_MAINMENU


#include <memory>

#include "frontend.hpp"
#include "backend.hpp"

#include "cppconsmenu.hpp"



namespace Frontend {
    ChoiceAssignMan::ChoiceAssignMan() : ConsMenu::Choice("Assignment Manager") {
        this->screen = std::make_unique<AssignMan::MainMenu>(AssignMan::MainMenu());
    }

    MainMenu::MainMenu() {
        this->is_main_menu = true;
        this->title = "Welcome to the main menu!";
        this->desc = "Wawa.";

        this->add_choice<ChoiceAssignMan>();
    }
}



#endif