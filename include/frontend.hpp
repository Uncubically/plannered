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
            extern std::optional<Backend::AssignMan::Period> current_period;
            extern std::optional<std::filesystem::path> current_period_path;



            class ShowSubjectsScreen : public ConsMenu::Screen {
                public:
                    void show() override;
            };
            class ShowSubjectsChoice : public ConsMenu::Choice {
                public:
                    ShowSubjectsChoice();
            };



            class CreateSubjectScreen : public ConsMenu::Screen {
                public:
                    void show() override;
            };
            class CreateSubjectChoice : public ConsMenu::Choice {
                public:
                    CreateSubjectChoice();
            };



            class SaveScreen : public ConsMenu::Screen {
                public:
                    void show() override;
            };
            class SaveChoice : public ConsMenu::Choice {
                public:
                    SaveChoice();
            };



            class MainMenu : public ConsMenu::SelectMenu {
                public:
                    MainMenu(Backend::AssignMan::Period _period, std::filesystem::path _period_path);

                    void show() override;
            };
        }
    }

}



