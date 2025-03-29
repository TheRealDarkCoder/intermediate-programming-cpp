/**
 * @file letter.h
 * @author Jack Toole, updated by Sean Massung to add doxygen comments
 * @date Fall 2011
 * @modified in Spring 2025 by Anna LaValle
 */

#ifndef LETTER_H
#define LETTER_H


/**
 * Represents a group of students with the same first letter of their last
 * name.
 */
class Letter
{
	public:

        /** The character this Letter represents */
        char letter;

        /** How many students have been allocated for this letter. */
        int count_students_for_letter;

        /**
         * Letter constructor. Initializes the letter to '-' with 0 students
         * The letter should be set by the client.
         */
        Letter();

        /**
         * Adds one additional student to the letter group.
         * @param name
         */
        void addStudent();

        /**
         * Comparator for letters (to allow for sorting).
         * @param other A Letter to compare against
         * @return Whether the parameter is less than this Letter.
         */
        bool operator<(const Letter & other) const;
};

#endif
