#include <iostream>

#include "frontend.hpp"

#include "cpputils.hpp"



int main() {
    std::cout
        << "Make the console window bigger if this line wraps around." << std::endl
        << std::endl
        << "=====================================================================================================================" << std::endl
        << std::endl
        << "Press enter to start the program." << std::endl;

    Console::enter_to_exit(false);

    Frontend::screen_end_anim();

    try {
        Frontend::MainMenu().show();
    } catch (const std::exception& exc) {
        std::cerr << exc.what() << std::endl;
        std::cout << "The program encountered an error and needs to exit." << std::endl;
        Console::enter_to_exit();
    }

    return 0;
}
