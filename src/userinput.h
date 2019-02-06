#ifndef USERINPUT_H
#define USERINPUT_H

namespace UserInput {

	std::string GetStringInput( uint minLength = 1 , uint maxLength = 25 );

    int GetIntegerInput( int min = 0, int max = 10000 );

	float GetFloatInput( float min = 0.0f , float max = 10000.0f );

}

#endif