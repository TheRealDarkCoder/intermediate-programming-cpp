/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>

#include "cartalk_puzzle.h"

using std::vector;
using std::string;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of "StringTriples" (a typedef'd std::tuple, see top of 
 * cartalk_puzzle.h). Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector< StringTriple > cartalk_puzzle(PronounceDict d,
                                      const string& word_list_fname)
{
    /* Your code goes here! */
    vector<StringTriple> result;
    std::ifstream word_file(word_list_fname);
    string word;
    
    // Process each word in the word list
    while (getline(word_file, word)) {
        // We're looking for a 5-letter word (at least)
        if (word.length() >= 5) {
            // Remove first letter
            string without_first = word.substr(1);
            
            // Put back first letter and remove second letter
            string without_second = word.substr(0, 1) + word.substr(2);
            
            // Check if both resulting words are homophones of the original word
            if (d.homophones(word, without_first) && d.homophones(word, without_second)) {
                // Add this triple to our results
                result.push_back(std::make_tuple(word, without_first, without_second));
            }
        }
    }
    
    return result;
}
