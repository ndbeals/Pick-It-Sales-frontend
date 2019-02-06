// #include <iostream>
#include <string>

#include "constants.h"

#include "helperfunctions.h"
#include "userinput.h"
#include "command.h"
#include "commands/login.h"
// #include "con"
// #include "helperfunctions.cpp"
// #include "userinput.cpp"
// #include "Commands.cpp"



int main(int argc, char *argv[]) {

	printf("Welcome to Pick-It Sales!\n");

	// string readin = UserInput::GetStringInput();
	// int num = UserInput::GetIntegerInput(-1000,100);
	// float num = UserInput::GetFloatInput(-1000,1000);

	// printf("input float: %f\n",num);
	// test inst(4);

	bool run = true;
	
	while( run ){
		// input = cin
		printf("Enter a command: ");
		std::string input = UserInput::GetStringInput();

		if (input == "exit" ) {
			run = false;
			// exit(0);
			break;
		}

		Command *currentCommand = Command::GetCommand( input );

		currentCommand->Process();

		delete currentCommand;

		// for(int i = 0; i < 1000; i++)
		// {
		// Command *currentCommand = Command::GetCommand( input );
		// printf("main : %p\n",(void *)currentCommand);
		// printf("val: %d\n",currentCommand->val);
		// currentCommand->val = 6;
		// printf("val: %d\n",currentCommand->val);

		// Command test = *currentCommand;
		// printf("main : %p\n",(void *)&test);
		// printf("main : %p\n",(void *)&*&test);
		// printf("val: %d\n",test.val);
		// test.val = 1621;
		// printf("val: %d\n",test.val);

		// printf("val: %d\n",currentCommand->val);
		// 	/* code */
		// 	// delete test;
		// 	delete currentCommand;
		// }
		

	}

		// command = factory ( input )

		// command->getuserinput();

		// if (command->wasvalid()) {
			// command->gettransaction() // write transaction to session
		// }
		// else {
			// do command again
		// }
	// }
	

	// printf("\n\ndebug: %s\n",readin.c_str());
	return 0;
}