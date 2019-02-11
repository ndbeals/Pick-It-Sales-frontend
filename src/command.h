#ifndef COMMAND_H
#define COMMAND_H

#include "session.h"

class Command
{
private:
    static const char TransactionNumber;

    // virtual bool validateInput( std::string );

    // processInput();
protected:

    Session* userSession;


    int testes;
public:
    // Variable block
    static const std::string CommandName;
    

    // Method block
    // Command( Session );
    Command(  );
    Command( Session* );
    virtual ~Command();

    virtual bool Process();

    Session* getSession() { return userSession; }


    virtual std::string GetCommandName() { return "empty"; }





    const char GetTransactionNumber() { return TransactionNumber; }

    virtual int gettest() {return testes;}

    static Command* GetCommandNameFromInput( std::string , Session* );
};





#endif