#include <iostream>
#include <string>

#include "constants.h"

#include "helperfunctions.h"
#include "userinput.h"
#include "command.h"
#include "commands/login.h"
#include "commands/logout.h"
#include "session.h"
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

	// bool isLoggedIn = false;

	bool run = true;

	// std::string input;
	// while( !std::cin.eof() ){
	// 	auto test = std::getline( std::cin , input );
	// 	/* code */
	// 	printf("echo: %s\n",input.c_str());
	// }
	

	///*
	Session currentSession;
	
	while( true ){
		currentSession = Session();
		currentSession.num=1;

		// printf("cs num: %d\n",currentSession.num);

		// process user input / wait until they have logged in
		currentSession.WaitForLogin();

		// printf("main login? %d\b",currentSession.isLoggedIn());
		// once logged in, process the main event loop
		currentSession.ProcessMainEventLoop();

		// input = cin
		// printf("Enter a command: ");
		// std::string input = UserInput::GetCommandInput();//UserInput::GetStringInput(0 , 25);

		// if (input == "exit" ) {
		// 	run = false;
		// 	// exit(0);
		// 	break;
		// }

		// // if (!isLoggedIn && input!="login")
		// // {
		// 	// errorPrintf("You must login before executing that command.\n");
		// 	// break;
		// 	// continue;
		// // }
		// // else
		// // {
		// 	// printf("login entered\n");
		// 	// isLoggedIn
		// // }
		

		// Command *currentCommand = Command::GetCommandNameFromInput( input , &currentSession);

		// // bool suc = 
		// currentCommand->Process();

		// std::string test = currentCommand->GetCommandName(); //->GetCommandName();
		// // int test = currentCommand->gettest();

		// printf("commandname: %s\n",test.c_str());
		// printf("testes: %d\n",currentCommand->gettest());

		// // if (input=="login" && suc) {
		// 	// isLoggedIn=true;
		// // }
		
		// printf("cs num: %d\n\n\n\n",currentSession.num);

		// delete currentCommand;


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
	//*/

	// printf("\n\ndebug: %s\n",readin.c_str());
	return 0;
}
