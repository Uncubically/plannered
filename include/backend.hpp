#pragma once


#include <ctime>
#include <string>
#include <vector>
#include <optional>
#include <memory>
#include <filesystem>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "cpputils.hpp"



namespace Backend {
    class JsonInterface {
        public:
            virtual json to_json() = 0;
    };

    namespace AssignMan {
        // Represents an assignment.
        class Task : public JsonInterface {
            public:
                std::string name;
                time_t time_created;
                std::optional<time_t> deadline;
                bool is_finished;
                std::optional<time_t> time_finished;

                Task(
                    std::string _name = "Unnamed Task",
                    time_t _time_created = Datetime::current_timet,
                    std::optional<time_t> _deadline = std::nullopt,
                    bool _is_finished = false,
                    std::optional<time_t> _time_finished = std::nullopt
                );

                void mark_finished();
                void mark_unfinished();

                json to_json() override;
                static Task from_json(json json_input);

                std::string get_display_str();
                std::string get_display_str_choice();
        };

        // Represents a subject.
        class Subject : public JsonInterface {
            public:
                std::string subject_name;
                std::string subject_abbr;
                std::string subject_code;
                std::optional<std::string> teacher_name;
                std::vector<Task> tasks;

                Subject(std::string _subject_name = "Unnamed Subject", std::string _subject_abbr = "SS", std::string _subject_code = "S01", std::optional<std::string> _teacher_name = std::nullopt, std::vector<Task> _todos = {});

                std::string get_display_str();
                std::string get_display_str_choice();

                json to_json() override;
                static Subject from_json(json json_input);
        };

        // Represents a period of time where the subjects are effective.
        class Period : public JsonInterface {
            public:
                std::string name;
                std::vector<Subject> subjects;

                time_t start_date;
                std::optional<time_t> end_date;

                Period(
                    std::string _name = "Unnamed Period",
                    std::vector<Subject> _subjects = {},
                    time_t _start_date = Datetime::current_timet,
                    std::optional<time_t> _end_date = std::nullopt
                );

                std::string get_display_str();

                json to_json() override;
                static Period from_json(json json_input);

                void write_json_to_file(std::filesystem::path json_path);
                static Period get_from_json_file(std::filesystem::path json_path);
        };

        extern std::optional<Period> current_period;
    }
}