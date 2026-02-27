/**
 * @file cmos.cpp
 * @author Kennedy Firth and Megan Penn
 * @brief - cpp file for plagiarism detection program 
 * @date 2026-02-26
 */

// include statements
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    // getting txt file
    string filename = argv[1];
    ifstream file(filename);
    if(!file) {
        cerr << "Error opening file: " << filename << endl;
        return 1;
    }


    string token, line;
    while (getline(file, line)) {
    // process each line for fingerprinting
        for(int i = 0; i < line.length(); i++) {
            if (line[i] == ' ' || line[i] == '\n') {
                line.erase(i, 1);
                i++;
            }
        }
        

    }
    
    // compare fingerprints

    // output results to report file

    return 0;
}