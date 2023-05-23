#include <iostream>

#include "frontend.hpp"

#include "backend.hpp"
#include "cppconsmenu.hpp"
#include "cpputils.hpp"



namespace Frontend::AssignMan::OpenedPeriod::ManageSubjs {
    std::optional<int> subject_index = std::nullopt;



    Backend::AssignMan::Subject& get_subject() {
        return current_period.value().subjects[subject_index.value()];
    }



    std::optional<int> send_prompt_choose_task(
        std::string prompt,
        bool is_optional,
        bool show_optional_text,
        std::optional<std::string> blank_input
    ) {
        std::vector<std::string> choices;
        for (Backend::AssignMan::Task task : get_subject().tasks) choices.push_back(task.get_display_str_choice());

        std::optional<int> choice = Console::Prompt::send_prompt_choice(
            prompt,
            choices,
            is_optional, show_optional_text, blank_input
        );

        if (!choice.has_value()) return std::nullopt;
        return choice.value();
    }



    void ShowTasksUnfinishedScreen::show() {
        Backend::AssignMan::Subject& subject = get_subject();

        std::vector<Backend::AssignMan::Task> unfinished_tasks;
        for (Backend::AssignMan::Task task : subject.tasks) if (!task.is_finished) unfinished_tasks.push_back(task);


        if (unfinished_tasks.size() != 0) {
            std::cout << "These are the unfinished tasks available for the subject \"" << subject.subject_name << "\":" << std::endl << std::endl << std::endl;

            for (Backend::AssignMan::Task task : subject.tasks) {
                if (!task.is_finished) std::cout << task.get_display_str() << std::endl << std::endl;
            }
        } else {
            std::cout << "There are no unfinished tasks in the subject." << std::endl;
        }

        std::cout << std::endl;
        Console::enter_to_exit();
    }
    ShowTasksUnfinishedChoice::ShowTasksUnfinishedChoice() : ConsMenu::Choice("Show Unfinished Tasks") {
        this->set_screen<ShowTasksUnfinishedScreen>();
    }



    void CreateTaskScreen::show() {
        Backend::AssignMan::Subject& subject = get_subject();
        std::cout << "A task is like an assignment, a quiz, or anything you would like to assign yourself." << std::endl << std::endl;

        std::string name = Console::Prompt::send_prompt("Input the name of the task: ").value();
        std::shared_ptr<time_t> time_created = Datetime::ask_date("Input the start date of the task: ");

        std::optional<std::shared_ptr<time_t>> deadline;
        if (Console::Prompt::send_prompt_yn("Would you like to input a deadline?")) {
            deadline = Datetime::ask_date("Input the deadline of the task: ");
        } else deadline = std::nullopt;


        Backend::AssignMan::Task task(name, time_created, deadline);
        subject.tasks.push_back(task);

        std::cout
            << "Created task!" << std::endl
            << std::endl
            << task.get_display_str()
            << std::endl;

        Console::enter_to_exit();
    }
    CreateTaskChoice::CreateTaskChoice() : ConsMenu::Choice("Create Task") {
        this->set_screen<CreateTaskScreen>();
    }



    void DeleteTaskScreen::show() {
        Backend::AssignMan::Subject& subject = get_subject();
        if (subject.tasks.size() == 0) {
            std::cout << "There are no tasks in the subject to be deleted." << std::endl;
            Console::enter_to_exit();
            return;
        }

        int task_idx = send_prompt_choose_task("Select a task to delete:").value();
        subject.tasks.erase(subject.tasks.begin() + task_idx);
        std::cout << "Task deleted." << std::endl;
        Console::enter_to_exit();
    }
    DeleteTaskChoice::DeleteTaskChoice() : ConsMenu::Choice("Delete Task") {
        this->set_screen<DeleteTaskScreen>();
    }



    MainMenu::MainMenu(int _subject_index) {
        subject_index = _subject_index;

        this->add_choice<ShowTasksUnfinishedChoice>();
        this->add_choice<CreateTaskChoice>();
        this->add_choice<DeleteTaskChoice>();
    }
}