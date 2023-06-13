#include "shared.hpp"

#include "cpputils.hpp"



namespace Shared {
    bool enable_fancy_colors = true;

    Console::Color::SpecStyle period_color = Console::Color::SpecStyle(false, Console::Color::light_green, Console::Color::black, true);
    Console::Color::SpecStyle period_important_color = Console::Color::SpecStyle(false, Console::Color::black, Console::Color::light_green, true);
    Console::Color::SpecStyle get_period_important_color() {
        return enable_fancy_colors ? period_important_color : period_color;
    }

    Console::Color::SpecStyle subject_color = Console::Color::SpecStyle(false, Console::Color::yellow, Console::Color::black, true);
    Console::Color::SpecStyle subject_important_color = Console::Color::SpecStyle(false, Console::Color::black, Console::Color::yellow, true);
    Console::Color::SpecStyle get_subject_important_color() {
        return enable_fancy_colors ? subject_important_color : subject_color;
    }

    Console::Color::SpecStyle task_color = Console::Color::SpecStyle(false, Console::Color::light_blue, Console::Color::black, true);
    Console::Color::SpecStyle task_important_color = Console::Color::SpecStyle(false, Console::Color::black, Console::Color::light_blue, true);
    Console::Color::SpecStyle get_task_important_color() {
        return enable_fancy_colors ? task_important_color : task_color;
    }
}