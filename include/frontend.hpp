#pragma once


#include "cppconsmenu.hpp"

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


    namespace AssignMan {
        class OpenPeriodScreen : public ConsMenu::Screen {
            public:
                void show() override;
        };
        class OpenPeriodChoice : public ConsMenu::Choice {
            public:
                OpenPeriodChoice();
        };



        class CreatePeriodScreen : public ConsMenu::Screen {
            public:
                void show() override;
        };
        class CreatePeriodChoice : public ConsMenu::Choice {
            public:
                CreatePeriodChoice();
        };


        class MainMenu : public ConsMenu::SelectMenu {
            public:
                MainMenu();
        };



        namespace OpenedPeriod {
            class CreateSubjectScreen : public ConsMenu::Screen {
                public:
                    Backend::AssignMan::Period& period;
                    CreateSubjectScreen(Backend::AssignMan::Period& _period);
                    void show() override;
            };
            class CreateSubjectChoice : public ConsMenu::Choice {
                public:
                    CreateSubjectChoice();
            };

            class MainMenu : public ConsMenu::SelectMenu {
                public:
                    Backend::AssignMan::Period period;

                    MainMenu(Backend::AssignMan::Period _period);

                    void show() override;
            };
        }
    }

}



