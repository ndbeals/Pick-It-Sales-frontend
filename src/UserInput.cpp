#include <iostream>
#include <string>
#include "HelperFunctions.cpp"

using namespace std;

namespace UserInput {
	string trim(const string& str)
	{
		size_t first = str.find_first_not_of(' ');
		if (string::npos == first)
		{
			return str;
		}
		size_t last = str.find_last_not_of(' ');
		return str.substr(first, (last - first + 1));
	}

	string GetStringInput( int minLength = 1 , int maxLength = 15 ) 
	{
		bool validInput = false;
		string input;

		// loop while the input is not valid
		while ( !validInput ) {
			getline( cin , input );
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
				validInput = true;
			}

			// printf("input is: %s\n",input.c_str());
		}

		return input;
	}

	int GetIntegerInput( int min = 0, int max = 10000 )
	{
		// declare used variables.
		bool validInput = false;
		int inputNum;

		// loop while the input is invalid
		while( !validInput ) {
			// Get string input from cin
			string input = GetStringInput( 1 , 10 );

			try
			{
				// printf(" char[0] : %c\n",input.find_first_not_of(' '));
				// holds the amount of characters processed by stoi
				size_t charCount;
				// try to convert the string to an integer, using c++11 'stoi'
				inputNum = std::stoi( input , &charCount );

				// check if input stream is PURELY a number
				if ( (input.length() == (int)charCount ) && (inputNum >= min && inputNum <= max) ) {
					// If it didn't error, set validInput to true:
					validInput = true;
				}
				else {
					// otherwise, error and restart
					throw std::invalid_argument("");
				}

				// printf("read in: %s , ret: %d , char pos: %d" , input.c_str(), inputNum, (int)charCount);
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

	float GetFloatInput( float min = 0.0f , float max = 10000.0f ) {
		// declare used variables.
		bool validInput = false;
		float inputNum;

		// loop while the input is invalid
		while( !validInput ) {
			// Get string input from cin
			string input = GetStringInput( 1 , 10 );

			try
			{
				// printf(" char[0] : %c\n",input.find_first_not_of(' '));
				// holds the amount of characters processed by stof
				size_t charCount;
				// try to convert the string to an integer, using c++11 'stof'
				inputNum = std::stof( input , &charCount );

				// check if input stream is PURELY a number
				if ( (input.length() == (int)charCount ) && (inputNum >= min && inputNum <= max) ) {
					// If it didn't error, set validInput to true:
					validInput = true;
				}
				else {
					// otherwise, error and restart
					throw std::invalid_argument("");
				}

				// printf("read in: %s , ret: %f , char pos: %d" , input.c_str(), inputNum, (int)charCount);
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