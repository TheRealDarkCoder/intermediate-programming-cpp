/**
 * @file fileio.cpp
 * @author Jack Toole, updated by Sean Massung to add doxygen comments
 * @date Fall 2011
 * @modified in Spring 2025 by Anna LaValle
 */
#include "fileio.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

/**
 * Utility functions for reading students/rooms from files.
 * @note THERE ARE NO BUGS in fileio
 */
namespace fileio {
    /**
     * Holds variables that can only be accessed within the current file. 
     * This is similar to private variables in a class.
     */
    namespace {
        /** A vector of students names that were read from the file */
        std::vector<std::string> student_names;
      
        /** A vector of Rooms names that were read from the file */
        std::vector<std::string> room_names;
      
        /** Represents the index of the student to read next */
        size_t next_student_index = 0;
      
        /** Represents the index of the Room to read next */
        size_t next_room_index = 0;
    }

    void init() {
        student_names.clear();
        room_names.clear();
        next_student_index = 0;
        next_room_index = 0;
    }

    void loadStudents(const std::string &file) {
        student_names.clear();
        next_student_index = 0;
        readFile(file, student_names);
        std::stable_sort(student_names.begin(), student_names.end());
    }

    void loadRooms(const std::string &file) {
        room_names.clear();
        next_room_index = 0;
        readFile(file, room_names);
    }

    int getNumStudents() {
        return student_names.size();
    }

    int getNumRooms() {
        return room_names.size();
    }

    bool areMoreStudents() {
        return next_student_index < student_names.size();
    }

    bool areMoreRooms() {
        return next_room_index < room_names.size();
    }

    std::string & nextStudent() {
        return student_names[next_student_index++];
    }

    Room nextRoom() {
        return readRoom(room_names[next_room_index++]);
    }

    Room readRoom(const std::string &line) {
        std::istringstream iss(line);
        std::string name;
        std::string capacity_str;
        std::getline(iss, name, ',');
        std::getline(iss, capacity_str);
        int capacity = std::stoi(capacity_str) / 2;
        return Room(name, capacity);
    }

    void readFile(const std::string &file, std::vector<std::string> &lines) {
        std::ifstream infile(file);
        if (!infile.is_open()) {
            std::cerr << "Unable to open file: " << file << std::endl;
            return;
        }
        std::string line;
        while (std::getline(infile, line)) {
            if (!line.empty() && line.front() != ';') { // Skip empty lines and comments
                lines.push_back(line);
            }
        }
    }
}

