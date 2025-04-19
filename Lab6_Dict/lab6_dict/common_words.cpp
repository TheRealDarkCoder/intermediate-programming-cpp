/**
 * @file common_words.cpp
 * Implementation of the CommonWords class.
 *
 * @author Zach Widder
 * @date Fall 2014
 */

#include "common_words.h"

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

using std::string;
using std::vector;
using std::ifstream;
using std::cout;
using std::endl;
using std::feof;

string remove_punct(const string& str) 
{
    string ret;
    std::remove_copy_if(str.begin(), str.end(), 
                        std::back_inserter(ret),
                        std::ptr_fun< int, int >(&std::ispunct));
    return ret;
}

/**
 * Constructs a CommonWords object from a vector of filenames. 
 * file_word_maps is a vector of maps, where each element of the vector represents a different file,
 * and the map hashes a word in the file to the number of time that word has been seen.
 * common is a map of words in all files that hashes to how many files it appeared in.
 * @param filenames The vector of strings where the strings are the filenames to read in.
 */
CommonWords::CommonWords(const vector<string>& filenames)
{
    // initialize all member variables
    init_file_word_maps(filenames);
    init_common();
}

/**
 * Initializes common, mapping a word to the number of documents it shows up in.
 */
void CommonWords::init_common() 
{
    /* Your code goes here! */
    for (auto& file_map : file_word_maps) {
      for (auto& word_pair : file_map) {
            string word = word_pair.first;
            if (common.find(word) == common.end()) {
                common[word] = 1; 
            } else {
                common[word]++; 
            }
        }
    }
}

/**
 * Initializes file_word_maps, having each index hold a map going from the word 
 * seen in that file to the number of times the word has been seen
 * @param filenames The vector of names of the files that will be used
 */
void CommonWords::init_file_word_maps(const vector<string>& filenames) 
{
    // vector is equal to number of files given
    file_word_maps.resize(filenames.size());

    // go through all files
    for(size_t i = 0; i < filenames.size(); i++) {
        // get the corresponding vector of words that represents the current file
        vector<string> words = file_to_vector(filenames[i]);
        /* Your code goes here! */
        for (const string& word : words) {
            string lower_word = word;
            transform(lower_word.begin(), lower_word.end(), lower_word.begin(), ::tolower);
            
            
            if (lower_word.empty()) {
                continue;
            }
            
            
            if (file_word_maps[i].find(lower_word) == file_word_maps[i].end()) {
                file_word_maps[i][lower_word] = 1; 
            } else {
                file_word_maps[i][lower_word]++; 
            }
        }
    }
}

/**
 * @param n The number of times to word has to appear.
 * @return A vector of strings. Vector contains all words that appear in all
 * files >= n times. I.e. the word must appear in all files more than 
 * n times.
 */
vector< string > CommonWords::get_common_words(unsigned int n) const
{
    /* Your code goes here! */
    vector<string> out;

    size_t num_files = file_word_maps.size();
    
    
    for (const auto& word_pair : common) {
        string word = word_pair.first;
        unsigned int file_count = word_pair.second;
        
        
        if (file_count == num_files) {
            bool appears_n_times = true;
            for (const auto& file_map : file_word_maps) {
                
                auto it = file_map.find(word);
                
                if (it == file_map.end() || it->second < n) {
                    appears_n_times = false;
                    break;
                }
            }
            
            
            if (appears_n_times) {
                out.push_back(word);
            }
        }
    }

    return out;
}

/**
 * Takes a filename and transforms it to a vector of all words in that file.
 * @param filename The name of the file that will fill the vector
 */
vector< string > CommonWords::file_to_vector(const string& filename) const {
    ifstream words(filename);
    vector<string> out;

    if(words.is_open()) {
        std::istream_iterator<std::string> word_iter(words);
        while(!words.eof()) {
            out.push_back(remove_punct(*word_iter));
            ++word_iter;
        }
    }
    return out;
}
