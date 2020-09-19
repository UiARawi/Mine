//
// Created by mohasa18 on 9/7/2020.
//
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <limits>
#include <algorithm>

#include "Commands.h"


Results results;
Class_Vector class_vector;
Tests_Vector tests_vector;
static int j = 1;
static int k = 1;

Cmd::Cmd(int command_id,const std::string name, void (*function)()){

    this->command_id = command_id;
    this->name = name;
    this->function = function;
}

CommandProcessor::CommandProcessor() {


}
void CommandProcessor::Add(Cmd command_) {

    this->cmd.push_back(command_);


}

void AddStudent(){
    Students new_student;
    new_student.id = j;
    std::cout << "Please Enter the name:" << std::endl;
    getline(std::cin, new_student.name);
    std::cout << "Please Enter the email:" << std::endl;
    getline(std::cin, new_student.Date_email);
    class_vector.push_back(new_student);

    j++;
}

void EditStudent(){

    int count = 1;
    std::cout << "Student details:" << std::endl;
    for (auto& itr : class_vector)
    {
        std::cout << "student id = " <<  itr.id << std::endl;
        count++;
    }
    std::cout << count <<  ". Back" << std::endl;
    std::cout << "Please choose the student by id:" << std::endl;
    int id_to_delete = 0;
    std::cin >> id_to_delete ;
    std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n') ;
    if (id_to_delete != count) {
        for (auto &itr_id : class_vector) {
            if (itr_id.id == id_to_delete) {
                std::cout << "Please Enter the name:" << std::endl;
                getline(std::cin, itr_id.name);
                std::cout << "Please Enter the email:" << std::endl;
                getline(std::cin, itr_id.Date_email);
            }

        }
    }else{
        return;
    }
}

void RemoveStudent(){
    int count = 1;
    std::cout << "Student details:" << std::endl;
    for (auto& itr : class_vector)
    {
        std::cout << "student id = " <<  itr.id << std::endl;
        count++;
    }
    std::cout << count <<  ". Back" << std::endl;
    std::cout << "Please choose the student by id:" << std::endl;
    int id_to_delete = 0;
    std::cin >> id_to_delete ;
    std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n') ;
    if (id_to_delete != count) {
        class_vector.erase(
                std::remove_if(class_vector.begin(), class_vector.end(), [&id_to_delete](const Students &stu) -> bool {
                    return (stu.id == id_to_delete);
                }), class_vector.end());

        for (auto &rst: results) {
            if (rst.first == id_to_delete) results.erase(rst.first);
        }
    }else{
        return;
    }

}

void AddTest(){

    Tests new_test;
    new_test.id = k;
    std::cout << "Please Enter the course name:" << std::endl;
    getline(std::cin, new_test.course_name);
    std::cout << "Please Enter the test name:" << std::endl;
    getline(std::cin, new_test.name);
    std::cout << "Please Enter the Date YYYY.MM.DD :" << std::endl;
    getline(std::cin, new_test.Date_email);
    tests_vector.push_back(new_test);
    k++;

}

void EditTest(){
    int count = 1;
    std::cout << "Test details:" << std::endl;
    for (auto& itr_test : tests_vector)
    {
        std::cout <<"test id = " << itr_test.id << std::endl;
        count++;
    }
    std::cout << count <<  ". Back" << std::endl;
    std::cout << "Please choose the student by id:" << std::endl;
    int test_id_to_edit = 0;
    std::cin >> test_id_to_edit ;
    std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n') ;
    if (test_id_to_edit != count) {
        std::vector<Tests>::iterator itr_edit_test = std::find_if(tests_vector.begin(), tests_vector.end(),
                                                                  [&test_id_to_edit](const Tests &lamb_test) -> bool {
                                                                      return lamb_test.id == test_id_to_edit;
                                                                  });
        std::cout << "Please Enter the course name:" << std::endl;
        getline(std::cin, itr_edit_test->course_name);
        std::cout << "Please Enter the test name:" << std::endl;
        getline(std::cin, itr_edit_test->name);
        std::cout << "Please Enter the date YYYY.MM.DD :" << std::endl;
        getline(std::cin, itr_edit_test->Date_email);
    }else{
        return;
    }

}

