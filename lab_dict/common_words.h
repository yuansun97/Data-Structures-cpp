/**
 * @file common_words.h
 * Header file of a class to find all the common words across multiple files
 *
 * @author Zach Widder
 * @date Fall 2014
 */

#pragma once

#include <string>
#include <map>
#include <vector>

using std::map;
using std::vector;
using std::string;

/**
 * CommonWords class. Definition of a class to find all the common words across
 * multiple files
 *
 * @author Zach Widder
 * @date October 2014
 */
class CommonWords
{
  public:
    /**
     * Constructs a CommonWords object from a vector of filenames.
     * @param filenames The list of filenames to read.
     */
    CommonWords(const std::vector<std::string>& filenames);

    /**
     * @param n The number of times to word has to appear.
     * @return A vector of strings. The vector contains all words that appear
     * in each file >= n times.
     */
    std::vector<std::string> get_common_words(unsigned int n) const;

  private:
    /**
     * Map a word to a vector of frequencies in corresponding files.
     * "eg" -> [2, 0, 3]
     * means "eg" appears twice in the 1st file, 
     *                    0 time in the 2nd file, 
     *                    3 times in the 3rd file.
     * */
    map<string, vector<unsigned int>> word_to_freqs;

    /* helper functions */

    /**
     * Initializes #file_word_maps.
     * @param filenames The vector of names of the files that will be used
     */
    void init_word_to_freqs(const vector<string>& filenames);

    // /**
    //  * Initializes #common.
    //  */
    // void init_common();

    /**
     * Takes a filename and transforms it to a vector of all words in that file.
     * @param filename The name of the file that will fill the vector
     */
    vector<string> file_to_vector(const string& filename) const;
};
