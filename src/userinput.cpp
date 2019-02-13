#include <iostream>
#include <string>

#include "userinput.h"
#include "constants.h"
#include "helperfunctions.h"

namespace UserInput {

	/**
	 * Read a string input from the command line
	 * @param minLength Minimum length of the input string (default=1)
	 * @param maxLength Maximum length of the input string (default=25)
	 * @return the user input as a string
	 */
	std::string GetStringInput( uint minLength , uint maxLength ) 
	{
		// bool validInput = false;
		std::string input;

		// loop while the input is not valid
		// while ( !validInput ) {
			std::getline( std::cin , input );
			
			
			if (std::cin.eof()) {
				exit(0);
			}

			
			// trim leading and trailing spaces.
			input = trim(input);

			// validate input against min and max length;
			if ( input.length() < minLength ) {
				// too short
				errorPrintf("Input too short\n");
			}
			else if ( input.length() > maxLength ) {
				// too long
				errorPrintf("%s","Input too long\n");
				// ErrorPrintf("%s%s%s" , "Input too long\n","test\n");
			}
			else {
				// validation passed.
				// validInput = true;
			}

			// printf("input is: %s\n",input.c_str());
		// }

		return input;
	}

	/**
	 * GetCommandInput wraps GetStringInput and just prints a text prompt before asking for input
	 * @return the user input as a string
	 * @see GetStringInput
	 */
	std::string GetCommandInput()
	{
		printf(COMMAND_PROMPT_PREFIX);
		return GetStringInput(0,25);
	}

	/**
	 * Read an integer input from the command line, takes a max and min value
	 * @param min Minimum value of the integer (default=0)
	 * @param max Maximum value of the integer (default=10000)
	 */
	int GetIntegerInput( int min , int max )
	{
		// declare used variables.
		bool validInput = false;
		int inputNum;

		// loop while the input is invalid
		while( !validInput ) {
			// Get string input from cin
			std::string input = GetStringInput( 1 , 10 );

			try
			{
				// holds the amount of characters processed by stoi
				size_t charCount;
				// try to convert the string to an integer, using c++11 'stoi'
				inputNum = std::stoi( input , &charCount );

				// check if input stream is PURELY a number
				if ( (input.length() == (uint)charCount ) && (inputNum >= min && inputNum <= max) ) {
					// If it didn't error, set validInput to true:
					validInput = true;
				}
				else {
					// otherwise, error and restart
					throw std::invalid_argument("");
				}
			}
			catch(const std::invalid_argument& e)
			{
				errorPrintf("Invalid input, enter only numbers\n");
				// std::cerr << "A?" << e.what() << '\n';
			}
			catch(const std::exception &e)
			{
				errorPrintf("Out of range error (how on earth did this happen?!)\n");
			}
		}
		return inputNum;
	}

	/**
	 * Read an integer float from the command line, takes a max and min value
	 * @param min Minimum value of the float (default=0)
	 * @param max Maximum value of the float (default=10000)
	 */
	float GetFloatInput( float min , float max )
	{
		// declare used variables.
		bool validInput = false;
		float inputNum;

		// loop while the input is invalid
		while( !validInput ) {
			// Get string input from cin
			std::string input = GetStringInput( 1 , 10 );

			try
			{
				// holds the amount of characters processed by stof
				size_t charCount;
				// try to convert the string to an integer, using c++11 'stof'
				inputNum = std::stof( input , &charCount );

				// check if input stream is PURELY a number
				if ( (input.length() == (uint)charCount ) && (inputNum >= min && inputNum <= max) ) {
					// If it didn't error, set validInput to true:
					validInput = true;
				}
				else {
					// otherwise, error and restart
					throw std::invalid_argument("");
				}
			}
			catch(const std::invalid_argument& e)
			{
				errorPrintf("Invalid input, enter only numbers\n");
				// std::cerr << "A?" << e.what() << '\n';
			}
			catch(const std::exception &e)
			{
				errorPrintf("Out of range error (how on earth did this happen?!)\n");
			}
		}
		return inputNum;
	}
}

