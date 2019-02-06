#ifndef COMMAND_H
#define COMMAND_H

class Command
{
private:
    /* data */
public:
    int val;
    Command(/* args */);
    ~Command();

    virtual bool Process();

    static Command* GetCommand( std::string );
};





#endif