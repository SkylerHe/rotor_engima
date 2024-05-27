
#include "Enigma.h"
#include <string>

//set the default rotor
const std::vector<std::string> Enigma::rotors = {
    "#GNUAHOVBIPWCJQXDKRYELSZFMT",
    "#EJOTYCHMRWAFKPUZDINSXBGLQV",
    "#BDFHJLNPRTVXZACEGIKMOQSUWY",
    "#NWDKHGXZVRIFJBLMAOPSCYUTQE",
    "#TGOWHLIFMCSZYRVXQABUPEJKND"
};
//Constructor
Enigma::Enigma(int innerRotorNumber, int middleRotorNumber, int outerRotorNumber, std::string initialRotorPositionChar)
: innerRotor(rotors[innerRotorNumber - 1], initialRotorPositionChar[0]),
  middleRotor(rotors[middleRotorNumber - 1], initialRotorPositionChar[1]),
  outerRotor(rotors[outerRotorNumber - 1], initialRotorPositionChar[2]),
  initialRotorPositionChar(initialRotorPositionChar)
{}

std::string Enigma::encrypt(std::string toEncrypt) 
{
    std::string result;
    int charCount = 0; // Counter to keep track of characters encrypted
    int rotorSize = rotors[0].length();
    for(char& c: toEncrypt) {
        result += encryptChar(c);
        //Increment the character counter
        charCount++;
        // Rotate the inner rotor
        innerRotor.rotate();

        // Check if the inner rotor completed a full rotation
        if (charCount % rotorSize == 0) {
            // Rotate the middle rotor if the inner rotor completed a full rotation
            middleRotor.rotate();
        }

        // Check if the middle rotor completed a full rotation
        if (charCount % (rotorSize * rotorSize) == 0) {
            // Rotate the outer rotor if the middle rotor completed a full rotation
            outerRotor.rotate();
        }
    }
    return result;
}

char Enigma::encryptChar(char c) {
    //set an index
    int index;
    //find the character in inner rotor
    index = innerRotor.findIndex(c);
    //find the char in outer rotor 
    char outerChar = outerRotor.findChar(index);
    //use the char in outer rotor to find the index
    index = middleRotor.findIndex(outerChar);
    //use the index to find the char in outer
    char encrypted = outerRotor.findChar(index);

    return encrypted;
}

std::string Enigma::decrypt(std::string toDecrypt) 
{
    std::string result;
    int charCount = 0; // Counter to keep track of characters decrypted
    int rotorSize = rotors[0].length();
    
    for(char& c: toDecrypt) {
        result += decryptChar(c);

        // Increment the character counter
        charCount++;

        // Rotate the inner rotor after every character
        innerRotor.rotate();
        // Check if the outer rotor completed a full rotation
        if (charCount % rotorSize == 0) {
            // Rotate the middle rotor if the outer rotor completed a full rotation
            middleRotor.rotate();
        }

        // Check if the middle rotor completed a full rotation
        if (charCount % (rotorSize * rotorSize) == 0) {
            // Rotate the outer rotor if the middle rotor completed a full rotation
            outerRotor.rotate();
        }
    }
    return result;
}


char Enigma::decryptChar(char c) {
    //set an index
    int index;
    //find the index in outer rotor
    index = outerRotor.findIndex(c);
    //line up with the middle rotor and find the char
    char middleChar = middleRotor.findChar(index);
    //and find the char in outer rotor, keep the index
    index = outerRotor.findIndex(middleChar);
    //find the final answer in inner rotor
    char decrypted = innerRotor.findChar(index);

    return decrypted;
}