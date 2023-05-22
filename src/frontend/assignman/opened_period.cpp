#include <iostream>

#include "frontend.hpp"

#include "backend.hpp"



namespace Frontend {
    namespace AssignMan {
        namespace OpenedPeriod {
            MainMenu::MainMenu(Backend::AssignMan::Period _period) {
                this->period = _period;
            };

            void MainMenu::show() {
                ConsMenu::Screen::show();

                std::cout << this->period.get_display_str() << std::endl << std::endl;

                Console::enter_to_exit();
            }
        }
    }
}