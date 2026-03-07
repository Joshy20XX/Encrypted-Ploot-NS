#Makefile for Club Ploot/Encrypted Ploot
#If you have MinGW installed, use mingw32-make in the console to compile this

#Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -g
RM = del *.o ep_main.exe

#Target executable
TARGET = ep_main

#Object files
OBJS = ep_main.o ploot.o

all: $(TARGET)

.PHONY: all clean

#Default target goal to build
$(TARGET): $(OBJS) 
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

#Rules for main file
cp_main.o: cp_main.cpp ploot.h
	$(CXX) $(CXXFLAGS) -c ep_main.cpp -o ep_main.o

#Rules for ploot source file
ploot.o: ploot.cpp ploot.h
	$(CXX) $(CXXFLAGS) -c ploot.cpp -o ploot.o

#Pattern rule
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(TARGET) $(OBJS)
	