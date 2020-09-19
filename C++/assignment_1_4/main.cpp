#include <iostream>
#include <string>
#include <locale>

int main() {

    //assignment_1_4_1
    std::locale loc1;
    std::locale loc2;
    std::string word;
    std::cout<< " Enter a word: "<< std::endl;
    std::getline(std::cin, word);

    for (std::string::size_type i = 0; i< word.length(); ++i)
    std::cout << std::toupper(word[i], loc1);

    std::cout<< std::endl;

    for (std::string::size_type j = 0; j< word.length(); ++j)
    std::cout << std::tolower(word[j], loc1);

    std::cout<< std::endl;

    //assignment_1_4_2
    std::string word_split;
    word_split = word;
    size_t pos = ((word_split.length())/2);

    word_split.insert(pos, " - " );

    std::cout<< word_split << std::endl;


    //assignment_1_4_3
    int integer = 0;

    try{
        integer = std::stoi(word);
        std::cout<< integer*integer << std::endl;
    } catch (std::invalid_argument) {
    }

    double dou = 0;
    try {
        dou = std::stod(word);
        std::cout<< dou/(2.0) << std::endl;
    } catch (std::invalid_argument) {

    }

    return 0;
}
