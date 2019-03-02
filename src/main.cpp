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
#include <map>
#include <unistd.h>
#include <limits.h>

#include "session.h"
#include "constants.h"
#include "helperfunctions.h"
#include "userinput.h"
#include "command.h"
#include "commands/login.h"
#include "commands/logout.h"


#include "stdlib.h"
#include "stdio.h"
#include "string.h"

int parseLine(char* line){
    // This assumes that a digit will be found and the line ends in " Kb".
    int i = strlen(line);
    const char* p = line;
    while (*p <'0' || *p > '9') p++;
    line[i-3] = '\0';
    i = atoi(p);
    return i;
}

int getValue(){ //Note: this value is in KB!
    FILE* file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];

    while (fgets(line, 128, file) != NULL){
        if (strncmp(line, "VmSize:", 7) == 0){
            result = parseLine(line);
            break;
        }
    }
    fclose(file);
    return result;
}



/// \file
/**
 \brief  Main function
 \param  argc An integer argument count of the command line arguments
 \param  argv An argument vector of the command line arguments
 \return an integer 0 upon exit success
*/

int main(int argc, char *argv[]) {
	// Working dir fix
	// read the local path of the executed binary (e.g "./bin/pick-it-sales")
	std::string fullPath = readLink( "/proc/self/exe" ); 
	// cut off the end after "/"
	std::string path = fullPath.substr(0, fullPath.find_last_of("/"));
	// change working directory to that path, this ensure file read operations are local to the binary's location
	// chdir(path.c_str());

	// set the location of the user accounts file.
	if ( argc > 1 ) {
		Session::UserAccountFile = std::string( argv[1] );
		// printf("%s\n",argv[1]);
	}

	if ( argc > 2 ) {
		Session::AvailableTicketsFile = std::string( argv[2] );
	}
	if ( argc > 3 ) {
		Session::DailyTransactionFile = std::string( argv[3] );
	}
	
	


	// printf("ADHSDHS: %s\n",path.c_str());
	// chdir( readLink( "/proc/self/cwd" ).c_str() );
	
	// printf("CWD: %s to: %s\n",get_current_dir_name() );



	// sysinfo (&memInfo);
	// long long totalVirtualMem = memInfo.totalram;
	// //Add other values in next statement to avoid int overflow on right hand side...
	// totalVirtualMem += memInfo.totalswap;
	// totalVirtualMem *= memInfo.mem_unit;

	// printf("Total mem before: %d\n" , getValue());


	// Parse the following two arguments (they are the file paths, local to the binary)
	// std::string userFileLocation = "./AvailableTickets.txt"; //argv[1];

	// std::string test("./AvailableTickets.txt");

	// for(int i = 0; i < 10000; i++)
	// {
		// getFullPath(userFileLocation);
	// }
	

	// sysinfo (&memInfo);
	// totalVirtualMem = memInfo.totalram;
	// //Add other values in next statement to avoid int overflow on right hand side...
	// totalVirtualMem += memInfo.totalswap;
	// totalVirtualMem *= memInfo.mem_unit;

	// printf("Total mem after : %d\n" , getValue());

	
	// printf(" passed loc: %s %s\n",getFullPath(userFileLocation).c_str(),argv[1]);


	// hello world!
	printf("Welcome to Pick-It Sales!\n" ); //\n\nfullpath: %s\n",getFullPath( Session::UserAccountFile).c_str()

	Session currentSession;
	Session::AvailableUsers = readUsersFile();
	Session::ReadTicketsFile();
	// Session::AvailableTicketsFile = "test";
	
	while( true ){
		currentSession = Session();

		// process user input / wait until they have logged in
		currentSession.WaitForLogin();

		// once logged in, process the main event loop
		currentSession.ProcessMainEventLoop();

		// currentSession.WriteTransactionFile();

		// currently, to exit, the user type "exit" and it'll call 'exit(0)'

	}

	return 0;
}
