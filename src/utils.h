
/*
    Funções responsáveis por realizar funcionalidades diversas, que não se encaixavão em outros arquivos
*/

#include <iostream>

using namespace std;

void clear_terminal(){
    #if defined _WIN32
        system("cls");
    #elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
        system("clear");
    #elif defined (__APPLE__)
        system("clear");
    #endif
}

void print_menu(){
    cout << "+-------------------------------------+" << endl;
    cout << "| [1] ADD ELEMENT                     |" << endl;
    cout << "|-------------------------------------|" << endl;
    cout << "| [2] EDIT ELEMENT                    |" << endl;
    cout << "|-------------------------------------|" << endl;
    cout << "| [3] SWAP ELEMENTS                   |" << endl;
    cout << "|-------------------------------------|" << endl;
    cout << "| [4] SHOW A SECTION OF THE DATASET   |" << endl;
    cout << "|-------------------------------------|" << endl;
    cout << "| [5] SHOW COMPLETE DATASET           |" << endl;
    cout << "|-------------------------------------|" << endl;
    cout << "| [0] EXIT                            |" << endl;
    cout << "+-------------------------------------+" << endl;
}