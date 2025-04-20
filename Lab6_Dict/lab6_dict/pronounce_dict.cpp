/**
 * @file pronounce_dict.cpp
 * Implementation of the PronounceDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "pronounce_dict.h"

#include <iterator>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstring>
#include <cctype>
#include <algorithm>

using std::string;
using std::unordered_map;
using std::vector;
using std::ifstream;
using std::istream;
using std::istream_iterator;
using std::stringstream;

/** 
 * Constructs a PronounceDict from a CMU pronunciation dictionary
 * file. See http://www.speech.cs.cmu.edu/cgi-bin/cmudict .
 * @param pronun_dict_filename Filename of the CMU pronunciation
 * dictionary.
 */
PronounceDict::PronounceDict(const string& pronun_dict_filename)
{
    ifstream pronun_dict_file(pronun_dict_filename);
    string line;
    if(pronun_dict_file.is_open()) {
        while(getline(pronun_dict_file, line)) {
            /* Used to break the line by whitespace. The CMU Dict does this for
             * separating words from their pronunciations. */
            stringstream line_ss(line);
            istream_iterator< string > line_begin(line_ss);
            istream_iterator< string > line_end;
            if(line[0] != '#' && *line_begin != ";;;") {   
                /* Associate the word with the rest of the line
                 * (its pronunciation). */
            	string w = *line_begin;
                dict[w] = vector< string > (++line_begin, line_end);
            }
        }
    }
    /* If it's not open then... well... just don't do anything for the sake
     * of simplicity. */
}

/** 
 * Constructs a PronounceDict from a CMU std::map mapping the word
 * to a vector of strings which represent the pronunciation.
 * @param pronun_dict_filename Filename of the CMU pronunciation
 * dictionary.
 * @param pronun_dict Maps a string word to a vector of strings
 * representing its pronunciation.
 */
PronounceDict::PronounceDict(const unordered_map< string, vector< string > >& 
                             pronun_dict) : dict(pronun_dict)
{
    /* Nothing to see here. */  
}

/** 
 * Uses the dictionary to determine if the two words are homophones.
 * @param word1 First word to be tested.
 * @param word2 Second word to be tested.
 * @return true if the two words are homophones, false otherwise (or
 * one or both words weren't in the dictionary).
 * Note: The word keys in the dictionary are stored in uppercase.
 */
bool PronounceDict::homophones(const string& word1, const string& word2) const
{
    /* Your code goes here! */
    string word1_upper = word1;
    string word2_upper = word2;
    
    std::transform(word1_upper.begin(), word1_upper.end(), word1_upper.begin(), ::toupper);
    std::transform(word2_upper.begin(), word2_upper.end(), word2_upper.begin(), ::toupper);
    
    
    auto word1_it = dict.find(word1_upper);
    auto word2_it = dict.find(word2_upper);
    
    if (word1_it == dict.end() || word2_it == dict.end()) {
        return false;
    }
    
    
    const vector<string>& pronunciation1 = word1_it->second;
    const vector<string>& pronunciation2 = word2_it->second;
    
    
    if (pronunciation1.size() != pronunciation2.size()) {
        return false;
    }
    
    for (size_t i = 0; i < pronunciation1.size(); i++) {
        if (pronunciation1[i] != pronunciation2[i]) {
            return false;
        }
    }
    return true;
}
