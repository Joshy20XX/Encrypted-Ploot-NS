/*
    Encrypted Ploot: A chat room for your favorite ploot.
    The Network Security Version.
    Authors: Nicholas Melchiore, Edgar Zayas, Josh Ottey
*/

//For now this is just the Club Ploot main file
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include "ploot.h"
using namespace std;

//Main code (work in progress)
int main() {

    //C++ file open handling. You can also use fopen() too.
    ifstream ploot_stream("Melissa.ploot");
    
    //Return error if something bad happens to the file
    if (!ploot_stream.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }
    
    //Declaring ploot
    Ploot ploot;
    ploot.parsePloot(ploot_stream); //Parse the text file
    ploot_stream.close(); //Close the file handling for now
    
    ploot.info(); //Print the ploot's stats from the class file

}