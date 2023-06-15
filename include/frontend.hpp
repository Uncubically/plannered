#pragma once


#include "cppconsmenu.hpp"

#include "backend.hpp"



namespace Frontend {
    // If true, animations are enabled. False otherwise.
    extern bool enable_anim;



    // Parent class for all menus that present a choice.
    class MainMenuInherit : public ConsMenu::SelectMenu {
        void anim_chosen(ConsMenu::SelectResult result) override;

        void anim_exit_menu() override;
    };



    // Plays the animation after a screen exits.
    void screen_end_anim();




    // The screen for the credits.
    class ShowCreditsScreen : public ConsMenu::Screen {
        public:
            void show() override;
    };
    class ShowCreditsChoice : public ConsMenu::Choice {
        public:
            ShowCreditsChoice();
    };



    // The screen for setting if animations are enabled or not.
    class AnimationSetScreen : public ConsMenu::Screen {
        public:
            void show() override;
    };
    class AnimationSetChoice : public ConsMenu::Choice {
        public:
            AnimationSetChoice();
    };



    // The screen for setting if fancy colors are enabled or not.
    class FancyColorsSetScreen : public ConsMenu::Screen {
        public:
            void show() override;
    };
    class FancyColorsSetChoice : public ConsMenu::Choice {
        public:
            FancyColorsSetChoice();
    };


    // The choice for entering the Assignment Manager.
    class ChoiceAssignMan : public ConsMenu::Choice {
        public:
            ChoiceAssignMan();
    };


    // Represents the main menu.
    class MainMenu : public MainMenuInherit {
        public:
            MainMenu();
    };


    // The Assignment Manager namespace.
    namespace AssignMan {
        // The screen for opening a period.
        class OpenPeriodScreen : public ConsMenu::Screen {
            public:
                void show() override;
        };
        class OpenPeriodChoice : public ConsMenu::Choice {
            public:
                OpenPeriodChoice();
                void on_show() override;
        };



        // The screen for creating a period.
        class CreatePeriodScreen : public ConsMenu::Screen {
            public:
                void show() override;
        };
        class CreatePeriodChoice : public ConsMenu::Choice {
            public:
                CreatePeriodChoice();
        };


        // The assignment manager main menu.
        class MainMenu : public MainMenuInherit {
            public:
                MainMenu();
        };



        // The namespace containing all menus after opening a period.
        namespace OpenedPeriod {
            // Sends a prompt to choose a subject.
            std::optional<int> send_prompt_choose_subjects(
                std::string prompt,
                bool is_optional = false,
                bool show_optional_text = true,
                std::optional<std::string> blank_input = std::nullopt
            );



            // The currently opened period. If empty, there is no currently opened period.
            extern std::optional<Backend::AssignMan::Period> current_period;

            // The path to the currently opened period. If empty, there is no currently opened period.
            extern std::optional<std::filesystem::path> current_period_path;

            // true if there are unsaved changes.
            extern bool has_changes;



            // The screen for showing the period's information.
            class ShowPeriodInfoScreen : public ConsMenu::Screen {
                public:
                    void show() override;
            };
            class ShowPeriodInfoChoice : public ConsMenu::Choice {
                public:
                    ShowPeriodInfoChoice();
                    void on_show() override;
            };



            // The screen for editing a period's information.
            class EditPeriodScreen : public ConsMenu::Screen {
                public:
                    void show() override;
            };
            class EditPeriodChoice : public ConsMenu::Choice {
                public:
                    EditPeriodChoice();
            };



            // The screen for showing all subjects.
            class ShowSubjectsScreen : public ConsMenu::Screen {
                public:
                    void show() override;
            };
            class ShowSubjectsChoice : public ConsMenu::Choice {
                public:
                    ShowSubjectsChoice();
                    void on_show() override;
            };



            // The screen for creating a new subject in the period.
            class CreateSubjectScreen : public ConsMenu::Screen {
                public:
                    void show() override;
            };
            class CreateSubjectChoice : public ConsMenu::Choice {
                public:
                    CreateSubjectChoice();
            };



