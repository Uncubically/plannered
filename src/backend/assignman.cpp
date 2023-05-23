#include <ctime>
#include <string>
#include <vector>
#include <optional>
#include <memory>
#include <filesystem>
#include <fstream>

#include "backend.hpp"

#include <nlohmann/json.hpp>
using json = nlohmann::json;



namespace Backend {
    namespace AssignMan {
        Task::Task(
            std::string _name,
            std::shared_ptr<time_t> _time_created,
            std::optional<std::shared_ptr<time_t>> _deadline,
            bool _is_finished,
            std::optional<std::shared_ptr<time_t>> _time_finished
        ) {
            this->name = _name;
            this->time_created = _time_created;
            this->deadline = _deadline;
            this->is_finished = _is_finished;
            this->time_finished = _time_finished;
        }

        json Task::to_json() {
            return {
                {"name", this->name},
                {"time_created", *this->time_created},
                {"deadline", this->deadline.has_value() ? json(**this->deadline) : json(nullptr)},
                {"is_finished", this->is_finished},
                {"time_finished", this->time_finished.has_value() ? json(**this->time_finished) : json(nullptr)}
            };
        }

        Task Task::from_json(json json_input) {
            std::optional<std::shared_ptr<time_t>> deadline;
            if (json_input["deadline"].is_null()) deadline = std::nullopt;
            else deadline = std::make_shared<time_t>(json_input["deadline"].get<time_t>());

            std::optional<std::shared_ptr<time_t>> time_finished;
            if (json_input["time_finished"].is_null()) time_finished = std::nullopt;
            else time_finished = std::make_shared<time_t>(json_input["time_finished"].get<time_t>());


            return Task(
                json_input["name"].get<std::string>(),
                std::make_shared<time_t>(json_input["time_created"].get<time_t>()),
                deadline,
                json_input["is_finished"].get<bool>(),
                time_finished
            );
        }

        std::string Task::get_display_str() {
            std::string deadline_str;
            if (this->deadline.has_value()) {
                deadline_str = Datetime::date_format(this->deadline.value());
            } else {
                deadline_str = "Not set!";
            }

            std::string finished_str;
            if (this->is_finished) finished_str = "Finished on:\t" + Datetime::date_format(this->time_finished.value());
            else finished_str = "Task not finished!";

            return std::string() +
                "Task name:\t" + this->name + "\n" +
                "Time created:\t" + Datetime::date_format(this->time_created) + "\n" +
                "Deadline:\t" + deadline_str + "\n" +
                "Finished on: \t" + finished_str;
        }
        std::string Task::get_display_str_choice() {
            std::string deadline_str;
            if (this->deadline.has_value()) {
                deadline_str = Datetime::date_format(this->deadline.value());
            } else {
                deadline_str = "???";
            }

            return this->name + " (created at " + Datetime::date_format(this->time_created) + ", deadline at " + deadline_str + ")";
        }



        Subject::Subject(std::string _subject_name, std::string _subject_abbr, std::string _subject_code, std::optional<std::string> _teacher_name, std::vector<Task> _todos) {
            this->subject_name = _subject_name;
            this->subject_abbr = _subject_abbr;
            this->subject_code = _subject_code;
            this->teacher_name = _teacher_name;
            this->tasks = _todos;
        }

        std::string Subject::get_display_str() {
            return
                "Subject name:\t" + this->subject_name + "\n" +
                "Abbreviation:\t" + this->subject_abbr + "\n" +
                "Subject code:\t" + this->subject_code + "\n" +
                "Teacher name:\t" + this->teacher_name.value_or("Not set!");
        }

        std::string Subject::get_display_str_choice() {
            return this->subject_name + " (" + this->subject_abbr + ")";
        }

        json Subject::to_json() {
            std::vector<json> todos;
            for (Task todo : this->tasks) todos.push_back(todo.to_json());

            return {
                {"subject_name", this->subject_name},
                {"subject_abbr", this->subject_abbr},
                {"subject_code", this->subject_code},
                {"teacher_name", this->teacher_name.has_value() ? json(*this->teacher_name) : json(nullptr)},
                {"todos", todos}
            };
        }

        Subject Subject::from_json(json json_input) {
            std::vector<Task> todos;
            for (json todo_json : json_input["todos"].get<std::vector<json>>()) todos.push_back(Task::from_json(todo_json));

            std::optional<std::string> teacher_name;
            if (json_input["teacher_name"].is_null()) teacher_name = std::nullopt;
            else teacher_name = json_input["teacher_name"];

            Subject subject{
                json_input["subject_name"].get<std::string>(),
                json_input["subject_abbr"].get<std::string>(),
                json_input["subject_code"].get<std::string>(),
                teacher_name,
                todos
            };

            return subject;
        }



        Period::Period(
            std::string _name,
            std::vector<Subject> _subjects,
            std::shared_ptr<time_t> _start_date,
            std::optional<std::shared_ptr<time_t>> _end_date
        ) {
            this->name = _name;
            this->subjects = _subjects;
            this->start_date = std::move(_start_date);
            this->end_date = std::move(_end_date);
        }

        void Period::set_start_date_now() {
            this->start_date = Datetime::current_timet_ptr;
        }

        void Period::set_end_date_now() {
            this->end_date = Datetime::current_timet_ptr;
        }

        std::string Period::get_display_str() {
            std::string end_date_str;
            if (this->end_date.has_value()) {
                end_date_str = Datetime::date_format(this->end_date.value());
            } else {
                end_date_str = "Not set!";
            }

            std::string display_str =
                "Period name: " + this->name + "\n" +
                "Date info:\n" +
                "- Start date: " + Datetime::date_format(this->start_date) + "\n" +
                "- End date: " + end_date_str + "\n" +
                "Subjects:\n";

            if (this->subjects.size() == 0) {
                display_str += "- No subjects added!";
            } else {
                std::vector<std::string> subject_list_str;
                for (Subject subject : this->subjects) {
                    subject_list_str.push_back("[" + subject.subject_abbr + "] - " + subject.subject_name);
                }

                display_str += StrUtils::join_strs(subject_list_str, "\n");
            }

            return display_str;
        }

        json Period::to_json() {
            std::vector<json> subjects;
            for (Subject subject : this->subjects) subjects.push_back(subject.to_json());

            return {
                {"name", this->name},
                {"start_date", *this->start_date},
                {"end_date", this->end_date.has_value() ? json(**this->end_date) : json(nullptr)},
                {"subjects", subjects}
            };
        }

        Period Period::from_json(json json_input) {
            std::vector<Subject> subjects;
            for (json subject : json_input["subjects"].get<std::vector<json>>()) subjects.push_back(Subject::from_json(subject));

            std::optional<std::shared_ptr<time_t>> end_date;
            if (json_input["end_date"].is_null()) end_date = std::nullopt;
            else end_date = std::make_shared<time_t>(json_input["end_date"].get<time_t>());

            return Period(
                json_input["name"].get<std::string>(),
                subjects,
                std::make_shared<time_t>(json_input["start_date"].get<time_t>()),
                end_date
            );
        }

        void Period::write_json_to_file(std::filesystem::path json_path) {
            std::ofstream json_file;
            json_file.open(json_path);
            json_file << this->to_json().dump(4);
            json_file.close();
        }

        Period Period::get_from_json_file(std::filesystem::path json_path) {
            std::string json_str = File::read_str_file(json_path);
            return from_json(json::parse(json_str));
        }
    }
}