#ifndef USER_H
#define USER_H


#include <string>
#include <vector>

// #include "ticketbatch.h"
#include "session.h"

// enum Session::SessionState;


class User
{
private:
    std::string userName;
    std::string userType;

    float userBalance;
public:
    User(/* args */);
    User(std::string, std::string,float);
    ~User();



    /// Getters/setters
    /// setUserType sets the user type string
    void setUserType( std::string newType ) { this->userType = newType; };
    /// UserType
    std::string getUserType(){ return this->userType; };
    /// Get the correct session state that this user will be when logged in
    Session::SessionState getLoggedInSessionState();

    /// Username
    std::string getUserName() { return this->userName; };
    void setUserName( std::string newName ) { this->userName = newName; };

    /// User Balance
    float getUserBalance() { return this->userBalance; };
    void setUserBalance( float newBalance ) { this->userBalance = newBalance; };
};




#endif