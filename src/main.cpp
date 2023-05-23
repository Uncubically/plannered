#include <iostream>

#include "frontend.hpp"

#include "cpputils.hpp"



int main() {
    std::cout
        << "Please maximize the console window so it takes up your whole screen." << std::endl
        << "Press enter to start the program." << std::endl;

    Console::enter_to_exit(false);

    Frontend::MainMenu().show();

    return 0;
}
