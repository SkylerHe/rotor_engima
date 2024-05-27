#include "Rotor.h"
#include <iostream>
#include <string>

// Constructor: Initialize rotor_list and initial_position, and rotate to initial_char
Rotor::Rotor(std::string rotor_str, char initial_char)
    : rotor_list(rotor_str), initial_position(initial_char)
{
    //set to the initial position
    rotateTo(initial_char);
}

// Rotate the rotor one position to the right
void Rotor::rotate()
{
    if (rotor_list.length() > 0)
    {
        char last_char = rotor_list.back();
        rotor_list.pop_back();
        rotor_list.insert(rotor_list.begin(), last_char);
    }

} 
//Rotate to a specific character
void Rotor::rotateTo(char c)
{
    while(rotor_list.length() > 0 && rotor_list[0] != c)
    {
        rotate();
    }
}


// Find the index of a character in the rotor
int Rotor::findIndex(char c)
{
    int len = rotor_list.length();
    for(int i = 0; i < len; i++)
    {
        if(rotor_list[i] == c)
            return i;
    }
    return -1; // Return -1 if character not found
}
// Find the character at a specific index in the rotor
char Rotor::findChar(int index)
{   
    int len = rotor_list.length();
    if(index >= 0 && index < len)
        return rotor_list[index];
    return '#'; // Return # as a default if index is out of bounds
}
