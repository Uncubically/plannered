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
                std::shared_ptr<time_t> time_created;
                std::optional<std::shared_ptr<time_t>> deadline;
                bool is_finished;
                std::optional<std::shared_ptr<time_t>> time_finished;

                Task(
                    std::string _name = "Unnamed Task",
                    std::shared_ptr<time_t> _time_created = Datetime::current_timet_ptr,
                    std::optional<std::shared_ptr<time_t>> _deadline = std::nullopt,
                    bool _is_finished = false,
                    std::optional<std::shared_ptr<time_t>> _time_finished = std::nullopt
                );

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

                std::shared_ptr<time_t> start_date;
                std::optional<std::shared_ptr<time_t>> end_date;

                Period(
                    std::string _name = "Unnamed Period",
                    std::vector<Subject> _subjects = {},
                    std::shared_ptr<time_t> _start_date = Datetime::current_timet_ptr,
                    std::optional<std::shared_ptr<time_t>> _end_date = std::nullopt
                );

                void set_start_date_now();
                void set_end_date_now();

                std::string get_display_str();

                json to_json() override;
                static Period from_json(json json_input);

                void write_json_to_file(std::filesystem::path json_path);
                static Period get_from_json_file(std::filesystem::path json_path);
        };

        extern std::optional<Period> current_period;
    }
}