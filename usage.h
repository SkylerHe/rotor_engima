/**
 * Header file for the usage functions.
 * 
 * DO NOT MODIFY THIS FILE.
*/

#include <string>

/**
 * Structure to hold the valid command line arguments.
*/
struct Arguments
{
    int innerRotorNumber;
    int middleRotorNumber;
    int outerRotorNumber;
    std::string initialRotorPositionCharacters;
    std::string encryptOrDecrypt;
};

void printUsageMessage(std::string executableName);
Arguments validateCommandLineArguments(int argc, char* argv[]);