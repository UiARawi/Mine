#include <iostream>
#include "std_lib_facilities.h"


template<class T1>
T1* DoSomeMath() {
    T1 value1;
    T1 value2;
    std::cin >> value1;
    std::cin >> value2;

    std::cout << "Add: " << setprecision(2) << fixed<< value1 + value2 << std::endl;
    std::cout << "Sub: " << setprecision(2) << fixed<< value1 - value2 << std::endl;
    std::cout << "Mul: " << setprecision(2) << fixed<< value1 * value2 << std::endl;
    std::cout << "Div: " << setprecision(2) << fixed << value1 / value2 << std::endl;

}



int main() {

    DoSomeMath<double>();
        return 0;


}