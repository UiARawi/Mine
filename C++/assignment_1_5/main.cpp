#include <iostream>

int main() {

    std::string word1;
    std::string word2;
    std::cout<< " Enter the first word: "<< std::endl;
    std::getline(std::cin, word1);
    std::cout<< " Enter the second word: "<< std::endl;
    std::getline(std::cin, word2);

    if ((word1.compare(word2) == 0) or (word2.compare(word1) == 0))
        std::cout<<"are equal"<<std::endl;
    else
        std::cout<<"are not equal"<<std::endl;
    if ((word1.find(word2) != std::string::npos) or (word2.find(word1) != std::string::npos))
        std::cout<<"is a substring"<<std::endl;
    else
        std::cout<<"is not a substring"<<std::endl;
    return 0;
}
