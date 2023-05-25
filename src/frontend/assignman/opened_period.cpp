#include <iostream>
#include <string>

#include "frontend.hpp"

#include "backend.hpp"
#include "shared.hpp"



namespace Frontend::AssignMan::OpenedPeriod {
    std::optional<Backend::AssignMan::Period> current_period = std::nullopt;
    std::optional<std::filesystem::path> current_period_path;

    bool has_changes = false;



    int count_unfinished_tasks() {
        int count = 0;
        for (Backend::AssignMan::Subject& subject : current_period.value().subjects) {
            for (Backend::AssignMan::Task& task : subject.tasks) {
                if (!task.is_finished) count++;
            }
        }

        return count;
    }



    std::optional<int> send_prompt_choose_subjects(
        std::string prompt,
        bool is_optional,
        bool show_optional_text,
        std::optional<std::string> blank_input
    ) {
        std::vector<std::string> choices;
        for (Backend::AssignMan::Subject subject : current_period.value().subjects) choices.push_back(subject.get_display_str_choice());

        std::optional<int> choice = Console::Prompt::send_prompt_choice(
            prompt,
            choices,
            is_optional, show_optional_text, blank_input
        );

        if (!choice.has_value()) return std::nullopt;
        return choice.value();
    }



    void ShowPeriodInfoScreen::show() {
        Backend::AssignMan::Period& period = current_period.value();

        std::cout
            << "Current period information!" << std::endl
            << std::endl
            << period.get_display_str()
            << std::endl << std::endl;

        Console::enter_to_exit();
        screen_end_anim();
    }
    ShowPeriodInfoChoice::ShowPeriodInfoChoice() : ConsMenu::Choice("Show Current Period Information", Shared::period_important_color) {
        this->set_screen<ShowPeriodInfoScreen>();
    }



    void EditPeriodScreen::show() {
        Backend::AssignMan::Period& period = current_period.value();
        int attribute_idx = Console::Prompt::send_prompt_choice(
            "Input the attribute of the current period that you want to edit:",
            {"Name", "Start Date", "End Date"}
        ).value();

        if (attribute_idx == 0) {
            period.name = Console::Prompt::send_prompt("Input new name of period: ").value();
        } else if (attribute_idx == 1) {
            period.start_date = Datetime::ask_date("Input the new start date of the period:");
        } else if (attribute_idx == 2) {
            if (period.end_date.has_value()) {
                int end_date_set_idx = Console::Prompt::send_prompt_choice(
                    "Would you like to set the end date or clear it so that the period doesn't have an end date?",
                    {"Set End Date", "Clear End Date"}
                ).value();

                if (end_date_set_idx == 0) period.end_date = Datetime::ask_date("Input the new end date of the period: ");
                else period.end_date = std::nullopt;
            } else period.end_date = Datetime::ask_date("Input the new end date of the period: ");
        }


        std::cout
            << std::endl << std::endl
            << "Period edited!" << std::endl
            << std::endl
            << period.get_display_str()
            << std::endl << std::endl;


        has_changes = true;
        Console::enter_to_exit();
        screen_end_anim();
    }
    EditPeriodChoice::EditPeriodChoice() : ConsMenu::Choice("Edit Current Period", Shared::period_color) {
        this->set_screen<EditPeriodScreen>();
    }



    void ShowSubjectsScreen::show() {
        Backend::AssignMan::Period& period = current_period.value();
        if (period.subjects.size() != 0) {
            std::cout << "These are the subjects available for the period \"" << period.name << "\":" << std::endl << std::endl << std::endl;

            for (Backend::AssignMan::Subject subject : period.subjects) {
                std::cout << subject.get_display_str() << std::endl << std::endl;
            }
        } else {
            std::cout << "There are no subjects in the period." << std::endl;
        }

        std::cout << std::endl;
        Console::enter_to_exit();
        screen_end_anim();
    }
    ShowSubjectsChoice::ShowSubjectsChoice() : ConsMenu::Choice("Show All Subjects", Shared::subject_important_color) {
        this->set_screen<ShowSubjectsScreen>();
    }



