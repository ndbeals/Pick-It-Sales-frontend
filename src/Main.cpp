// #include <iostream>
#include "Constants.h"
#include "UserInput.cpp"
// #include "HelperFunctions.cpp"

int main(int argc, char *argv[]) {

	printf("Welcome to Pick-It Sales!\n");

	// string readin = UserInput::GetStringInput();
	// int num = UserInput::GetIntegerInput(-1000,100);
	int num = UserInput::GetFloatInput(-1000,1000);

	// printf("\n\ndebug: %s\n",readin.c_str());
	return 0;
}