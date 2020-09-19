#include <iostream>
#include <string>
int main() {

    bool is_palindrome = true;
    std::string word;
    std::cout<< " Enter a word: "<< std::endl;
    std::cin >> word;
    std::cout<< word.length()<<std::endl;
    for (int j= 0; j < word.length(); j++)
    {
            if (word[j] != word[word.length()-j-1]){
                is_palindrome = false;}
    }
    if (is_palindrome) std::cout<< "is a palindrome"<< std::endl;
    else std::cout<< "is not a palindrome"<< std::endl;

    for (std::string::reverse_iterator rit = word.rbegin(); rit != word.rend(); ++rit)
        std::cout<< *rit;

    //Stackoverflow example
    /*
        std::string s;
        std::cin >> s;
        if( equal(s.begin(), s.begin() + s.size()/2, s.rbegin()) )
        std::cout << "is a palindrome.\n";
        else
        std::cout << "is NOT a palindrome.\n";
    */
    /*
    string input;
    cout << "Please enter a string: ";
    cin >> input;
    if (input == string(input.rbegin(), input.rend())) {
    cout << input << " is a palindrome";
    }
     */

    return 0;
}
