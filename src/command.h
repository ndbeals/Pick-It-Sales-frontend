#ifndef COMMAND_H
#define COMMAND_H

class Command
{
private:
    std::string commandName;
    char transactionNumber;

    // virtual bool validateInput( std::string );

    // processInput();
public:
    int val;
    Command(/* args */);
    virtual ~Command();

    virtual bool Process();

    static Command* GetCommand( std::string );
};





#endif