#include <iostream>

int main() {

    //assignment_1_1_1
    int num_10 = 10;
    int num_20 = 20;
    int num_50 = 50;
    int num_40 = 40;
    int num_100 = 100;
    for (int i = 1; i < (num_10 + 1); i++) {
        std::cout << i << " ";
        if (i == num_10) { std::cout << std::endl; }
    }


    //assignment_1_1_2
    for (int j = 1; j < (num_20 + 1); j++) {
        if ((j % 2) == 0) { std::cout << j << " "; }
        if (j == num_20) { std::cout << std::endl; }
    }

    //assignment_1_1_3
    for (int j = 1; j < (num_20 + 1); j++) {
        if ((j % 2) != 0) { std::cout << j << " "; }
        if (j == num_20) { std::cout << std::endl; }
    }

    //assignment_1_1_4
    int k = 1;
    while (k < (num_50)) {
//        if (k != 1)
            std::cout << k << " ";
        k = k + 3;
    }
    std::cout << std::endl;
    //assignment_1_1_5
    int h = num_40;
    while (h >= 1) {
//        if (h != 40)
            std::cout << h << " ";
        h = h - 4;
    }
    std::cout << std::endl;
    //assignment_1_1_5

    std::cout << 2 << " ";
    for (int a = 2; a <= num_100; a++) {
        for (int b = 2; b <= a; b++) {
            if (a % b == 0)
                break;
            else if (a == b + 1)
                std::cout << a << " ";
        }
    }
    std::cout << std::endl;
    return 0;
}