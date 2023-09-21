/*
    Classe responsável por realizar as operações dentro do arquivo binário
*/

#include <iostream>
#include <string.h>
#include <fstream>
#include "data_fileds.h"

using namespace std;


class Operations{
    private:
        string binFile;
        Fields data;
    public:
        Operations(string binFile);
        ~Operations();
        void showDataInterval(int first, int last);
        void addElement(int position);
        void editElement(int position);
        void swapElements(int position1, int position2);
        void showAllData();

};

Operations::Operations(string path){
    binFile = path;
}

//first: its the first position of the interval that we want to read
//last: its the last position of the interval that we want to read
void Operations::showDataInterval(int first, int last){
    ifstream file (binFile, ios::binary);
    if(!file.good()){
        cerr << "Error trying to open the file";
        exit(EXIT_FAILURE);
    }

    for(int i=first; i<=last; i++){
        memset((void*) &data,0,sizeof(Fields)); // Cleaning the struct data

        int readingPosition = i*sizeof(Fields);
        file.seekg(readingPosition, ios::beg);

        file.read((char *)&data, sizeof(Fields));

        data.showData();
        cin.clear(); //reset de buffer
    }
    cin.clear(); //reset de buffer
}

void Operations::showAllData(){
    cout << "DISPLAING ALL THE DATA \n";
    ifstream file (binFile, ios::binary);
    if(!file.good()){
        cerr << "Error trying to open the file";
        exit(EXIT_FAILURE);
    }

    file.seekg(0,ios::end);
    int size = (file.tellg())/sizeof(Fields);
    cout << "Size: " << size << endl;
    file.seekg(0,ios::beg);
    for(int i=0; i<size; i++){
        memset((void*) &data,0,sizeof(Fields)); // Cleaning the struct data
        file.read((char *)&data, sizeof(Fields));

        data.showData();
    }
    file.close();
    cin.clear(); //reset de buffer
}

void Operations::editElement(int pos){
    ifstream inFile(binFile, ios::binary);
    if(!inFile.good()){
        cerr << "Error trying to open the file";
        exit(EXIT_FAILURE);
    }

    int position = pos*sizeof(Fields);

    inFile.seekg(position, ios::beg);

    inFile.read((char *)&data, sizeof(Fields));

    //Getting the new element
    cout << "DO NOT TYPE EXTRA COMMAS (',')! \n";
    cout << "<ID>, <NAME>, <CITY>, <SPORT>, <EVENT>, <NOC> \n";
    string line;
    cin.ignore();
    getline(cin, line);
    sscanf(line.c_str(), "%u, %[^,], %[^,], %[^,], %[^,], %[^,]",&data.id, data.name, data.city, data.sport, data.event, data.noc);

    ofstream outFile(binFile, std::ios_base::binary | std::ios_base::out | std::ios_base::in);
    outFile.seekp(position, ios::beg);
    if(!outFile.good()){
        cerr << "Error trying to open the file";
        exit(EXIT_FAILURE);
    }
    data.saveToFile(outFile);
}

void Operations::swapElements(int pos1, int pos2){
    Fields aux;

    ifstream inFile(binFile, ios::binary);
    if(!inFile.good()){
        cerr << "Error trying to open the file";
        exit(EXIT_FAILURE);
    }
    ofstream outFile(binFile, std::ios_base::binary | std::ios_base::out | std::ios_base::in);
    if(!outFile.good()){
        cerr << "Error trying to open the file";
        exit(EXIT_FAILURE);
    }

    //Getting the 1 element
    int elementOnePosition = pos1*sizeof(Fields);
    inFile.seekg(elementOnePosition, ios::beg);
    inFile.read((char *)&data, sizeof(Fields));
    cin.clear();

    //Getting the 2 element
    int elementTwoPosition = pos2*sizeof(Fields);
    inFile.seekg(elementTwoPosition, ios::beg);
    inFile.read((char *)&aux, sizeof(Fields));
    cin.clear();

    //Saving the 1 on the 2 space
    outFile.seekp(elementTwoPosition, ios::beg);
    data.saveToFile(outFile);

    //Saving the 2 on the 1 space
    outFile.seekp(elementOnePosition, ios::beg);
    aux.saveToFile(outFile);

    cin.clear();
}

void Operations::addElement(int pos){
    ofstream file(binFile, ios_base::binary | ios_base::app);
    if(!file.good()){
        cerr << "Error trying to open the file";
        exit(EXIT_FAILURE);
    }

    //Getting the new element
    cout << "DO NOT TYPE EXTRA COMMAS (',')! \n";
    cout << "<ID>, <NAME>, <CITY>, <SPORT>, <EVENT>, <NOC> \n";
    string line;
    cin.ignore();
    getline(cin, line);
    sscanf(line.c_str(), "%u, %[^,], %[^,], %[^,], %[^,], %[^,]",&data.id, data.name, data.city, data.sport, data.event, data.noc);
    data.saveToFile(file);

    file.seekp(0,ios::end);
    int size = (file.tellp())/sizeof(Fields)-1;
    cout << "Size: " << size << endl;
    cin.clear();
    file.seekp(0,ios::beg);

    int newElementPosition = size;
    for(int i=size; i>pos; i--){
        swapElements(newElementPosition, newElementPosition-1);
        newElementPosition--;
    }
}

    
//Ordenacao Externa 













