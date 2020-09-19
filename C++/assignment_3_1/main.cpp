#include <iostream>
#include <cmath>
#include <limits>
#include <map>
#include <vector>
#include <memory>
#include <string>
#include "students.h"
#include "Test.h"
#include "Functions.h"
#include "Commands.h"
#include "Menu.h"







int main() {

    Cmd cmd1(1, "Add student",  &AddStudent );
    Cmd cmd2(2, "EditStudent", &EditStudent);
    Cmd cmd3(3, "RemoveStudent", &RemoveStudent);

    Cmd cmd4(4, "AddTest", &AddTest);
    Cmd cmd5(5, "EditTest", &EditTest);
    Cmd cmd6(6, "RemoveTest", &RemoveTest);

    Cmd cmd7(7, "Add_Edit_Test_Result", &Add_Edit_Test_Result);
    Cmd cmd8(8, "Remove_Test_Result", &Remove_Test_Result);
    Cmd cmd9(9, "ShowInfo", &ShowInfo);

    CommandProcessor cp;

    cp.Add(cmd1);
    cp.Add(cmd2);
    cp.Add(cmd3);
    cp.Add(cmd4);
    cp.Add(cmd5);
    cp.Add(cmd6);
    cp.Add(cmd7);
    cp.Add(cmd8);
    cp.Add(cmd9);

    MainMenu mainMenu;
    mainMenu.DisplayMenu();
    int select = 0;
    std::cin >> select;
    std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n') ;
    while (select != 10){


        for (const auto itr : cp.cmd) {
//            std::cout << itr.command_id << "  " << itr.name  << std::endl;
            if ( itr.command_id == select)
                itr.function();
        }

        MainMenu mainMenu;
        mainMenu.DisplayMenu();
        std::cin >> select;
        std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n') ;
    }

    return 0;
}
