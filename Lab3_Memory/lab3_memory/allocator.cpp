/**
 * @file allocator.cpp
 * @author Jack Toole, updated by Sean Massung to add doxygen comments
 * @date Fall 2011
 * @modified in Spring 2025 by Anna LaValle
 */

#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <utility>

#include "letter.h"
#include "room.h"
#include "allocator.h"
#include "fileio.h"

/**
 * Allocator constructor
 */
Allocator::Allocator(const std::string & studentFile, const std::string & roomFile)
{
	createLetterGroups();
	loadStudents(studentFile);
	loadRooms(roomFile);
}


Allocator::~Allocator()
{
  // delete &alphabet;
}


/**
 * Allocates the vector of letters
 */
void Allocator::createLetterGroups()
{
	// Make letters (A - Z lettergroups)
	alphabet.resize(26,  Letter());
	for (int i = 0; i < 26; i++)
		alphabet[i].letter = 'A' + i;
}

/**
 * Reads the students from the students file and places them in their letter
 * groups.
 */
void Allocator::loadStudents(const std::string & file)
{
	// Read in students
	fileio::loadStudents(file);
	studentCount = fileio::getNumStudents();

	for (int i = 0; i < studentCount; i++)
	{
		std::string name = fileio::nextStudent();
		char letter = name[0];
		int index = (int)letter - 'A';
		alphabet[index].addStudent();
	}
}

/**
 * Reads rooms from the rooms file
 */
void Allocator::loadRooms(const std::string & file)
{
	// Read in rooms
	fileio::loadRooms(file);
	rooms.clear();
	totalCapacity = 0;

	while (fileio::areMoreRooms())
	{
		Room newRoom = fileio::nextRoom();
    rooms.push_back(newRoom);  // Store rooms properly instead of overwriting
    totalCapacity += newRoom.getCapacity();
	}

	roomCount = rooms.size();  // Ensure correct count
}

void Allocator::printStudents()
{
	// Output number of each last letter name
  	std::cout << "Student counts (" << studentCount << " total)" << std::endl;
	for (int i = 0; i < 26; i++)
		std::cout << alphabet[i].letter << ": " << alphabet[i].count_students_for_letter << std::endl;
}

/**
 * Main allocation function
 * Allocates student letter groups to rooms
 */
void Allocator::allocate()
{
	// Perform the allocation
	int border = solve();

	// Check for an error
	if (border < 0)
	{
		std::cerr << std::endl << "Cannot allocate all students." << std::endl << std::endl;
		exit(-1);
	}
}

/**
 * Prints the rooms and their fullness
 */
void Allocator::printRooms()
{
	// Output the allocation
	std::cout << "Room Allocation (" << studentCount << "/" << totalCapacity << ")" << std::endl;
	for (int i = 0; i < roomCount; i++)
		rooms[i].print();
}

/**
 * Calculates the allocation
 */
int Allocator::solve()
{
	stable_sort(alphabet.begin(), alphabet.end());
	
	for (int L = 0; L < 26; L++)
	{
		Room& r = largestOpening();
		r.addLetter(alphabet[L]);
	}
	
	return minSpaceRemaining();
}

/**
 * Returns the amount of seats remaining in the room with the fewest
 * spare seats
 */
int Allocator::minSpaceRemaining()
{
	int border = 1000000;
	for (int i = 0; i < roomCount; i++)
		if (rooms[i].spaceRemaining() < border)
			border = rooms[i].spaceRemaining();
	return border;
}

/**
 * Return the room with the largest number of open seasts
 */
Room & Allocator::largestOpening()
{
	int index = 0;
	int max_remaining = 0;
	for (int i = 0; i < roomCount; i++)
	{
		if (rooms[i].spaceRemaining() > max_remaining)
		{
			index = i;
			max_remaining = rooms[i].spaceRemaining();
		}
	}
	return rooms[index];
}
