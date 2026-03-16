/**
 * @file cmos.cpp
 * @author Kennedy Firth and Megan Penn
 * @brief - cpp file for plagiarism detection program 
 * @date 2026-03-20
 */

// include statements
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

/**
 * @name - hashFunc
 *         function used to hash generated kmers
 * 
 * @param str - string to be hashed
 * @return long long - the hashed string as a number 
 */
long long hashFunc(const string& str);

/**
 * @name - Pair
 *         structure to store two submissions and their similarity score
 */
struct Pair{
    string program1;
    string program2;
    float similarity;
};

int main(int argc, char* argv[]) {
    // getting tokens file
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

        // storing the line 
        lines.push_back(tokenString);
    }

    // creating the kmers
    size_t k = 4; 
    vector<vector<string>> submissions;

    for (size_t i = 0; i < lines.size(); i++){  
        vector<string> kmers;
        string submission = lines[i];

        // edge case
        if (submission.length() < k) {
            continue;
        }

        // actually pulling the kmers from the string
        for (size_t i = 0; i <= submission.length() - k; i++) {
            kmers.push_back(submission.substr(i, k));
        }

        // adding kmers to submission
        submissions.push_back(kmers);
    }

    // hashing the kmers
    vector<vector<long long>> hashes;
    for (size_t i = 0; i < submissions.size(); i++) {
        vector<long long> temp;

        // hashing each kmer
        for (size_t j = 0; j < submissions[i].size(); j++) {
            string kmer = submissions[i][j];
            temp.push_back(hashFunc(kmer));
        }
        // storing the hashed kmers
        hashes.push_back(temp);
    }    

    // creating fingerprints
    size_t window = 3;
    vector<vector<long long>> fingerprints;

    for (size_t i = 0; i < hashes.size(); i++){
        vector<long long>& hash_temp = hashes[i];
        vector<long long> minHashes;

        // edge case
        if(hash_temp.size() < window){
            continue;
        }

        for (size_t j = 0; j <= hash_temp.size() - window; j++){
            long long min = hash_temp[j];

            // finding the minimum value for the window
            for (size_t k = 1; k < window; k++) {
                if (hash_temp[j + k] < min) {
                    min = hash_temp[j + k];
                }
            }
            minHashes.push_back(min);
        }
        // adding to final fingerprint vector
        fingerprints.push_back(minHashes);
    }

    // compare fingerprints
    vector<vector<float>> final_results;
    for (size_t i = 0; i < fingerprints.size(); i++) {
        // stores the results for one submission
        vector<float> res;

        for (size_t j = 0; j < fingerprints.size(); j++) {
            // comparing to itself
            if (i == j) {
                res.push_back(1.0);
                continue;
            }

            // getting min to avoid weird results
            size_t minSize = min(fingerprints[i].size(), fingerprints[j].size());

            int match = 0;
            for (size_t k = 0; k < minSize; k++) {
                // comparing fingerprints and incrementing
                if (fingerprints[i][k] == fingerprints[j][k]) {
                    match++;
                }
            }

            // calculating similarity
            float similarity = (float) match / minSize;
            // adding to submission vector
            res.push_back(similarity);
        }

        // adding single submission results to final vector of all submissions
        final_results.push_back(res);
    }

    // vector for sorting results
    vector<Pair> rankedResults;

    for (size_t i = 0; i < final_results.size(); i++) {
        for (size_t j = i + 1; j < final_results[i].size(); j++) {
            // building the result pairs based on index
            Pair temp;
            temp.program1 = programs[i];
            temp.program2 = programs[j];
            temp.similarity = final_results[i][j];
            rankedResults.push_back(temp);
        }
    }

    // sorting the final results
    sort(rankedResults.begin(), rankedResults.end(), [](const Pair& a, const Pair& b) {
            return a.similarity > b.similarity;
        });

    // outputting the results 
    for (size_t i = 0; i < rankedResults.size(); i++) {
        cout << rankedResults[i].program1 << " vs "
            << rankedResults[i].program2 << " : "
            << rankedResults[i].similarity * 100 << "%" << endl;
    }

    return 0;
}

long long hashFunc(const string& str) {
    long long h = 0;
    for (char c : str) {
        // hash function
        h = h * 23 + (c - '0');
    }
    return h;
}