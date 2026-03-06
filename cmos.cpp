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
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    // getting txt file
    string filename = argv[1];
    ifstream file(filename);
    if(!file) {
        cerr << "Error opening file: " << filename << endl;
        return 1;
    }

    string line;
    while (getline(file, line)) {
    // process each line for fingerprinting
        for(size_t i = 0; i < line.length(); i++) {
            if (line[i] == ' ' || line[i] == '\n') {
                line.erase(i, 1);
                i++;
            }
        }
    }

    vector<string> kmers;
    int k = 4; 
    for (size_t i = 0; i <= line.length() - k; i++) {
        kmers.push_back(line.substr(i, k));
    }

    // testing kmer outputss
    for (const auto& kmer : kmers) {
        cout << kmer << endl;
    }

    // compare fingerprints
    /**if() {
       
    } else {
        
    }*/
    // output results to report file
    return 0;
}