    void CreateSubjectScreen::show() {
        std::cout << "Add subject" << std::endl << std::endl;

        std::string subject_name = Console::Prompt::send_prompt("Input the name of the subject: ").value();
        std::string subject_abbr = Console::Prompt::send_prompt("Input the abbreviation of the subject: ").value();
        std::string subject_code = Console::Prompt::send_prompt("Input the subject code: ").value();
        std::optional<std::string> teacher_name = Console::Prompt::send_prompt("Input the name of the teacher: ", true);

        Backend::AssignMan::Subject subject(subject_name, subject_abbr, subject_code, teacher_name);
        current_period.value().subjects.push_back(subject);

        std::cout << std::endl << std::endl;

        std::cout
            << "Created subject!" << std::endl
            << subject.get_display_str() << std::endl
            << std::endl;

        has_changes = true;
        Console::enter_to_exit();
        screen_end_anim();
    }
    CreateSubjectChoice::CreateSubjectChoice() : ConsMenu::Choice("Create Subject", Shared::subject_color) {
        this->set_screen<CreateSubjectScreen>();
    }



    void EditSubjectScreen::show() {
        int subject_idx = send_prompt_choose_subjects("Select the subject you want to choose:").value();
        Backend::AssignMan::Subject& subject = current_period.value().subjects[subject_idx];

        int attribute_idx = Console::Prompt::send_prompt_choice(
            "Input the attribute that you want to edit:",
            {"Subject Name", "Subject Abbreviation", "Subject Code", "Teacher Name"}
        ).value();

        if (attribute_idx == 0) {
            subject.subject_name = Console::Prompt::send_prompt("Input the new name of the subject: ").value();
        } else if (attribute_idx == 1) {
            subject.subject_abbr = Console::Prompt::send_prompt("Input the new abbreviation of the subject:").value();
        } else if (attribute_idx == 2) {
            subject.subject_code = Console::Prompt::send_prompt("Input the new subject code:").value();
        } else if (attribute_idx == 3) {
            if (subject.teacher_name.has_value()) {
                int teacher_name_set_idx = Console::Prompt::send_prompt_choice(
                    "Would you like to set the teacher name or clear it so the subject doesn't have a teacher name?",
                    {"Set Teacher Name", "Clear Teacher Name"}
                ).value();

                if (teacher_name_set_idx == 0) subject.teacher_name = Console::Prompt::send_prompt("Input the new teacher name: ").value();
                else subject.teacher_name = std::nullopt;
            } else subject.teacher_name = Console::Prompt::send_prompt("Input the new teacher name: ").value();
        }


        std::cout
            << std::endl << std::endl
            << "Subject edited!" << std::endl
            << std::endl
            << subject.get_display_str()
            << std::endl << std::endl;

        has_changes = true;
        Console::enter_to_exit();
        screen_end_anim();
    }
    EditSubjectChoice::EditSubjectChoice() : ConsMenu::Choice("Edit Subject", Shared::subject_color) {
        this->set_screen<EditSubjectScreen>();
    }



    void DeleteSubjectScreen::show() {
        Backend::AssignMan::Period& period = current_period.value();
        if (period.subjects.size() == 0) {
            std::cout << "There are no subjects to delete." << std::endl;
            Console::enter_to_exit();
            return;
        }

        int subject_idx = send_prompt_choose_subjects("Choose a subject to delete: ").value();
        period.subjects.erase(period.subjects.begin() + subject_idx);

        std::cout << "Subject deleted." << std::endl << std::endl;

        has_changes = true;
        Console::enter_to_exit();
        screen_end_anim();
    }
    DeleteSubjectChoice::DeleteSubjectChoice() : ConsMenu::Choice("Delete Subject", Shared::subject_color) {
        this->set_screen<DeleteSubjectScreen>();
    }



