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
            std::optional<int> send_prompt_choose_subjects(
                std::string prompt,
                bool is_optional = false,
                bool show_optional_text = true,
                std::optional<std::string> blank_input = std::nullopt
            );



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



            class DeleteSubjectScreen : public ConsMenu::Screen {
                public:
                    void show() override;
            };
            class DeleteSubjectChoice : public ConsMenu::Choice {
                public:
                    DeleteSubjectChoice();
            };



            class ManageSubjsScreen : public ConsMenu::Screen {
                public:
                    void show() override;
            };
            class ManageSubjsChoice : public ConsMenu::Choice {
                public:
                    ManageSubjsChoice();
            };



            namespace ManageSubjs {
                extern std::optional<std::shared_ptr<Backend::AssignMan::Subject>> current_subject;



                class ShowTasksUnfinishedScreen : public ConsMenu::Screen {
                    public:
                        void show() override;
                };
                class ShowTasksUnfinishedChoice : public ConsMenu::Choice {
                    public:
                        ShowTasksUnfinishedChoice();
                };



                class CreateTaskScreen : public ConsMenu::Screen {
                    public:
                        void show() override;
                };
                class CreateTaskChoice : public ConsMenu::Choice {
                    public:
                        CreateTaskChoice();
                };



                class MainMenu : public ConsMenu::SelectMenu {
                    public:
                        MainMenu(std::shared_ptr<Backend::AssignMan::Subject> _current_subject);
                };
            }



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



