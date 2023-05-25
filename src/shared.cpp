#include "shared.hpp"

#include "cpputils.hpp"



namespace Shared {
    Console::Color::SpecStyle period_color = Console::Color::SpecStyle(false, Console::Color::light_green, Console::Color::black, true);
    Console::Color::SpecStyle period_important_color = Console::Color::SpecStyle(false, Console::Color::black, Console::Color::light_green, true);

    Console::Color::SpecStyle subject_color = Console::Color::SpecStyle(false, Console::Color::yellow, Console::Color::black, true);
    Console::Color::SpecStyle subject_important_color = Console::Color::SpecStyle(false, Console::Color::black, Console::Color::yellow, true);

    Console::Color::SpecStyle task_color = Console::Color::SpecStyle(false, Console::Color::light_blue, Console::Color::black, true);
    Console::Color::SpecStyle task_important_color = Console::Color::SpecStyle(false, Console::Color::black, Console::Color::light_blue, true);
}