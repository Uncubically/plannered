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
            virtual json to_json() {};
            static JsonInterface from_json(json json_input) {};
    };

    namespace AssignMan {
        // Represents an assignment.
        class Todo : public JsonInterface {
            public:
                std::string name;
                time_t time_created;
                time_t deadline;
                bool is_finished;
                std::optional<time_t> time_finished;

                Todo(
                    std::string _name,
                    time_t _time_created,
                    time_t _deadline,
                    bool _is_finished = false,
                    std::optional<time_t> _time_finished = std::nullopt
                );

                json to_json() override;
                static Todo from_json(json json_input);
        };

        // Represents a subject.
        class Subject : public JsonInterface {
            public:
                std::string subject_name;
                std::string subject_abbr;
                std::string subject_code;
                std::optional<std::string> teacher_name;

                std::vector<Todo> todos;

                Subject(std::string _subject_name, std::string _subject_abbr, std::string _subject_code, std::optional<std::string> _teacher_name = std::nullopt);

                std::string get_display_str();

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
                    std::string _name,
                    std::vector<Subject> _subjects = {},
                    std::shared_ptr<time_t>& _start_date = Datetime::current_timet_ptr,
                    std::optional<std::shared_ptr<time_t>> _end_date = std::nullopt
                );

                void set_start_date_now();
                void set_end_date_now();

                std::string get_display_str();

                json to_json() override;
                static Period from_json(json json_input);

                void write_json_to_file(std::filesystem::path json_path);
        };

        extern std::optional<Period> current_period;
    }
}