#include <iostream>

#include "frontend.hpp"

#include "cpputils.hpp"



int main() {
    std::cout
        << "Please maximize the console window so it takes up your whole screen." << std::endl
        << "Press enter to start the program." << std::endl;

    Console::enter_to_exit(false);

    try {
        Frontend::MainMenu().show();
    } catch (const std::exception& exc) {
        std::cerr << exc.what() << std::endl;
        std::cout << "The program encountered an error and needs to exit." << std::endl;
        Console::enter_to_exit();
    }

    return 0;
}
