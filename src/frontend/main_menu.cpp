#ifndef FRONTEND_MAINMENU
#define FRONTEND_MAINMENU


#include <memory>

#include "frontend.hpp"

#include "backend.hpp"



namespace Frontend {
    ChoiceAssignMan::ChoiceAssignMan() : ConsMenu::Choice("AssignMan") {
        this->screen = std::make_unique<FAssignMan::MainMenu>(FAssignMan::MainMenu());
    }

    class MainMenu : public ConsMenu::SelectMenu {
        public:
            MainMenu() {
                this->is_main_menu = true;
                this->title = "Welcome to the main menu!";
                this->desc = "Wawa.";

                this->choices.push_back(std::make_unique<ChoiceAssignMan>(ChoiceAssignMan()));
            }
    };
}



#endif