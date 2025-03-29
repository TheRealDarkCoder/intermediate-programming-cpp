/**
 * @file room.cpp
 * @author Jack Toole, updated by Sean Massung to add doxygen comments
 * @date Fall 2011
 * @modified in Spring 2025 by Anna LaValle
 */

#include <vector>
#include <iostream>
#include <string>
#include "room.h"

/**
 * Room Default Constructor
 * Creates a blank (uninitialized) room
 */
Room::Room()
    : name("-"), capacity(0), total_students_in_Room(0),
      count_letters_allocated_to_Room(0), letters(new Letter[26]){
}

/**
 * Main Room constructor
 * Creates an empty room with the given name and capacity
 */
Room::Room(const std::string & init_name, int init_capacity)
	: name(init_name), capacity(init_capacity), total_students_in_Room(0),
      count_letters_allocated_to_Room(0), letters(new Letter[26]){
}

/**
 * Room copy constructor
 */
Room::Room(const Room & other): name(other.name), capacity(other.capacity), letters(new Letter[26])
{
	copy(other);
}

/**
 * Room assignment operator
 */
Room & Room::operator=(const Room & other)
{
	if (this != &other)
	{
		clear();
		copy(other);
	}
	return *this;
}

/**
 * Room destructor
 */
Room::~Room()
{
	clear();
}

/**
 * Allocates a letter group to this room
 */
void Room::addLetter(const Letter & L)
{
  letters[count_letters_allocated_to_Room++] = L;
  total_students_in_Room += L.count_students_for_letter;
}

/**
 * Returns the number of empty seats remaining in the room after current
 * allocations
 */
int Room::spaceRemaining() const
{
	return capacity - total_students_in_Room;
}

/**
 * Outputs the room to cout
 */
void Room::print() const
{
	std::cout << name << " (" << total_students_in_Room  << "/" << capacity << "):";
	for (int L = 0; L < count_letters_allocated_to_Room; L++)
		std::cout << " " << letters[L].letter;
	std::cout << std::endl;
}

/**
 * Outputs the capacity of the room
 */
int Room::getCapacity() const
{
  return capacity;
}  


/**
 * Destructor/assignment operator clear helper function
 */
void Room::clear()
{
    delete [] letters;
    letters = nullptr;
    count_letters_allocated_to_Room = 0;
    total_students_in_Room = 0;
}

/**
 * Cctor/assignment operator copy helper function
 */
void Room::copy(const Room & other)
{
	total_students_in_Room = other.total_students_in_Room;
	count_letters_allocated_to_Room = other.count_letters_allocated_to_Room;
	// letters = other.letters;
	for (int i = 0; i < count_letters_allocated_to_Room; i++) {
	  letters[i] = other.letters[i];
	}
	
}

