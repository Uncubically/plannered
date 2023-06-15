#include <iostream>

#include "frontend.hpp"

#include "cpputils.hpp"



int main() {
    // Print a line in the console for users to base on if the console window size is enough.
    std::cout
        << "Make the console window bigger if this line wraps around." << std::endl
        << std::endl
        << "=====================================================================================================================" << std::endl
        << std::endl
        << "Press enter to start the program." << std::endl;

    Console::enter_to_exit(false);


    // Starts the animation for the program.
    Frontend::screen_end_anim();

    try {
        // Show the main menu.
        Frontend::MainMenu().show();
    } catch (const std::exception& exc) {
        // When any exception is raised, catch them then send the error to the user for easier bug reporting.
        std::cerr << exc.what() << std::endl;
        std::cout << "The program encountered an error and needs to exit." << std::endl;
        Console::enter_to_exit();
    }

    // yes
    return 0;
}
