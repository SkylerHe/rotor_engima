#ifndef ROTOR_H
#define ROTOR_H

#include <string>

class Rotor 
{
public:
    //Define rotor, initial_char
    Rotor(std::string rotor_str, char initial_char);
    //rotate the rotor
    void rotate();
    //rotate to the specific character
    void rotateTo(char c);
    //find index
    int findIndex(char c);
    //find char
    char findChar(int index);
    //get the initial position, it will return you initial_position
    char getInitialPosition() { return initial_position; }

private:
    std::string rotor_list;
    char initial_position;
};

#endif // ROTOR_H
