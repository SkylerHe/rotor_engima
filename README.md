Rotor Class (Rotor.h and Rotor.cpp):

Purpose: The Rotor class represents one of the rotors used in the Enigma machine. It defines the behavior of a rotor, including its rotation, character mapping, and initial position.
Public Methods:
    Rotor(std::string rotor_str, char initial_char): Constructor to initialize a rotor with a rotor configuration string and an initial character position.
    void rotate(): Rotates the rotor one position to the right.
    void rotateTo(char c): Rotates the rotor to a specific character.
    int findIndex(char c): Finds the index of a character in the rotor.
    char findChar(int index): Finds the character at a specific index in the rotor.
    char getInitialPosition(): Retrieves the initial position of the rotor.

private members:
    std::string rotor_list: a string to hold the rotor_list
    char initial_position: a char to represent the initial position of the rotor

Enigma Class (Enigma.h and Enigma.cpp):

Purpose: The Enigma class simulates the operation of an Enigma machine with three rotors. It handles the encryption and decryption of text.
Public Methods:
    Enigma(int innerRotorNumber, int middleRotorNumber, int outerRotorNumber, std::string initialRotorPositionChar): Constructor to initialize an Enigma machine with rotor settings.
    std::string encrypt(std::string toEncrypt): Encrypts a given text using the configured Enigma machine.
    std::string decrypt(std::string toDecrypt): Decrypts a given text using the configured Enigma machine.
Private Members:
    const std::vector<std::string> rotors: A static vector holding the rotor configurations.
    Rotor innerRotor, Rotor middleRotor, Rotor outerRotor: Instances of the Rotor class representing the inner, middle, and outer rotors.
    std::string initialRotorPositionChar: The initial positions of the three rotors.
Private Methods:
    char encryptChar(char c): Encrypts a single character based on the rotor settings.
    char decryptChar(char c): Decrypts a single character based on the rotor settings.



## Rotor.cpp

Use the space below to describe the object oriented design applied with respect to data hiding and encapsulation

Private Data Members: The class defines private data members, rotor_list and initial_position, which cannot be directly accessed or modified from outside the class. This enforces data hiding, preventing external code from tampering with the rotor's internal state.

Constructor: The class has a constructor that initializes the rotor's state. It takes in the rotor configuration string (rotor_str) and the initial character position (initial_char). The constructor ensures that the rotor is properly initialized, and it encapsulates the rotor's internal state setup.

Rotate Method: The rotate method is used to rotate the rotor one position to the right. This method is encapsulated within the class, and external code can't directly manipulate the rotor's internal position without using this method.

RotateTo Method: The rotateTo method allows the rotor to be rotated to a specific character (c). It encapsulates the logic for achieving the desired position while abstracting the internal rotor manipulation details.

FindIndex and FindChar Methods: These methods are provided for external code to interact with the rotor's configuration. The findIndex method finds the index of a character in the rotor, and the findChar method retrieves the character at a specific index. These methods encapsulate the logic for accessing rotor information.



## Enigma.cpp

Use the space below to describe the object oriented design applied with respect to data hiding and encapsulation


Static Rotor Configuration: The class includes a rotors vector that stores the rotor configurations. This vector is marked as static to ensure that it is shared among all instances of the Enigma class. It defines the available rotors for the Enigma machine.

Constructor: The class has a constructor that initializes an Enigma machine with three rotors: inner, middle, and outer. It takes the following parameters:

innerRotorNumber, middleRotorNumber, and outerRotorNumber: These parameters specify the rotor numbers (indices) for the inner, middle, and outer rotors. The indices are used to select the rotor configurations from the rotors vector.
initialRotorPositionChar: A string containing three characters that represent the initial positions of the inner, middle, and outer rotors.
Encrypt Method: The encrypt method takes a string toEncrypt as input and returns the encrypted result as a string. It performs the following steps for each character in the input:

Calls the encryptChar method to encrypt the character using the Enigma machine's rotor configuration.
Rotates the inner rotor and checks if it completes a full rotation. If so, it rotates the middle rotor. Similarly, it checks if the middle rotor completes a full rotation and rotates the outer rotor if needed.
EncryptChar Method: The encryptChar method encrypts a single character c using the Enigma machine's rotor configuration. It finds the character's index in the inner rotor, uses it to find a corresponding character in the outer rotor, then finds the index in the middle rotor, and finally uses it to find the encrypted character in the outer rotor.

Decrypt Method: The decrypt method takes a string toDecrypt as input and returns the decrypted result as a string. It follows a similar process to the encrypt method but uses the decryptChar method to decrypt each character.

DecryptChar Method: The decryptChar method decrypts a single character c using the Enigma machine's rotor configuration in reverse order. It first finds the index of the character in the outer rotor, lines it up with the middle rotor to find an intermediate character, then finds the index of that intermediate character in the outer rotor, and finally finds the decrypted character in the inner rotor.
