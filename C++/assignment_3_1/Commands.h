//
// Created by mohasa18 on 9/7/2020.
//

#ifndef ASSIGNMENT_3_1_COMMANDS_H
#define ASSIGNMENT_3_1_COMMANDS_H

#include <string>
#include <vector>

#include "students.h"
#include "Test.h"


class Cmd {
public:
    Cmd(int command_id,const std::string name, void (*function)());

    std::string name;
    int command_id;
    void (*function)();
};

class CommandProcessor{
public:

    CommandProcessor();

    void Add(Cmd command_);

    std::vector<Cmd> cmd;
};

void AddStudent();
void EditStudent();
void RemoveStudent();

void AddTest();
void EditTest();
void RemoveTest();

void Add_Edit_Test_Result();
void Remove_Test_Result();
void ShowInfo();


typedef std::map <int , std::string> Test_Grade_Map;
// todo map[Student_id][test_id] = grade;
typedef std::map <int , Test_Grade_Map> Results;
#endif //ASSIGNMENT_3_1_COMMANDS_H
