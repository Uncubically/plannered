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
            time_t _time_created,
            std::optional<time_t> _deadline,
            bool _is_finished,
            std::optional<time_t> _time_finished
        ) {
            this->name = _name;
            this->time_created = _time_created;
            this->deadline = _deadline;
            this->is_finished = _is_finished;
            this->time_finished = _time_finished;
        }

        void Task::mark_finished() {
            this->is_finished = true;
            this->time_finished = time(0);
        }
        void Task::mark_unfinished() {
            this->is_finished = false;
            this->time_finished = std::nullopt;
        }

        json Task::to_json() {
            return {
                {"name", this->name},
                {"time_created", this->time_created},
                {"deadline", this->deadline.has_value() ? json(this->deadline.value()) : json(nullptr)},
                {"is_finished", this->is_finished},
                {"time_finished", this->time_finished.has_value() ? json(this->time_finished.value()) : json(nullptr)}
            };
        }

        Task Task::from_json(json json_input) {
            std::optional<time_t> deadline;
            if (json_input["deadline"].is_null()) deadline = std::nullopt;
            else deadline = json_input["deadline"].get<time_t>();

            std::optional<time_t> time_finished;
            if (json_input["time_finished"].is_null()) time_finished = std::nullopt;
            else time_finished = json_input["time_finished"].get<time_t>();


            return Task(
                json_input["name"].get<std::string>(),
                json_input["time_created"].get<time_t>(),
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
            if (this->is_finished) finished_str = Datetime::date_format(this->time_finished.value());
            else finished_str = "Task not finished!";

            return Shared::task_important_color.get_str() +
                "Task name:\t" + this->name + "\n" +
                Shared::task_color.get_str() +
                "Time created:\t" + Datetime::date_format(this->time_created) + "\n" +
                "Deadline:\t" + deadline_str + "\n" +
                "Finished on: \t" + finished_str +
                Console::Color::SpecStyle(true).get_str();
        }
        std::string Task::get_display_str_choice() {
            std::string deadline_str;
            if (this->deadline.has_value()) {
                deadline_str = ", deadline at " + Datetime::date_format(this->deadline.value());
            } else {
                deadline_str = ", no deadline";
            }

            std::string finished_str = "";
            if (this->is_finished) finished_str = ", finished";

            return
                Shared::task_color.get_str() +
                this->name +
                " (created at " + Datetime::date_format(this->time_created) + deadline_str + finished_str + ")" +
                Console::Color::SpecStyle(true).get_str();
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
                Shared::subject_important_color.get_str() +
                "Subject name:\t" + this->subject_name + "\n" +
                Shared::subject_color.get_str() +
                "Abbreviation:\t" + this->subject_abbr + "\n" +
                "Subject code:\t" + this->subject_code + "\n" +
                "Teacher name:\t" + this->teacher_name.value_or("Not set!") +
                Console::Color::SpecStyle(true).get_str();
        }

        std::string Subject::get_display_str_choice() {
            return 
                Shared::subject_color.get_str() +
                this->subject_name + " (" + this->subject_abbr + ")" +
                Console::Color::SpecStyle(true).get_str();
        }

        json Subject::to_json() {
            std::vector<json> todos;
            for (Task todo : this->tasks) todos.push_back(todo.to_json());

            return {
                {"subject_name", this->subject_name},
                {"subject_abbr", this->subject_abbr},
                {"subject_code", this->subject_code},
                {"teacher_name", this->teacher_name.has_value() ? json(this->teacher_name.value()) : json(nullptr)},
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
            time_t _start_date,
            std::optional<time_t> _end_date
        ) {
            this->name = _name;
            this->subjects = _subjects;
            this->start_date = _start_date;
            this->end_date = _end_date;
        }

        std::string Period::get_display_str() {
            std::string end_date_str;
            if (this->end_date.has_value()) {
                end_date_str = Datetime::date_format(this->end_date.value());
            } else {
                end_date_str = "Not set!";
            }

            std::string display_str =
                Shared::period_important_color.get_str() +
                "Period name: " + this->name + "\n" +
                Shared::period_color.get_str() +
                "Date info:\n" +
                "- Start date: " + Datetime::date_format(this->start_date) + "\n" +
                "- End date: " + end_date_str + "\n" +
                Shared::subject_color.get_str()+
                "Subjects:\n";

            if (this->subjects.size() == 0) {
                display_str += "- No subjects added!";
            } else {
                std::vector<std::string> subject_list_str;
                for (Subject subject : this->subjects) {
                    subject_list_str.push_back("- " + subject.subject_name + "(" + subject.subject_abbr + ")");
                }

                display_str += StrUtils::join_strs(subject_list_str, "\n");
            }

            display_str += Console::Color::SpecStyle(true).get_str();

            return display_str;
        }

        json Period::to_json() {
            std::vector<json> subjects;
            for (Subject subject : this->subjects) subjects.push_back(subject.to_json());

            return {
                {"name", this->name},
                {"start_date", this->start_date},
                {"end_date", this->end_date.has_value() ? json(this->end_date.value()) : json(nullptr)},
                {"subjects", subjects}
            };
        }

        Period Period::from_json(json json_input) {
            std::vector<Subject> subjects;
            for (json subject : json_input["subjects"].get<std::vector<json>>()) subjects.push_back(Subject::from_json(subject));

            std::optional<time_t> end_date;
            if (json_input["end_date"].is_null()) end_date = std::nullopt;
            else end_date = json_input["end_date"].get<time_t>();

            return Period(
                json_input["name"].get<std::string>(),
                subjects,
                json_input["start_date"].get<time_t>(),
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