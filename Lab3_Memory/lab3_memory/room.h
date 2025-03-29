/**
 * @file room.h
 * @author Jack Toole, updated by Sean Massung to add doxygen comments
 * @date Fall 2011
 * @author Anna LaValle
 * @modified Spring 2025
 */
#ifndef ROOM_H
#define ROOM_H

#include "letter.h"

/**
 * Represents a testing room, which has a group of letters allocated to it
 * (where letters are first letters of last names).
 */
class Room
{
public:

        /**
         * Room Default Constructor.
         * Creates a blank (uninitialized) room
         */
        Room();

        /**
         * Main Room constructor.
         * Creates an empty room with the given name and capacity
         * @param init_name The name to create this Room with
         * @param init_capacity The size of this Room
         */
        Room(const std::string & init_name, int init_capacity);

        /**
         * Room copy constructor.
         * @param other The Room to copy into this room.
         */
        Room(const Room & other);

        /**
         * Room assignment operator.
         * @param other The Room to make a copy of
         * @return A reference to the copied Room
         */
        Room & operator=(const Room & other);

        /**
         * Room destructor.
         */
        ~Room();

        /**
         * Allocates a letter group to this room.
         * @param L The letter group to add
         */
        void addLetter(const Letter & L);

        /**
         * @return the number of empty seats remaining in the room after
         *  current allocations.
         */
        int spaceRemaining() const;

        /**
         * Outputs the room to cout.
         */
        void print() const;

       /**
        * Outputs the capacity of the room
        */
        int getCapacity() const;


private:

        /** The room name */
        std::string name;

        /** The capacity of the room */
        int capacity;

        /** The number of students currently allocated to the Room */
        int total_students_in_Room = 0; 

        /** The number of valid Letters in the Letters array */
        int count_letters_allocated_to_Room = 0; 

        /** An array of Letters currently allocated */
        /** Should be replaced with a vector instead */  
        Letter * letters;
  
        /**
         * Destructor/assignment operator clear helper function.
         */
        void clear();

        /**
         * Cctor/assignment operator copy helper function.
         */
        void copy(const Room & other);
};

#endif
