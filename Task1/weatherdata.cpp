// Include vector library. same data type, can grow size if needed
#include <vector>
// Include string. no need to know how long, can grow if needed. store
#include <string>
// header file for cout
#include <iostream>
// storing warmest day and temperature
#include <tuple>

//main entry point 
//1. Use vector <string> to store names of separate days of the week
int main() {
    std:: vector <std::string> weekdays=
    {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
// double is primitive, doesn`t require std namespace ! 2. Use vector double to store temperature readings    
    std:: vector <double> temperature=
    {8,10,15.5,20,30,6,13};
// declaring the tuple, to compare warmest day
    std:: tuple <std::string,double> warmest = {weekdays[0], temperature[0]};
//use cout to print each day and its temperature with for loop
    for (int i = 0; i<7; i++) {
    std:: cout << weekdays[i] << ": " << temperature[i] << " C ";
//use if-else statement to classify each day as cold, ok, warm 
    if (temperature[i] <10 ) {
    std:: cout << "- The day is cold";
    }
    else if (temperature[i] >20 ){
    std:: cout << "- The day is warm";
    }
    else if (temperature [i] >10 || temperature[i] < 20){

    std:: cout << "- The day is ok";
    }
    std::cout << "\n";
    if (temperature [i] > std::get<double>(warmest)){
        std::get<double>(warmest) = temperature[i];
        std::get<std::string>(warmest) = weekdays[i];
    }
}
std::cout << "Warmest day is " << std::get<std::string>(warmest) << " with temperature " << std::get<double>(warmest) << std::endl;
}
