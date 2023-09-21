/*
    Aruqivo main: Possui a função principal, ele realiza a coneção das classes e faz com que o programa funcione como um só
*/

#include <iostream>
#include <fstream>
#include <cstdio>
#include "csv_to_bin.h"
#include "operations.h" 
#include "utils.h"

using namespace std;

int main(){
    string dataPath, binPath;
    cout << "+---------------------------------------------+\n";
    cout << "|                  FILE PATHS                 |\n";
    cout << "+---------------------------------------------+\n";
    cout << "CSV PATH: ";
    cin >> dataPath;
    cout << "BINARY PATH: ";
    cin >> binPath;
    
    //Converting file
    auto conversor = new CsvToBin(dataPath, binPath);
    conversor->convertCsv();

    if(!conversor->readStatus){
        cerr << "Something went wrong during conversion";
        exit(EXIT_FAILURE);
    }

    clear_terminal();

    cout << "CONVERTED FILE AT: " << binPath << endl;


    cout << "+---------------------------------------------+\n";
    cout << "|                 OPERATIONS                  |\n";
    cout << "+---------------------------------------------+\n";
    bool menu = true;
    int menuOpt;
    int pos1, pos2;
    auto operations = new Operations(binPath);

    while(menu){
        print_menu();
        cout << "-> ";
        cin >> menuOpt;
        switch (menuOpt)
        {
        case 1:
            clear_terminal();
            cout << "+------------------------------+" << endl;
            cout << "|           ADD ELEMENT        |" << endl;
            cout << "+------------------------------+" << endl;
            cout << "POSITION: ";
            cin >> pos1;
            operations->addElement(pos1);
            cout << "ELEMENT ADDED! \n";
            operations->showAllData();
            break;
        case 2:
            clear_terminal();
            cout << "+------------------------------+" << endl;
            cout << "|          EDIT ELEMENT        |" << endl;
            cout << "+------------------------------+" << endl;
            cout << "POSITION: ";
            cin >> pos1;
            operations->editElement(pos1);
            cout << "ELEMENT EDITED! \n";
            operations->showAllData();
            break;
        case 3:
            clear_terminal();
            cout << "+------------------------------+" << endl;
            cout << "|         SWAP ELEMENTS        |" << endl;
            cout << "+------------------------------+" << endl;
            cout << "POSITION 1: ";
            cin >> pos1;
            cout << "POSITION 2: ";
            cin >> pos2;
            operations->swapElements(pos1, pos2);
            cout << "ELEMENTS SWAPED! \n";
            operations->showAllData();
            break;
        case 4:
            clear_terminal();
            cout << "+------------------------------+" << endl;
            cout << "|          SHOW SECTION        |" << endl;
            cout << "+------------------------------+" << endl;
            cout << "POSITION 1: ";
            cin >> pos1;
            cout << "POSITION 2: ";
            cin >> pos2;
            operations->showDataInterval(pos1, pos2);
            break;
        case 5:
            clear_terminal();
            cout << "+------------------------------+" << endl;
            cout << "|          SHOW DATESET        |" << endl;
            cout << "+------------------------------+" << endl;
            operations->showAllData();
            break;
        case 0:
            menu = false;
            break;
        default:
            cout << "INVALID OPTION!";
            break;
        }

    }
    return 0;
}