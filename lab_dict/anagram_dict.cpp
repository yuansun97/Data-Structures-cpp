/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>
#include <iostream>

using std::string;
using std::vector;
using std::ifstream;


// template <class K, class V>
// void printMap(std::map<K, V> map) {
//     for (auto & x : map) {
//         std::cout << "{" << x.first << " -> [";
//         for (auto & w : x.second) {
//             std::cout << w << ",";
//         }
//         std::cout << "]}" << std::endl;
//     }
//     std::cout << std::endl;
// }




/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
    ifstream infile(filename);
    string word;
    if (infile.is_open()) {
        // std::cout << "file open!" << std::endl;
        while (getline(infile, word)) {
            string key = hash_anagram(word);

            // std::cout << word << "-" << key << std::endl;

            dict[key].push_back(word);
        }
    }
    // printMap(dict);
    infile.close();
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
    for (const auto & word : words) {
        string key = hash_anagram(word);
        dict[key].push_back(word);
    }
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
    string key = hash_anagram(word);
    if (dict.find(key) == dict.end()) return vector<string>();
    return dict.at(key);
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    vector<vector<string>> ret;
    for (const auto & pair : dict) {
        if (pair.second.size() > 1) {
            ret.push_back(pair.second);
        }
    }
    return ret;
}

/**
 * Helper function generates a hash for a given string.
 * This hash is the same for all words in the same group of anagrams,
 * but unique for words that are not anagrams to each other.
 * 
 * @param word The word to generate anagram hash.
 * @return string A string with all characters sorted from given word.
 * */
std::string AnagramDict::hash_anagram(std::string word) const {
    if (word.size() == 0) return word;
    std::transform(word.begin(), word.end(), word.begin(), ::tolower);
    if (word.size() == 1) return word;

    int record[26] = {};
    for (unsigned i = 0; i < word.size(); i++) {
        record[word.at(i) - 'a']++;
    }

    string ret = "";
    for (int i = 0; i < 26; i++) {
        for (int n = 0; n < record[i]; n++) {
            ret += (char) 'a' + i;
        }
    }
    return ret;
}