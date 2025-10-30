#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
/*
Design and implement a C++ program that simulates a weather station collecting temperature data, storing it dynamically(memory), and logging it to a file.
The program should use classes, pointers, memory management, file I/O, and error handling.

Use methods
addReading(float value) to add a new temperature reading.
printReadings() to print all readings.
saveToFile(string filename) to save readings to a file.

Use try, catch, and throw for error handling.
Catch file I/O errors.
Prevent division by zero in average calculation and use a template for the calculation.

Use STL algorithms to sort the readings and count how many readings are above a threshold (e.g., 25°C).

Use new[] and delete[] for dynamic memory.

Implement a feature that reads back the saved file and reconstructs the readings into a new WeatherStation object.

The result should look like this:

Location: Lahti
Readings: 22.5 24.0 26.3 21.8 25.7
Average: 24.06
Readings above 25°C: 2
Saved to file: lahti_readings.txt

Return files into GitHub and answer with the link to your repository.


*/

// STL algrorims: https://www.geeksforgeeks.org/cpp/c-magicians-stl-algorithms/

// function to use for count_if
bool isOverThreshold(float value) {
    float threshold = 25.0;
    return value > threshold;
}

template<typename X>
X average(X* values, int numberOfElements) {
    if (numberOfElements > 0) {
        X sum = 0;
        for (int index = 0; index < numberOfElements; index++)
        {
            sum += values[index];
        } 
        return sum / numberOfElements;
    }
    return 0;
}


class WeatherStation {
    public:
    WeatherStation(std::string city) {
        numOfValues = 0;
        currentMaxNofValues = 0;
        values = nullptr;
        location = city;
        //std::cout << "Constructing WeatherStation\n";
    };

    ~WeatherStation() {
        delete[] values;
        //std::cout << "Destructing WeatherStation\n";
    }

    void addReading(float value){
        //std::cout << "Adding " << value << " to WeatherStation data\n";
        
        if (numOfValues == 0) {
            currentMaxNofValues = numOfValues + 10;
            values = new float[currentMaxNofValues];
            values[0] = value;
            numOfValues++;
            return;
        }
        else {
            // do we need to allocate more space?
            if (currentMaxNofValues == numOfValues) 
            {
                // allocate a temporary array
                float* temp = new float[currentMaxNofValues];
                // and copy current values to it
                for (int i=0; i < currentMaxNofValues; i++) {
                    temp[i] = values[i];
                }
                // delete the old one
                delete[] values;
                // allocate a new bigger one
                currentMaxNofValues += 10;
                values = new float[currentMaxNofValues];
                // copy from temp
                for (int i=0; i < numOfValues; i++) {
                    values [i] = temp [i];
                }
                delete [] temp;
            }
        }
        // add new value in
        values [numOfValues] = value;
        numOfValues++; //book keeping
    };

    void printReadings() {
        std::vector<float> readings;
        
        std::cout << "Location: " << location << "\n";
        std::cout << "Readings: ";
        for (int i=0; i < numOfValues; i++)
        {
            std::cout << values[i] << " ";
            readings.push_back(values[i]);
        }
        std::cout << "\nAverage: " << average<float>(values, numOfValues) << "\n";
        // this function counts how many elements in the vector match the requirement
        // https://www.geeksforgeeks.org/cpp/count_if-in-c/
        std::sort(readings.begin(), readings.end()); // sort in ascending order
        int readingsAboveThreshold = std::count_if(readings.begin(), readings.end(), isOverThreshold);
        std::cout << "Readings above 25C: " << readingsAboveThreshold << "\n";
        try {
            std::string filename = "lahti_readings.txt";
            saveToFile(filename);
            std::cout << "Saved to file: " << filename << "\n";
        } catch(const std::runtime_error& e) {
            // https://en.cppreference.com/w/cpp/language/throw.html
            std::cout << "Sorry, we failed to save the file :( " << e.what();
        }
        
    };
    void saveToFile(const std::string& fname) {
        // https://www.w3schools.com/cpp/cpp_files.asp
        // https://medium.com/@ryan_forrester_/c-file-handling-with-fstream-a-complete-guide-a4ebcc294bd0
        std::ofstream f(fname);
        if (f.bad()) {
            f.close();
            // https://en.cppreference.com/w/cpp/error/runtime_error.html
            throw std::runtime_error("Bad file");
        }
        f << location << "\n";
        for (int i=0; i < numOfValues; i++)
        {
            f << values[i] << " ";
        }
    };
    
    private:
    int currentMaxNofValues;
    int numOfValues;
    float* values; // the famous pointer
    std::string location;
};

WeatherStation readReadings(const std::string& filename) {
    std::ifstream f(filename);
    if (!f.good()) {
        // f is not good if it does not exist or when it cant be read
        throw std::runtime_error("Could not open file");
    }
    std::string location;
    std::string readings;
    std::getline(f, location);
    std::getline(f, readings);
    // separate the readings to different variables
    // https://www.geeksforgeeks.org/cpp/how-to-split-string-by-delimiter-in-cpp/
    std::stringstream ss(readings);
    std::string temporary;
    char delim = ' ';
    WeatherStation station(location);
    while (std::getline(ss, temporary, delim)) {
        // https://www.programiz.com/cpp-programming/string-float-conversion
        float value = std::stof(temporary);
        station.addReading(value);
    }
    
    return station;
}

int main() {
    //WeatherStation station("Lahti");
    //station.addReading(22.5);
    //station.addReading(24);
    //station.addReading(26.3);
    //station.addReading(21.8);
    //station.addReading(25.7);
    //station.printReadings();
    try
    {
        WeatherStation station = readReadings("lahti_readings.txt");
        station.printReadings();
    } catch(const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
}