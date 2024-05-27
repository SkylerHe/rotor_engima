/**
 * This file holds utility functions that will validate the user input on the command line.
 * 
 * DO NOT MODIFY THIS FILE.
*/

#include <iostream>
#include <vector>
#include "usage.h"
using namespace std;

/**
 * This function will print a usage message if the command line arguments were invalid.
*/
void printUsageMessage(string executableName)
{
    cerr << endl;
    cerr << "usage: " << executableName << " <inner#> <middle#> <outer#> \"init\" (encrypt|decrypt)" << endl;
    cerr << "<inner#>           -- Rotor number for the inner rotor." << endl;
    cerr << "<middle#>          -- Rotor number for the middle rotor." << endl;
    cerr << "<outer#>           -- Rotor number for the outer rotor." << endl;
    cerr << "\"init\"             -- Initial character positions for the three rotors, e.g. \"D#Y\" or \"TLB\"" << endl;
    cerr << "(encrypt|decrypt)  -- Option to encrypt or decrypt the message." << endl;
    cerr << endl;
}


/**
 * This function will validate the command line arguments passed in to the Comms program by the user.
*/
Arguments validateCommandLineArguments(int argc, char* argv[])
{
    /**
     * argv[0] == ./Comms              -- The name of the executable file.
     * argv[1] == <inner#>             -- The rotor number for the inner rotor.
     * argv[2] == <middle#>            -- The rotor number for the middle rotor.
     * argv[3] == <outer#>             -- The rotor number for the outer rotor.
     * argv[4] == \"init\"             -- The initial character positions for the three rotors.
     * argv[5] == (encrypt|decrypt)    -- The option to encrypt or decrypt the message.
    */

    // Check for the correct # of arguments
    if(argc != 6) 
    {
        cerr << "Invalid number of arguments." << endl;
        printUsageMessage(argv[0]);
        exit(1);
    }

    // Create three ints to store the rotor numbers. 
    int innerRotorNumber, middleRotorNumber, outerRotorNumber;

    // Try to convert the rotor number arguments from string to integer using the stoi function.
    try
    {
        innerRotorNumber = stoi(argv[1]);
        middleRotorNumber = stoi(argv[2]);
        outerRotorNumber = stoi(argv[3]);
    }
    catch(const invalid_argument& exception)
    {
        cerr << "Invalid rotor number." << endl;
        printUsageMessage(argv[0]);
        exit(1);       
    }

    // Put the rotor numbers in a vector.
    vector<int> rotorNumbers = {innerRotorNumber, middleRotorNumber, outerRotorNumber};

    // Use a for-each style loop to validate the router numbers.
    for(int rotorNumber : rotorNumbers) 
    {
        if(rotorNumber < 1 || rotorNumber > 5 ) 
        {
            cerr << "Invalid rotor number: " << rotorNumber << endl;
            printUsageMessage(argv[0]);
            exit(1);
        }
    }

    // Get the initial rotor positions from the command line and validate.
    string initialRotorPositionCharacters = argv[4];

    // Validate the length of the initial rotor position characters. 
    if (initialRotorPositionCharacters.length() != 3)
    {
        cerr << "Incorrect number of initial character positions for the three rotors." << endl;
        printUsageMessage(argv[0]);
        exit(1);
    }

    // The valid initial rotor positions.
    string validInitialRotorPositionCharacters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ#";

    // Use a for-each style loop to validate the characters in the initial rotor positions.
    for (char character : initialRotorPositionCharacters)
    {
        // Initialize the isValidCharacter to false.
        bool isValidCharacter = false;

        // Use a for-each style loop to loop through the valid characters.
        for (char validCharacter : validInitialRotorPositionCharacters)
        {
            if (character == validCharacter)
            {
                isValidCharacter = true;
                // Break out of the inner for loop.
                break;  
            }
        }

        if (!isValidCharacter)
        {
            cerr << "Invalid character in the initial character positions for the three rotors: " << character << endl;
            printUsageMessage(argv[0]);
            exit(1);
        }
    }

    // Encrypt or decrypt argument
    string encryptOrDecrypt = argv[5];

    // Validate the encrypt or decrypt argument.
    if(encryptOrDecrypt != "encrypt" && encryptOrDecrypt != "decrypt")
    {
        cerr << "Invalid option to encrypt or decrypt: " << encryptOrDecrypt << endl;
        printUsageMessage(argv[0]);
        exit(1);
    }

    // Create and populate an arguments struct. 
    Arguments arguments = {innerRotorNumber, 
                           middleRotorNumber, 
                           outerRotorNumber, 
                           initialRotorPositionCharacters, 
                           encryptOrDecrypt};

    // Return the valid arguments.
    return arguments;
}