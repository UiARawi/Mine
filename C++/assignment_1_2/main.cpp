#include <iostream>

int main() {
    std::string name;
    int age;
    std::cout << "Please enter your name" << std::endl;
    std::cin >> name;
    std::cout << "Please enter your age in years" << std::endl;
    std::cin >> age;
    std::cout << "Hello, " << name << "!"<<std::endl;

    int year_age = 0;
    int year_2020 = 2020;
    year_age = year_2020 - age;
    std::cout << "You were born in " << year_age <<std::endl;

    int  turning_100 = 0;
    int  num_100 = 100;
    turning_100 = num_100 - age;
    std::cout << "Years left until you turn 100! " << turning_100 <<std::endl;


    return 0;
}
