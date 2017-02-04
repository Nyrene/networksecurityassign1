/* 
 * File:   main.cpp
 * Author: jhansen3
 *
 * Created on February 3, 2015, 8:23 PM
 */

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>
using namespace std;

void regularHash(char* fileName, void* result) {
    ifstream fin;
    int counter = 0;
    char temp;
    unsigned char state[4] = {0xe7, 0xe8, 0x7c, 0x8c}; // Set initial state

    fin.open(fileName, fstream::in | fstream::binary); // open specified file

    fin.read(&temp, 1); // Read a single byte of the file
    while (!fin.fail() && !fin.eof()) { // As long as we're still getting bytes
        state[counter] = state[counter] ^ temp; // XOR the new byte with the current state byte
        counter = (counter + 1) % 4; // move over to the next state byte, wrapping if necessary

        fin.read(&temp, 1); // Get the next byte from the file
    }
 
    memcpy(result, state, 4); // Copy over the hash to the result variable

    return;
}

void strongerHash(char* fileName, void* result) {
    ifstream fin;
    int counter = 0;
    char temp;
    unsigned char* utemp = (unsigned char*)&temp; // make sure we can treat this as an unsigned char later
    unsigned char state[8] = {0xe7, 0xe8, 0x7c, 0x8c, 0xff, 0x00, 0xff, 0x00}; // Set initial state
    unsigned char box1[256] = // First substitution box
    {121, 105, 54, 110, 51, 182, 197, 38, 149, 23, 236, 33, 222, 233, 224,
        104, 59, 244, 218, 146, 201, 102, 230, 10, 206, 115, 117, 96, 133, 24,
        196, 162, 70, 140, 92, 37, 164, 6, 169, 34, 82, 186, 215, 204, 170, 217,
        130, 131, 106, 36, 177, 75, 16, 19, 98, 136, 88, 192, 248, 221, 66, 198,
        78, 234, 69, 240, 46, 171, 41, 226, 90, 72, 252, 151, 153, 245, 180,
        175, 119, 42, 173, 155, 148, 235, 184, 214, 64, 125, 154, 39, 137, 127,
        20, 123, 168, 188, 167, 87, 247, 161, 205, 229, 124, 156, 141, 103, 18,
        241, 212, 86, 232, 114, 107, 9, 227, 0, 27, 73, 209, 12, 22, 5, 26, 60,
        7, 40, 172, 253, 3, 80, 79, 152, 100, 126, 50, 251, 208, 74, 55, 193,
        15, 95, 65, 8, 203, 210, 43, 135, 237, 134, 1, 147, 31, 120, 44, 11,
        158, 101, 159, 225, 139, 68, 145, 53, 63, 239, 255, 165, 83, 62, 128,
        216, 94, 81, 179, 181, 223, 143, 91, 61, 254, 116, 211, 132, 187, 109,
        142, 163, 174, 58, 25, 14, 246, 99, 4, 220, 243, 176, 190, 228, 32, 242,
        13, 47, 183, 28, 17, 129, 67, 144, 49, 178, 157, 84, 2, 108, 29, 113,
        238, 52, 111, 118, 122, 207, 77, 48, 160, 89, 21, 249, 191, 231, 166,
        194, 76, 213, 195, 85, 45, 56, 97, 150, 185, 199, 71, 93, 138, 35, 57,
        250, 112, 219, 202, 189, 30, 200};

    unsigned char box2[256] = // Second substitution box
    {251, 126, 59, 224, 193, 168, 228, 245, 129, 17, 37, 96, 6, 196, 29, 0,
        179, 189, 170, 58, 72, 44, 36, 217, 61, 88, 226, 171, 130, 147, 135, 82,
        172, 11, 214, 90, 183, 185, 248, 65, 173, 201, 200, 177, 32, 42, 202, 206,
        95, 50, 149, 133, 209, 164, 47, 80, 198, 139, 252, 165, 125, 86, 154, 253,
        103, 117, 205, 127, 101, 64, 231, 100, 10, 33, 12, 31, 247, 81, 56, 111, 54,
        89, 208, 153, 70, 71, 55, 181, 27, 69, 184, 39, 235, 163, 157, 46, 9, 51,
        83, 114, 66, 207, 102, 7, 197, 16, 218, 118, 213, 169, 110, 68, 14, 98, 122,
        120, 97, 151, 232, 246, 242, 49, 211, 254, 26, 128, 199, 222, 43, 238, 145,
        158, 166, 142, 85, 215, 230, 236, 210, 138, 34, 35, 241, 1, 167, 234, 22,
        93, 204, 77, 41, 87, 108, 121, 223, 152, 132, 144, 78, 116, 187, 178, 8,
        180, 15, 60, 57, 237, 141, 2, 182, 52, 192, 73, 74, 62, 229, 113, 20, 75,
        137, 106, 107, 79, 124, 99, 40, 119, 243, 250, 255, 156, 5, 216, 225, 53,
        84, 219, 227, 91, 92, 109, 131, 67, 123, 115, 159, 244, 4, 221, 140, 155,
        162, 105, 136, 38, 143, 150, 174, 13, 161, 188, 28, 203, 191, 239, 233, 104,
        195, 176, 30, 160, 25, 112, 94, 21, 146, 76, 186, 63, 212, 48, 23, 148, 249,
        24, 190, 175, 134, 45, 18, 19, 194, 240, 3, 220};


    fin.open(fileName, fstream::in | fstream::binary); // open specified file

//    cout << "Opening " << fileName << endl;
    
    fin.read(&temp, 1); // Read a single byte of the file
    while (!fin.fail() && !fin.eof()) { // As long as we're still getting bytes
        // Hash transformations   
        if (counter % 5 == 0)
            state[counter % 8] ^= box1[*utemp]; // hash transformations
        else if (counter % 5 == 1)
            state[counter % 8] ^= *utemp ^ box2[*utemp]; // hash transformations
        else if (counter % 5 == 2)
            state[counter % 8] ^= (box2[*utemp] << 4) | (box1[*utemp] >> 4) ; // hash transformations
        else if (counter % 5 == 3)
            state[counter % 8] ^= *utemp ^ box1[*utemp];
        else
            state[counter % 8] ^= box2[*utemp];
                    
        counter++; // move over to the next state byte, wrapping if necessary

        fin.read(&temp, 1); // Get the next byte from the file
    }

    state[counter % 8]  ^= box2[counter%256] ^ box1[counter%256]; // add length of file to hash (pseudo-MD-Strengthening))
    
    state[0] = state[0] ^ state[1];
    state[1] = state[2] ^ state[3];
    state[2] = state[4] ^ state[5];
    state[3] = state[6] ^ state[7];
    
    memcpy(result, state, 4); // Copy over the hash to the result variable

    return;
}

int main(int argc, char** argv) {

    unsigned char* hashOut = new unsigned char[4];

//    cout << "Command line: (" << argc << ')' << endl;
//    for (int i = 0; i < argc; i++)
//        cout << argv[i] << ' ';
    
//    cout << endl;
    
    if (argc == 3) // If the user asks for strength 
        strongerHash(argv[2], hashOut); // Call the stronger function
    else
        regularHash(argv[1], hashOut); // Otherwise call the regular one

    for (int i = 0; i < 4; i++)
        cout << setfill('0') << setw(2) << hex << (int)(hashOut[i]);

    delete [] hashOut;

    return 0;
}

