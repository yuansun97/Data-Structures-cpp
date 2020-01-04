/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>
#include <iostream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;

    // Read words from file
    ifstream wordsFile(word_list_fname);
    string word;
    if (wordsFile.is_open()) {
        while (getline(wordsFile, word)) {
            if (word.size() == 5) {
                string word_1 = word;
                string word_2 = word;
                word_1.erase(0, 1);
                word_2.erase(1, 1);
                if (d.homophones(word, word_1) && d.homophones(word, word_2)) {
                    // cout << "{" << word << ", " << word_1 << ", " << word_2 << "} " << endl;
                    ret.push_back(std::make_tuple(word, word_1, word_2));
                }
            }
        }
    }
    wordsFile.close();
    return ret;
}
