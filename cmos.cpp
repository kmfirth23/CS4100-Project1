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
#include <sstream>
#include <algorithm>

using namespace std;

long long hashFunc(const string& str);

struct Pair{
    string program1;
    string program2;
    float similarity;
};

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
    vector<string> programs; 

    while (getline(file, line)) {

        stringstream ss(line);
        string name;

        // getting program name and pushing to vector
        ss >> name;
        programs.push_back(name);

        string token;
        string tokenString = "";

        // adding rest of line to the token string
        while (ss >> token) {
            tokenString += token;
        }

        lines.push_back(tokenString);
    }

    // creating the kmers
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

    // hashing the kmers
    vector<vector<long long>> hashes;
    for (size_t i = 0; i < submissions.size(); i++) {
        vector<long long> temp;

        for (size_t j = 0; j < submissions[i].size(); j++) {
            string kmer = submissions[i][j];
            temp.push_back(hashFunc(kmer));
        }
        hashes.push_back(temp);
    }    

    // creating fingerprints
    size_t window = 3;
    vector<vector<long long>> fingerprints;

    for (size_t i = 0; i < hashes.size(); i++){
        vector<long long>& hash_temp = hashes[i];
        vector<long long> minHashes;

        if(hash_temp.size() < window){
            continue;
        }

        for (size_t j = 0; j <= hash_temp.size() - window; j++){
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
    vector<vector<float>> final_results;
    for (size_t i = 0; i < fingerprints.size(); i++) {
        vector<float> res;

        for (size_t j = 0; j < fingerprints.size(); j++) {
            if (i == j) {
                res.push_back(1.0);
                continue;
            }

            size_t minSize = min(fingerprints[i].size(), fingerprints[j].size());
            if (minSize == 0) {
                res.push_back(0.0);
                continue;
            }

            int match = 0;
            for (size_t k = 0; k < minSize; k++) {
                if (fingerprints[i][k] == fingerprints[j][k]) {
                    match++;
                }
            }

            float similarity = (float) match / minSize;
            res.push_back(similarity);
        }

        final_results.push_back(res);
    }

    vector<Pair> rankedResults;

    for (size_t i = 0; i < final_results.size(); i++) {
        for (size_t j = i + 1; j < final_results[i].size(); j++) {
            Pair temp;
            temp.program1 = programs[i];
            temp.program2 = programs[j];
            temp.similarity = final_results[i][j];
            rankedResults.push_back(temp);
        }
    }

    sort(rankedResults.begin(), rankedResults.end(), [](const Pair& a, const Pair& b) {
            return a.similarity > b.similarity;
        });

    ofstream report("report.txt");
    for (size_t i = 0; i < rankedResults.size(); i++) {
        report << rankedResults[i].program1 << " vs "
            << rankedResults[i].program2 << " : "
            << rankedResults[i].similarity << endl;
    }

    report.close();
    return 0;
}

long long hashFunc(const string& str) {
    long long h = 0;
    for (char c : str) {
        h = h * 23 + (c - '0');
    }
    return h;
}