#include "cpputils.hpp"



namespace Shared {
    extern bool enable_fancy_colors;

    extern Console::Color::SpecStyle period_color;
    extern Console::Color::SpecStyle period_important_color;
    Console::Color::SpecStyle get_period_important_color();

    extern Console::Color::SpecStyle subject_color;
    extern Console::Color::SpecStyle subject_important_color;
    Console::Color::SpecStyle get_subject_important_color();

    extern Console::Color::SpecStyle task_color;
    extern Console::Color::SpecStyle task_important_color;
    Console::Color::SpecStyle get_task_important_color();
}