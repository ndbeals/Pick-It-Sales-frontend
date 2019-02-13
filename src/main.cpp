/** Pick-It Sales Ticket Purchasing System
 * 
 * This is a console application for a ticket purchasing system. 
 * The system is meant to be built and run using a series of bash commands.
 *
 * This ticket purchasing system handles the following transactions:
 * 		00 - End of session
 * 		01 - Create
 * 		02 - Delete
 * 		03 - Sell
 * 		04 - Buy
 * 		05 - Refund
 * 		06 - AddCredit
 * 
 * Functionality for user session authorization is implemented to ensure that only
 * priviliged users can complete certain transactions (ie. transactions 03, 02).
 * 
 * Input Files:
 * 	currentusers.txt
 * 		File which contains the current user list.
 *  availabletickets.txt
 * 		Files which contains the details of the tickets available for purchase
 * 
 * Output Files:
 * 	At the end of each session, when the logout transaction is processed, a daily 
 * transaction file for the day is written, listing every transaction made in the 
 * session.
 * 
 * @author		Nathan Beals, Nadia Goralski, Alex Waddell
 * @version		2019.proto
 * @since		January 2019
 *
 */
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
