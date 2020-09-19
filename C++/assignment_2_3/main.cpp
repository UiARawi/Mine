#include <iostream>
#include <map>
#include <string>

using namespace std;
typedef map<string, int> Output;
typedef string String;

int main() {

    Output output;
    String string;

    cout << "Enter some words:" << endl;

    while (string.compare("stop") != 0){

            getline(cin, string);
            output[string]++;
    }

    output.erase("stop");

    int count_unique = 0;
    int count = 0;
    int t = 0;

    for ( auto& out: output ){
        if (out.second == 1)
        {
            count_unique++;
        }else{

            t++;
        }

        count += out.second;
    }


    cout << "Unique : " << count_unique << endl;
    cout << "Total : " << count << endl;
    cout << "T : " << t+count_unique << endl;

    for (const auto& out: output){
            cout << out.first;
            cout << " : " << out.second << endl;
    }

    return 0;
}
