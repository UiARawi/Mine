//
// Created by mohasa18 on 9/7/2020.
//
#include <iostream>
#include <vector>
#include "Menu.h"
#include "Commands.h"
#include "students.h"
#include "Test.h"




MainMenu::MainMenu() {

    options.s_1 = "1. Add student";
    options.s_2 = "2. Edit student";
    options.s_3 = "3. Remove student";
    options.s_4 = "4. Add test";
    options.s_5 = "5. Edit test";
    options.s_6 = "6. Remove test";
    options.s_7 = "7. Add/edit test result";
    options.s_8 = "8. Remove test result";
    options.s_9 = "9. Show all info";
    options.s_10 = "10. Exit";
}

MainMenu::~MainMenu(){

}
void MainMenu::DisplayMenu(){

        std::cout << options.s_1 << std::endl;
        std::cout << options.s_2 << std::endl;
        std::cout << options.s_3 << std::endl;
        std::cout  << std::endl;
        std::cout << options.s_4 << std::endl;
        std::cout << options.s_5 << std::endl;
        std::cout << options.s_6 << std::endl;
        std::cout  << std::endl;
        std::cout << options.s_7 << std::endl;
        std::cout << options.s_8 << std::endl;
        std::cout << options.s_9 << std::endl;
        std::cout << options.s_10 << std::endl;

}


