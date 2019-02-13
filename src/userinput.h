#ifndef USERINPUT_H
#define USERINPUT_H

/**
 * UserInput Namespace contains all the functions to read user input from the command line
 */
namespace UserInput {

	/**
	 * Read a string input from the command line
	 * @param minLength Minimum length of the input string (default=1)
	 * @param maxLength Maximum length of the input string (default=25)
	 * @return the user input as a string
	 */
	std::string GetStringInput( unsigned int minLength = 1 , unsigned int maxLength = 25 );

	/**
	 * GetCommandInput wraps GetStringInput and just prints a text prompt before asking for input
	 * @return the user input as a string
	 * @see GetStringInput
	 */
	std::string GetCommandInput( );

	/**
	 * Read an integer input from the command line, takes a max and min value
	 * @param min Minimum value of the integer (default=0)
	 * @param max Maximum value of the integer (default=10000)
	 */
    int GetIntegerInput( int min = 0, int max = 10000 );

	/**
	 * Read an integer float from the command line, takes a max and min value
	 * @param min Minimum value of the float (default=0)
	 * @param max Maximum value of the float (default=10000)
	 */
	float GetFloatInput( float min = 0.0f , float max = 10000.0f );

}

#endif