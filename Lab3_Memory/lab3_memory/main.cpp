/**
 * @file allocator.cpp
 * @author Jack Toole, updated by Sean Massung to add doxygen comments
 * @date Fall 2011
 * @modified in Spring 2025 by Anna LaValle
 */

#include <algorithm>
#include <vector>
#include <iostream>
#include <utility>

#include "fileio.h"
#include "letter.h"
#include "room.h"
#include "allocator.h"

/**
 * Main routine.
 * Creates an Allocator object and allocates the students
 */
int main()
{
	std::cout << std::endl;
	fileio::init();
	Allocator theAllocator("students.txt", "rooms.txt");
	theAllocator.allocate();
	theAllocator.printRooms();
	std::cout << std::endl;
	return 0;
}
