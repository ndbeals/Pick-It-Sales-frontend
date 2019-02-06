main: Main.o #UserInput.o #helperfunctions.o
	g++ -o main Main.o #UserInput.o #helperfunctions.o

Main.o: src/Main.cpp
	g++ -c src/Main.cpp

# UserInput.o: src/UserInput.cpp
	# g++ -g -c src/UserInput.cpp

# helperfunctions.o: src/HelperFunctions.cpp
# 	g++ -c src/HelperFunctions.cpp