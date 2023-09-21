/*
    Classe responsável por realizar a conversão do arquivo CSV para binário
*/


#include <iostream>
#include <string.h>
#include <fstream>
#include "data_fileds.h"

using namespace std;

class CsvToBin{
    private:
        Fields fields;
        void dataTreatment(string fileLine);
    public:
        string csvFile;
        string binFile;
        bool readStatus;
        CsvToBin(string, string);
        ~CsvToBin();
        void convertCsv();
};

CsvToBin::CsvToBin(string csv, string bin){
    csvFile = csv;
    binFile =  bin;
    readStatus = false;
}

CsvToBin::~CsvToBin(){}

void CsvToBin::convertCsv(){
    ifstream csv(csvFile);
    ofstream bin(binFile, ios::binary); 
    
    if(!bin.good()){
        cerr << "Error creating the file" << endl;
        exit(EXIT_FAILURE);
    }

    string line, headerLine;

    getline(csv, headerLine); // discard the header line of the csv

    while(csv.good()){
        memset((void*) &fields,0,sizeof(Fields)); // Cleaning the struct data

        getline(csv, line);

        //Verify if there number os ',' on the line
        int commaCont = 0;
        for(int i=0; i<line.size();i++){
            if(line[i] == ','){
                commaCont++;
            }
        }

        // if there is more then 5 commas, than its necessary to treat this line separetaly 
        // to avoid reading mistakes between separators and text
        if(commaCont > 5){
            dataTreatment(line);
        }
        else{
            sscanf(line.c_str(), "%u, %[^,], %[^,], %[^,], %[^,], %[^,]",&fields.id, fields.name, fields.city, fields.sport, fields.event, fields.noc);
        }

        fields.saveToFile(bin);
    }
    readStatus = true;
    csv.close();
    bin.close();
}


//Iterate char by char in order to save data with ',' within it
void CsvToBin::dataTreatment(string line){
    int quotationCont = 0;
    int columnCont = 1;
    string tempColumn = "";
    for(int i = 0; i < line.size(); i++){
        if(line[i] == '"'){
            quotationCont++;
        }
        if(line[i] != ',' or (line[i] == ',' and quotationCont % 2 != 0)){
            tempColumn += line[i];
        }
        if((line[i] == ',' and (quotationCont == 0 or quotationCont == 2)) or (i == line.size()-1)){
            switch (columnCont){
                case 1:
                    fields.id = stoi(tempColumn);
                case 2:
                    for(int i = 0; i < tempColumn.size(); i++)
                        fields.name[i] = tempColumn[i];
                    break;
                case 3:
                    for(int i = 0; i < tempColumn.size(); i++)
                        fields.city[i] = tempColumn[i];
                    break;
                case 4:
                    for(int i = 0; i < tempColumn.size(); i++)
                        fields.sport[i] = tempColumn[i];
                    break;
                case 5:
                    for(int i = 0; i < tempColumn.size(); i++)
                        fields.event[i] = tempColumn[i];
                    break;
                case 6:
                    for(int i = 0; i < tempColumn.size(); i++)
                        fields.noc[i] = tempColumn[i];
                    break;
            }
            tempColumn.clear();
            quotationCont = 0;
            columnCont++;
        }
    }
}