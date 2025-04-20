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

using std::string;
using std::vector;
using std::ifstream;

string get_sorted_string(const string& word) {
    string sorted = word;
    std::sort(sorted.begin(), sorted.end());
    return sorted;
}


string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, last - first + 1);
}

/** 
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */ 
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
    ifstream words(filename);
    string word;
    
    if (words.is_open()) {
        while (getline(words, word)) {
            word = trim(word);
            if (word.empty()) continue;         
            string sorted = get_sorted_string(word);

            if (std::find(dict[sorted].begin(), dict[sorted].end(), word) == dict[sorted].end()) {
                dict[sorted].push_back(word);
            }
        }
    }
    
}

/** 
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */ 
AnagramDict::AnagramDict(const vector< string >& words)
{
    /* Your code goes here! */
    for (const string& word : words) {
        
        if (word.empty()) continue;
        
        string sorted = get_sorted_string(word);

        if (std::find(dict[sorted].begin(), dict[sorted].end(), word) == dict[sorted].end()) {
            dict[sorted].push_back(word);
        }
    }
}

/**
 * @param word The word to find anagrams of. 
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the 
 * word list.
 */
vector< string > AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
    string sorted = get_sorted_string(word);
    auto it = dict.find(sorted);
    
    if (it != dict.end()) {
        return it->second;
    }
    
    return vector< string >();
}       

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector< vector< string > > AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    vector<vector<string>> result;
    for (const auto& entry : dict) {
      if (entry.second.size() >= 2) {
            result.push_back(entry.second);                
      }
    }
    return result;
}


