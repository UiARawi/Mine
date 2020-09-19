#include <iostream>
#include <iomanip>
#include <algorithm>
#include <list>
using namespace std;
typedef list<int> Numbers;

 int main() {
     Numbers numbers;
     int number_entered;
     int avg= 0, n = 0;
     int median;
     cout<< " Enter some numbers, to quit enter 0 : "<<endl;

     //Finding Average
     do
     {
         cin>>number_entered;
         numbers.push_back(number_entered);
         n++;
     }while (number_entered);
     n--;
     numbers.remove(0);

     for(auto it = numbers.cbegin(); it != numbers.cend(); it++){
         avg += *it;
     }
     cout << "Average : " << setprecision(2)<< int (avg/n) << endl;

     //finding Median
     //Sort Ascending
     numbers.sort();
//     for(auto it = numbers.cbegin(); it != numbers.cend(); it++);

// A pointer to the first element of the list
    auto itr = numbers.begin();

     if (numbers.size() % 2 == 0){
         for( int i = 0 ; i < (numbers.size() / 2) ; i ++ ) {
             itr++;
         }

         median = ( (int )*itr + *--itr ) / 2;

     }else{
         for( int i = 0 ; i < numbers.size() / 2 ; i ++ ) {
             itr++;
         }
         median = *itr;
     }

     cout << "Median : " << setprecision(2) << median << endl;




     //sort Descending
     numbers.sort(greater<int>());
     cout <<"Descending : ";
     for(auto it = numbers.cbegin(); it != numbers.cend(); it++)
         cout << *it << " ";
     cout<<endl;
    return 0;
}
