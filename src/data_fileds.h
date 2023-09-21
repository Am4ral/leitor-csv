/*
    Esse arquivo possui uma struct que representa o os campos do arquivo csv
*/

#ifndef FIELDS
#define FIELDS

#include <iostream>
#include <fstream>

using namespace std;

struct Fields{
    unsigned int id;
    char name[80];
    char city[80];
    char sport[80];
    char event[120];
    char noc[4];

    void showData(){
        cout << "\t[ " << id << ", " << name << ", " << city << ", " << sport 
                      << ", " << event << ", " << noc << " ]\n";
    }

    void saveToFile(ofstream& outputFile){
        outputFile.write((const char *)this, sizeof(Fields));
        if(!outputFile.good()){
            cerr << "Error during file saving!";
            exit(EXIT_FAILURE);
        }
    }
};

#endif