#include <ctime>
#include <string>
#include <vector>
#include <optional>
#include <memory>

#include "backend.hpp"



namespace Backend {
    namespace AssignMan {
        Todo::Todo(
            std::string _name,
            time_t& _time_created,
            time_t& _deadline,
            bool _is_finished,
            std::optional<time_t> _time_finished
        ) {
            this->name = _name;
            this->time_created = _time_created;
            this->deadline = _deadline;
            this->is_finished = _is_finished;
            this->time_finished = _time_finished;
        }



        Subject::Subject(std::string _subject_name, std::string _subject_abbr, std::string _subject_code, std::optional<std::string> _teacher_name) {
            this->subject_name = _subject_name;
            this->subject_abbr = _subject_abbr;
            this->subject_code = _subject_code;
            this->teacher_name = _teacher_name;
        }
        std::string Subject::get_display_str() {
            return
                "Subject name:\t" + this->subject_name + "\n" +
                "Abbreviation:\t" + this->subject_abbr + "\n" +
                "Subject code:\t" + this->subject_code + "\n" +
                "Teacher name:\t" + this->teacher_name.value_or("Not set!");
        }



        Period::Period(
            int _index,
            std::vector<Subject> _subjects,
            std::shared_ptr<time_t>& _start_date,
            std::optional<std::shared_ptr<time_t>> _end_date
        ) {
            this->index = _index;
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
            if (this->end_date == std::nullopt) {
                end_date_str = "Not set!";
            } else {
                end_date_str = Datetime::date_format(*this->end_date);
            }

            std::string display_str =
                "Period #" + std::to_string(index) + "\n" +
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

        std::optional<Period> current_period = std::nullopt;
    }
}