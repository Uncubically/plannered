#pragma once


#include <ctime>
#include <string>
#include <vector>
#include <optional>
#include <memory>
#include <filesystem>

// This header file contains all the definitions for the backend.


#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "shared.hpp"

#include "cpputils.hpp"



// The backend namespace.
namespace Backend {
    // Parent class for all structures that can be turned into a JSON object.
    class JsonInterface {
        public:
            virtual json to_json() = 0;
    };

    // The assignment manager namespace.
    namespace AssignMan {
        // Represents an task.
        class Task : public JsonInterface {
            public:
                // The name of the task.
                std::string name;

                // What time the task was assigned.
                time_t time_created;

                // The deadline of the project. If empty, there is no set deadline.
                std::optional<time_t> deadline;

                // Tells if the task is finished or not. true = the task is finished.
                bool is_finished;

                // The time as to when the task is finished. If empty, the task is not finished.
                std::optional<time_t> time_finished;

                // Constructor.
                Task(
                    std::string _name = "Unnamed Task",
                    time_t _time_created = Datetime::current_timet,
                    std::optional<time_t> _deadline = std::nullopt,
                    bool _is_finished = false,
                    std::optional<time_t> _time_finished = std::nullopt
                );

                // Marks the task as finished.
                void mark_finished();

                // Marks the task as unfinished.
                void mark_unfinished();

                json to_json() override;
                static Task from_json(json json_input);

                // Gets the string for displaying information about the task.
                std::string get_display_str();

                // Gets the string for displaying the task as a choice.
                std::string get_display_str_choice();
        };

        // Represents a subject.
        class Subject : public JsonInterface {
            public:
                // The name of the subject.
                std::string subject_name;

                // The abbreviation of the subject.
                std::string subject_abbr;

                // The subject's code.
                std::string subject_code;

                // The name of the teacher. If empty, the teacher is not specified.
                std::optional<std::string> teacher_name;

                // The lists of tasks in the subject.
                std::vector<Task> tasks;

                // Constructor.
                Subject(std::string _subject_name = "Unnamed Subject", std::string _subject_abbr = "SS", std::string _subject_code = "S01", std::optional<std::string> _teacher_name = std::nullopt, std::vector<Task> _todos = {});

                // Gets the string for displaying information about the subject.
                std::string get_display_str();

                // Gets the string for displaying the subject as a choice.
                std::string get_display_str_choice();

                json to_json() override;
                static Subject from_json(json json_input);
        };

        // Represents a period of time where the subjects are effective.
        class Period : public JsonInterface {
            public:
                // The name of the period.
                std::string name;

                // The list of subjects in that period.
                std::vector<Subject> subjects;

                // The start of the period.
                time_t start_date;

                // The end of the period. If blank, no end date is specified.
                std::optional<time_t> end_date;

                // Constructor.
                Period(
                    std::string _name = "Unnamed Period",
                    std::vector<Subject> _subjects = {},
                    time_t _start_date = Datetime::current_timet,
                    std::optional<time_t> _end_date = std::nullopt
                );

                // Gets the string for displaying information about the period.
                std::string get_display_str();

                json to_json() override;
                static Period from_json(json json_input);

                // Writes the JSON to a file.
                void write_json_to_file(std::filesystem::path json_path);
                // Gets the period from a file.
                static Period get_from_json_file(std::filesystem::path json_path);
        };

        // The currently opened period. If blank, no period is opened.
        extern std::optional<Period> current_period;
    }
}