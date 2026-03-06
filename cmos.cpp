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

long long hashFunc(const string& str);

int main(int argc, char* argv[]) {
    // getting txt file
    string filename = argv[1];
    ifstream file(filename);
    if(!file) {
        cerr << "Error opening file: " << filename << endl;
        return 1;
    }

    string line;
    vector<string> lines;
    while (getline(file, line)) {
    // process each line for fingerprinting
        string token = "";

        for(size_t i = 0; i < line.length(); i++) {
            if (line[i] != ' ') {
                token += line[i];
            }
        }

        lines.push_back(token);
    }

    size_t k = 4; 
    vector<vector<string>> submissions;

    for (size_t i = 0; i < lines.size(); i++){  
        vector<string> kmers;
        string submission = lines[i];

        if (submission.length() < k) {
            continue;
        }

        for (size_t i = 0; i <= submission.length() - k; i++) {
            kmers.push_back(submission.substr(i, k));
        }

        submissions.push_back(kmers);
    }

    // hasing the kmers
    vector<vector<long long>> hashes;
    for (size_t i = 0; i < submissions.size(); i++) {
        vector<long long> temp;

        for (size_t j = 0; j < submissions[i].size(); j++) {
            string kmer = submissions[i][j];
            temp.push_back(hashFunc(kmer));
        }
        hashes.push_back(temp);
    }    

    size_t window = 3;
    vector<vector<long long>> fingerprints;

    for (size_t i = 0; i <= hashes.size(); i++){
        vector<long long>& hash_temp = hashes[i];
        vector<long long> minHashes;

        if(hash_temp.size() < window){
            continue;
        }

        for (size_t j = 0; j < hash_temp.size() - window; j++){
            long long min = hash_temp[j];

            for (size_t k = 1; k < window; k++) {
                if (hash_temp[j + k] < min) {
                    min = hash_temp[j + k];
                }
            }
            minHashes.push_back(min);
        }
        fingerprints.push_back(minHashes);
    }
    // compare fingerprints
    /**if() {
       
    } else {
        
    }*/
    // output results to report file
    return 0;
}

long long hashFunc(const string& str) {
    long long h = 0;
    for (char c : str) {
        h = h * 23 + (c - '0');
    }
    return h;
}