#ifndef ENIGMA_H
#define ENIGMA_H

#include <string>
#include <vector>
#include "Rotor.h"

class Enigma {
public:
    //constructor for three rotor in sequences
    Enigma(int innerRotorNumber, int middleRotorNumber, int outerRotorNumber, std::string initialRotorPositionChar);
    //encrypt and decrypt
    std::string encrypt(std::string toEncrypt);
    std::string decrypt(std::string toDecrypt);

private:
    static const std::vector<std::string> rotors;
    Rotor innerRotor;
    Rotor middleRotor;
    Rotor outerRotor;
    std::string initialRotorPositionChar;
    //to encrypt / decrypt a char
    char encryptChar(char c);
    char decryptChar(char c);
};

#endif // ENIGMA_H
