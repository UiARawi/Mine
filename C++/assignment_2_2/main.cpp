#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <limits>


using namespace std;
typedef map<string, string> Country_Code;
typedef string String;
int main() {

    Country_Code country_code;
    int choice;
    //strings to store input data
    String country_code_user = "Uninit" ;
    String country_name_user;
    //strings to store data read from countries.txt
    String country_code_file;
    String country_name_file;

    fstream MyFile("countries.txt");

//    country_code["0045"] =  "Danmark";
//    country_code["0046"] =  "Sweden";
//    country_code["0047"] = "Norway";
//
//    if (MyFile.is_open()){
//        for (auto& itr : country_code){
//            MyFile << itr.first << endl;
//            MyFile << itr.second << endl;
//        }
//
//    }

    cout<< "Enter 1 or 2:";
    cin>> choice;

    switch (choice) {
        case 1:
            cout << "Enter the country code:";
//            cin >> country_code_user;
//            cin.clear ( );
            cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n') ;
            getline(std::cin, country_code_user);

            if (MyFile.is_open()){
                while ((!MyFile.eof()) and (country_code_user.compare(country_code_file)) != 0){
                    getline(MyFile, country_code_file);
                    getline(MyFile, country_name_file);
                }
                cout << country_name_file;
                MyFile.close();
            }
            break;
        case 2:
            cout << "Enter the country name:";
//            cin >> country_name_user;
//            cin.clear ( );
            cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n') ;
            getline(cin , country_name_user);
            if ((MyFile.is_open()) and  country_name_user.compare(country_name_file) != 0){
                while (country_name_user.compare(country_name_file) != 0){
                    getline(MyFile, country_code_file);
                    getline(MyFile, country_name_file);
                }
                cout << country_code_file;

                MyFile.close();
            }
            break;

        default:
            break;

    }
    return 0;
}