    void ShowUnfinishedTasksScreen::show() {
        Backend::AssignMan::Period& period = current_period.value();

        std::vector<std::string> unfinished_task_strs;
        for (Backend::AssignMan::Subject subject : period.subjects) {
            std::vector<Backend::AssignMan::Task> unfinished_tasks;
            for (Backend::AssignMan::Task task : subject.tasks) {
                if (!task.is_finished) unfinished_tasks.push_back(task);
            }

            if (unfinished_tasks.size() != 0) {
                std::string output_str = subject.subject_name + ":\n\n";
                for (Backend::AssignMan::Task task : unfinished_tasks) {
                    output_str += task.get_display_str() + "\n\n";
                }

                unfinished_task_strs.push_back(output_str);
            }
        }

        if (unfinished_task_strs.size() == 0) {
            std::cout << "You have no unfinished tasks today. Congrats!" << std::endl;
            Console::enter_to_exit();
            return;
        }

        std::cout << "Your unfinished tasks:" << std::endl << std::endl << std::endl;
        for (std::string unfinished_task_str : unfinished_task_strs) {
            std::cout << unfinished_task_str << std::endl << std::endl;
        }

        std::cout << std::endl;
        Console::enter_to_exit();
        screen_end_anim();
    }
    ShowUnfinishedTasksChoice::ShowUnfinishedTasksChoice() : ConsMenu::Choice("Show Unfinished Tasks", Shared::task_important_color) {
        this->set_screen<ShowUnfinishedTasksScreen>();
    }



    void ManageTasksScreen::show() {
        if (current_period.value().subjects.size() == 0) {
            std::cout << "There are no subjects in this period to manage." << std::endl;
            Console::enter_to_exit();
            return;
        }

        int subject_idx = send_prompt_choose_subjects("Please select the subject you want to manage.").value();

        screen_end_anim();
        ManageTasks::MainMenu(subject_idx).show();
    }
    ManageTasksChoice::ManageTasksChoice() : ConsMenu::Choice("Manage Tasks", Shared::task_important_color) {
        this->set_screen<ManageTasksScreen>();
    }



    void SaveScreen::show() {
        std::cout << "Saving period \"" << current_period.value().name << "\"..." << std::endl;

        current_period.value().write_json_to_file(current_period_path.value());

        has_changes = false;
        std::cout << "Saved!" << std::endl;

        Console::enter_to_exit();
        screen_end_anim();
    }
    SaveChoice::SaveChoice() : ConsMenu::Choice("Save", Shared::period_important_color) {
        this->set_screen<SaveScreen>();
    }
    void SaveChoice::on_show() {
        Console::Color::SpecStyle unsaved_changes_color = Console::Color::SpecStyle(
            false,
            Console::Color::light_red,
            Console::Color::black,
            true, true, true
        );

        Console::Color::SpecStyle no_changes_color = Console::Color::SpecStyle(
            false,
            Console::Color::light_black,
            Console::Color::black,
            true
        );

        Console::Color::SpecStyle reset = Console::Color::SpecStyle(true);
    
        if (has_changes) {
            this->description = std::string("Save") + unsaved_changes_color.get_str() + " -- UNSAVED CHANGES!" + reset.get_str();
        } else {
            this->description = std::string("Save") + no_changes_color.get_str() + " -- No changes to save." + reset.get_str();
        }
    }



    MainMenu::MainMenu(Backend::AssignMan::Period _period, std::filesystem::path _period_path) {
        current_period = _period;
        current_period_path = _period_path;
        this->title = "Manage Period.";


        this->add_choice<ShowPeriodInfoChoice>();
        this->add_choice<EditPeriodChoice>();
        this->add_choice<ShowSubjectsChoice>();
        this->add_choice<CreateSubjectChoice>();
        this->add_choice<EditSubjectChoice>();
        this->add_choice<DeleteSubjectChoice>();
        this->add_choice<ShowUnfinishedTasksChoice>();
        this->add_choice<ManageTasksChoice>();
        this->add_choice<SaveChoice>();
    };
    void MainMenu::on_ask() {
        this->desc = "Opened Period: " + current_period.value().name;

        int unfinished_tasks_count = count_unfinished_tasks();
        if (unfinished_tasks_count != 0) {
            this->desc +=
                "\n" +
                Console::Color::SpecStyle(false, Console::Color::black, Console::Color::light_red, true).get_str() +
                "You have " + std::to_string(unfinished_tasks_count) + " task(s) left unfinished!" +
                Console::Color::SpecStyle(true).get_str();
        }
    }
}