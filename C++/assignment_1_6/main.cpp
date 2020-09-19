#include <iostream>

int main() {
    std::string string1;
    std::cout<< " Enter the first word: "<< std::endl;
    std::getline(std::cin, string1);

    int i = 0, Alphabet[26] = {0}, j;
    while (string1[i] != '\0'){
        if (string1[i] >= 'a' && string1[i] <= 'z'){
            j = string1[i] - 'a';
            ++Alphabet[j];
        }
        ++i;
    }
    for (int k = 0; k < 26; k++) {
        std::cout<<"'"<<char (k + 'a')<< "' : "<< Alphabet[k]<<std::endl;

    }
    return 0;
}
