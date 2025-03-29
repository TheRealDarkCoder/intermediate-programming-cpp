/**
 * @file letter.cpp
 * @author Jack Toole, updated by Sean Massung to add doxygen comments
 * @date Fall 2011
 * @modified in Spring 2025 by Anna LaValle
 */

#include <string>
#include "letter.h"

/**
 * Letter constructor. Initializes the letter to '-' with 0 students
 * The letter should be set by the client
 */
Letter::Letter()
	: letter('-'), count_students_for_letter(0)
{ }

/**
 * Adds one additional student to the letter group
 */
void Letter::addStudent()
{
	count_students_for_letter++;
}

/**
 * Comparator for letters (to allow for sorting)
 */
bool Letter::operator<(const Letter & other) const
{
	return count_students_for_letter > other.count_students_for_letter;
}
