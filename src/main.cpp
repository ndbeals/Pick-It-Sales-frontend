#include <iostream>
#include <string>
#include <unistd.h>
#include <map>

#include "constants.h"
#include "helperfunctions.h"
#include "userinput.h"
#include "command.h"
#include "commands/login.h"
#include "commands/logout.h"
#include "session.h"

/// \file
/**
 \brief  Main function
 \param  argc An integer argument count of the command line arguments
 \param  argv An argument vector of the command line arguments
 \return an integer 0 upon exit success
*/

std::map<std::string,class User> Session::AvailableUsers;

int main(int argc, char *argv[]) {
	// read the local path of the executed binary (e.g "./bin/pick-it-sales")
	std::string fullPath(argv[0]); 
	// cut off the end after "/"
	std::string path = fullPath.substr(0, fullPath.find_last_of("/"));
	// change working directory to that path, this ensure file read operations are local to the binary's location
	chdir(path.c_str());

	// hello world!
	printf("Welcome to Pick-It Sales!\n" );

	Session currentSession;
	Session::AvailableUsers = readUsersFile();
	
	while( true ){
		currentSession = Session();

		// process user input / wait until they have logged in
		currentSession.WaitForLogin();

		// once logged in, process the main event loop
		currentSession.ProcessMainEventLoop();

		// currently, to exit, the user type "exit" and it'll call 'exit(0)'

	}

	return 0;
}