void RemoveTest(){
    int count = 1;
    std::cout << "Test details:" << std::endl;
    for (auto& itr_test : tests_vector)
    {
        std::cout <<"test id = " << itr_test.id << std::endl;
        count++;
    }
    std::cout << "Please choose the test by id:" << std::endl;
    int test_id_to_delete = 0;
    std::cin >> test_id_to_delete ;
    std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n') ;

    if (test_id_to_delete != count) {
        tests_vector.erase(std::remove_if(tests_vector.begin(), tests_vector.end(),
                                          [&test_id_to_delete](const Tests &tes) -> bool {
                                              return (tes.id == test_id_to_delete);
                                          }), tests_vector.end());
    }else{
        return;
    }

}

void Add_Edit_Test_Result() {
    int count = 1;
    std::cout << "Student details:" << std::endl;
    for (auto &itr : class_vector) {
        std::cout << "student id = " << itr.id << std::endl;
        count++;
    }
    std::cout << count << ". Back" << std::endl;
    std::cout << "Please enter student id:" << std::endl;
    int stud_id_to_AddEdit_result = 0;
    std::cin >> stud_id_to_AddEdit_result;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


    if (stud_id_to_AddEdit_result != count){count = 1;
    std::cout << "Test details:" << std::endl;
    for (auto &itr_test : tests_vector) {
        std::cout << "test id = " << itr_test.id << std::endl;
        count++;
    }
    std::cout << count << ". Back" << std::endl;

    std::cout << "Please enter test id:" << std::endl;
    int test_id_to_AddEdit_result = 0;
    std::cin >> test_id_to_AddEdit_result;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (test_id_to_AddEdit_result != count) {
        std::cout << "Please enter grade:" << std::endl;
        std::string grade;
        getline(std::cin, grade);

        results[stud_id_to_AddEdit_result][test_id_to_AddEdit_result] = grade;
    }
}

}
void Remove_Test_Result(){
    std::cout << "Please enter student id:" << std::endl;
    int stud_id_to_remove_result = 0;
    std::cin >> stud_id_to_remove_result ;
    std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n') ;

    std::cout << "Please enter test id:" << std::endl;
    int test_id_remove_result = 0;
    std::cin >> test_id_remove_result ;
    std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n') ;

    results[stud_id_to_remove_result][test_id_remove_result] = "0" ;



}

void ShowInfo() {

    std::cout << "Student details:" << std::endl;
    for (auto &itr : class_vector) {
        std::cout << "student id = " << itr.id << ", name = " << itr.name << ", email = " << itr.Date_email
                  << std::endl;

    }
    std::cout << std::endl;
    std::cout << "Test details:" << std::endl;
    for (auto &itr_test : tests_vector) {
        std::cout << "test id = " << itr_test.id << ", course name = " << itr_test.course_name << ", test name = "
                  << itr_test.name << ", date = " << itr_test.Date_email << std::endl;

    }

    std::cout << std::endl;

    // Iterate map [student id][test id] = grade
    //         map [first][second.first] = second.second
    std::cout << "Test results:" << std::endl;
    for (const auto &itr_result: results) {
        // Iterate second.first = second.second
        for (const auto &course_test_names: itr_result.second) {
            // iterate test_vector and check the test id then prints the info
            for (const auto &itr_test_info : tests_vector)
                if (itr_test_info.id == course_test_names.first) {
                    std::cout<< "student id = " << itr_result.first << ", course name = " << itr_test_info.course_name << ", test id = "
                              << course_test_names.first << ", test name = " << itr_test_info.name << ", grade = " << course_test_names.second << std::endl;
                }

        }
    }


}
