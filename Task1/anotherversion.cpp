// create another version of weatherdata using map
// Include map in the library

#include <map>
#include <iostream>
#include <string>

using namespace std;

// use map <string; double>
int main() {
    map <string, double> weatherdata = {
        {"Monday", 8},
        {"Tuesday", 10},
        {"Wednesday", 15.5},
        {"Thursday", 20},
        {"Friday", 30},
        {"Saturday", 6},
        {"Sunday", 13}
    };

// add char variable to indicate weather condition ("S") for sunny, ("R") for rainny ("P") for perfect

    char S = 'S'; // S represents sunny';
    char R = 'R'; // R represents rainy;
    char P = 'P'; // P represents perfect;
    map <string, char> weathercondition = {
        {"Monday", R},
        {"Tuesday", R},
        {"Wednesday", R},
        {"Thursday", P},
        {"Friday", S},
        {"Saturday", R},
        {"Sunday", R}
    };

    //add loop and cout to show user this part 

    for (map<string, char>::iterator it = weathercondition.begin(); it != weathercondition.end(); it++)
     {
        cout << it->first << " is " << it->second << "\n"; //stream operator "<<";

    }
    // calculate average temperature for the week
    double sum = 0 ;
    map<string, double>::iterator it;
    for (it= weatherdata.begin(); it != weatherdata.end(); it++)
     {
        sum += it->second;
    }
    // get average
    cout << "The average temperature of the week is " << sum/weatherdata.size(); //function call operator ()


}