            // The screen for editing a subject in the period.
            class EditSubjectScreen : public ConsMenu::Screen {
                public:
                    void show() override;
            };
            class EditSubjectChoice : public ConsMenu::Choice {
                public:
                    EditSubjectChoice();
            };



            // The screen for deleting a subject from the period.
            class DeleteSubjectScreen : public ConsMenu::Screen {
                public:
                    void show() override;
            };
            class DeleteSubjectChoice : public ConsMenu::Choice {
                public:
                    DeleteSubjectChoice();
            };



            // The screen for showing all unfinished tasks.
            class ShowUnfinishedTasksScreen : public ConsMenu::Screen {
                public:
                    void show() override;
            };
            class ShowUnfinishedTasksChoice : public ConsMenu::Choice {
                public:
                    ShowUnfinishedTasksChoice();
                    void on_show() override;
            };



            // The screen for managing tasks.
            class ManageTasksScreen : public ConsMenu::Screen {
                public:
                    void show() override;
            };
            class ManageTasksChoice : public ConsMenu::Choice {
                public:
                    ManageTasksChoice();
                    void on_show() override;
            };



            // The namespace containing all structures used to manage tasks in the period.
            namespace ManageTasks {
                // The index of the subject in the period list to have its tasks edited. If empty, there is no currently chosen subject.
                extern std::optional<int> subject_index;



                // Sends a prompt to the user to choose a task.
                std::optional<int> send_prompt_choose_task(
                    std::string prompt,
                    bool is_optional = false,
                    bool show_optional_text = true,
                    std::optional<std::string> blank_input = std::nullopt
                );



                // The screen for showing all unfinished tasks in the subject.
                class ShowTasksUnfinishedScreen : public ConsMenu::Screen {
                    public:
                        void show() override;
                };
                class ShowTasksUnfinishedChoice : public ConsMenu::Choice {
                    public:
                        ShowTasksUnfinishedChoice();
                        void on_show() override;
                };



                /*
                The screen for showing all tasks in the subject.
                This is different from `ShowTasksUnfinishedScreen` because this shows all tasks, unfinished or finished.
                */
                class ShowAllTasksScreen : public ConsMenu::Screen {
                    public:
                        void show() override;
                };
                class ShowAllTasksChoice : public ConsMenu::Choice {
                    public:
                        ShowAllTasksChoice();
                        void on_show() override;
                };



                // The screen for creating a task in the subject.
                class CreateTaskScreen : public ConsMenu::Screen {
                    public:
                        void show() override;
                };
                class CreateTaskChoice : public ConsMenu::Choice {
                    public:
                        CreateTaskChoice();
                };



                // The screen for editing a task.
                class EditTaskScreen : public ConsMenu::Screen {
                    public:
                        void show() override;
                };
                class EditTaskChoice : public ConsMenu::Choice {
                    public:
                        EditTaskChoice();
                };



                // The screen for deleting a task.
                class DeleteTaskScreen : public ConsMenu::Screen {
                    public:
                        void show() override;
                };
                class DeleteTaskChoice : public ConsMenu::Choice {
                    public:
                        DeleteTaskChoice();
                };



                // The main menu for editing a subject's tasks.
                class MainMenu : public MainMenuInherit {
                    public:
                        MainMenu(int _subject_index);
                };
            }



            // The screen for saving the current period to the file.
            class SaveScreen : public ConsMenu::Screen {
                public:
                    void show() override;
            };
            class SaveChoice : public ConsMenu::Choice {
                public:
                    SaveChoice();

                    void on_show() override;
            };



            // The main menu which contains all controls for editing a period.
            class MainMenu : public MainMenuInherit {
                public:
                    MainMenu(Backend::AssignMan::Period _period, std::filesystem::path _period_path);

                    void on_ask() override;
            };
        }
    }

}



