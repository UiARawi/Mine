//
// Created by mohasa18 on 9/7/2020.
//

#ifndef ASSIGNMENT_3_1_TEST_H
#define ASSIGNMENT_3_1_TEST_H

#include <iostream>
#include <string>
#include <vector>

#include "Functions.h"

class Tests : public Common{

public:
    Tests();
    ~Tests();
    std::string course_name;


};

typedef std::vector<Tests> Tests_Vector;
#endif //ASSIGNMENT_3_1_TEST_H
