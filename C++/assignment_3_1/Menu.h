//
// Created by mohasa18 on 9/7/2020.
//

#ifndef ASSIGNMENT_3_1_MENU_H
#define ASSIGNMENT_3_1_MENU_H
#include <string>
#include <vector>

class MainMenu{
public:
    struct  Options{
        std::string s_1 ;
        std::string s_2 ;
        std::string s_3 ;
        std::string s_4 ;
        std::string s_5 ;
        std::string s_6 ;
        std::string s_7 ;
        std::string s_8 ;
        std::string s_9 ;
        std::string s_10 ;
    };
    Options options;
    MainMenu();
    ~MainMenu();

    void DisplayMenu();

};



#endif //ASSIGNMENT_3_1_MENU_H
