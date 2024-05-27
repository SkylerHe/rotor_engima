/**
 * This file contains the main function of this program. 
 * 
 * DO NOT MODIFY THIS FILE.
*/

#include <iostream>
#include <string>
#include "Enigma.h"
#include "usage.h"
using namespace std;

/**
 * Creates an Enigma machine based on command-line arguments, and reads a message
 * from the user from the standard input character stream (the terminal).
 * 
 * Decrypts/Encrypts using the Enigma class.
*/
int main(int argc, char* argv[]) 
{
    // Validate the command line arguments.
    Arguments arguments = validateCommandLineArguments(argc, argv);

    // A string to store the message.
    string message;
    
    // Get the message from the terminal by passing cin to the getline function. 
    getline(cin, message);

    // Call the Enigma's constructor to build the enigma machine.
    Enigma enigma = {arguments.innerRotorNumber, arguments.middleRotorNumber, arguments.outerRotorNumber, arguments.initialRotorPositionCharacters};

    // Encrypt or decrypt the message using the enigma object and output the results.
    if(arguments.encryptOrDecrypt == "encrypt")
    {
        cout << enigma.encrypt(message) << endl;
    }
    else
    {
        cout << enigma.decrypt(message) << endl;
    }

    return 0;
}



