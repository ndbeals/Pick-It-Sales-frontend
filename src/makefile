CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g -std=c++11 
LDFLAGS=-g 
LDLIBS=-L/sw/lib/root

# SRCS=main.cpp helperfunctions.cpp userinput.cpp
SRCS := $(shell find . -name "*.cpp")
OBJS=$(subst .cpp,.o,$(SRCS))

all: tool

tool: $(OBJS)
	$(CXX) $(LDFLAGS) -o tool $(OBJS) 

depend: .depend

.depend: $(SRCS)
	$(RM) ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) *~ .depend

include .depend