#include <iostream>
#include <limits>
#include <string>

#include "Node.h"


int main() {

    MyList<MyNode<int> > stack_int;
    MyList<MyNode<std::string> > stack_string;
    Display();
    int select = 0;
    std::cin >> select;
    std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n') ;

    while (select != 8){
        switch (select) {
            case 1: {
                std::cout << "Enter an integer:" << std::endl;
                int num;
                std::cin >> num;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                stack_int.push_back(new MyNode<int>(num));
                break;
            }
            case 2:{
                std::cout << "Enter the position: " << std::endl;
                std::size_t pos;
                std::cin >> pos;
                std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n') ;
                std::cout << "Integer in position " <<  pos << ": "  ;
                stack_int.printOnce(pos);

                break;}
            case 3: {
                std::cout << "Enter the position: " << std::endl;
                std::size_t pos_remove;
                std::cin >> pos_remove;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                stack_int.remove(pos_remove);
                break;
            }
            case 4:
            {
                std::cout << "Enter a string:" << std::endl;
                std::string string1;
                getline(std::cin, string1);
                stack_string.push_back(new MyNode<std::string>(string1));
                break;}
            case 5:
            {
                std::cout << "Enter the position: " << std::endl;
                std::size_t pos_string;
                std::cin >> pos_string;
                std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n') ;
                std::cout << "String in position " <<  pos_string << ": "  ;
                stack_string.printOnce(pos_string);
                break;}
            case 6: {
                std::cout << "Enter the position: " << std::endl;
                std::size_t pos_remove_st;
                std::cin >> pos_remove_st;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                stack_string.remove(pos_remove_st);
                break;
            }
            case 7:
            {
                std::size_t int_size = stack_int.size();
                std::cout << "Got " << int_size << " integers: ";
                stack_int.printList();
                std::size_t string_size = stack_string.size();
                std::cout << "Got " << stack_string.size() << " strings: ";
                stack_string.printList();
                break;}
            default:
                break;
        }
        Display();
        std::cin >> select;
        std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n') ;

    }

    return 0;
}





















