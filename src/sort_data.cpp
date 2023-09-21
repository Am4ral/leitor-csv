/*
Turma: 10A
Disciplina: Estrutura de Dados 2022/02
Alunos:     Guilherme dos Santos 
            Lucas Lopes
            Marco Túlio Amaral
*/



#include <iostream>
#include <fstream>
#include <string.h>
#include <cmath>
#include "data_fileds.h"

using namespace std;

// Func auxiliar para escrita em arquivo
void escreveRegistro(ofstream &arq, Fields &data)
{
    arq.write((char *)(&data), sizeof(Fields));
}

// Func auxiliar para escrita em arquivo
void lerRegistro(ifstream &arq, Fields &data)
{
    arq.read((char *)(&data), sizeof(Fields));
}

// Func auxiliar para comprar dois registros
bool comparaData(Fields d1, Fields d2)
{
    if (strcmp(d1.name, d2.name) != 0)
    {
        if (strcmp(d1.name, d2.name) < 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (d1.id < d2.id)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void merge(Fields *arr, int init, int mid, int end)
{
    auto aux = new Fields[end + 1];

    // Copiando dados para um vetor auxiliar
    for (int i = init; i <= end; i++)
    {
        aux[i] = arr[i];
    }

    int i = init;
    int j = mid + 1;
    int k = init;

    while ((i <= mid) && (j <= end))
    {
        if (comparaData(aux[i], aux[j]))
        {
            arr[k] = aux[i];
            i++;
        }
        else
        {
            arr[k] = aux[j];
            j++;
        }
        k++;
    }

    while (i <= mid)
    {
        arr[k] = aux[i];
        i++;
        k++;
    }

    while (j <= end)
    {
        arr[k] = aux[j];
        j++;
        k++;
    }
}

void mergeSort(Fields *arr, int init, int end)
{
    if (init >= end)
    {
        return;
    }
    else
    {
        int mid = floor((init + end) / 2);
        mergeSort(arr, init, mid);
        mergeSort(arr, mid + 1, end);

        merge(arr, init, mid, end);
    }
}

void intercalaArqs(string name1, string name2)
{
    cout << "INICIO DA INTERCALACAO DE ARQUIVOS \n";

    ifstream f1(name1, ios::binary);
    f1.seekg(0, ios::end);
    int size1 = (f1.tellg() / sizeof(Fields));
    f1.seekg(0, ios::beg);
    // cout << "SIZE F1: " << size1 << endl;

    ifstream f2(name2, ios::binary);
    f2.seekg(0, ios::end);
    int size2 = (f2.tellg() / sizeof(Fields));
    f2.seekg(0, ios::beg);
    // cout << "SIZE F2: " << size2 << endl;

    string fnome = "files/mergeArq";
    ofstream mergeFile(fnome, ios::binary);

    Fields dado1;
    Fields dado2;

    f1.read((char *)(&dado1), sizeof(Fields));
    f2.read((char *)(&dado2), sizeof(Fields));

    bool terminouLeitura = false;
    while (not terminouLeitura)
    {
        if (comparaData(dado1, dado2)) //Se dado1 for maior, escreve dado1 e lê o próximo valor do arquivo f1
        {
            escreveRegistro(mergeFile, dado1);
            if(!f1.read((char *)(&dado1), sizeof(Fields)))
            {
                terminouLeitura = true;
            }
        }
        else //Se dado1 for menor, escreve dado2 e lê o próximo valor do arquivo f2
        {
            escreveRegistro(mergeFile, dado2);
            if(!f2.read((char *)(&dado2), sizeof(Fields)))
            {
                terminouLeitura = true;
            }
        }
    }

    // Escreve, se tiver, oq restar do arquivo 1
    while (f1.read((char *)(&dado1), sizeof(Fields)))
    {
        escreveRegistro(mergeFile, dado1);
    }

    // Escreve, se tiver, oq restar do arquivo 2
    while (f2.read((char *)(&dado2), sizeof(Fields)))
    {
        escreveRegistro(mergeFile, dado2);
    }

    mergeFile.close();
    f1.close();
    f2.close();
}

// Faz a divisão do arquivo inciial em sub arquivos ordenados
void divideArq(string fname)
{
    cout << ("INICIO DA DIVISÃO DO ARQUIVO \n");
    ifstream input(fname, ios::binary);

    input.seekg(0, ios::end);
    int size = (input.tellg() / sizeof(Fields)) / 2;
    input.seekg(0, ios::beg);

    Fields data, dataArr[size];
    int count = 0;
    int fileCount = 1;
    string files[2];

    while (input.read((char *)&data, sizeof(Fields)))
    {
        // Separa o arquivo em blocos de dataAmount registros
        if (count < size)
        {
            dataArr[count] = data;
            count++;
        }
        else
        {
            mergeSort(dataArr, 0, size - 1); // ordena o vetor

            files[fileCount - 1] = "files/arq" + to_string(fileCount);
            ofstream file(files[fileCount - 1], ios::binary);
            // Escreve o array ordenado em um arquivo temporário
            for (int i = 0; i < size; i++)
            {
                escreveRegistro(file, dataArr[i]);
            }

            memset((void *)&data, 0, sizeof(Fields));
            memset((void *)&dataArr, 0, size * sizeof(Fields));
            count = 0;
            fileCount++;
            file.close();
        }
    }
    // Salvandoo ultimo/segundo pedaço do arquivo
    mergeSort(dataArr, 0, size - 1); // ordena o vetor

    files[fileCount - 1] = "files/arq" + to_string(fileCount);
    ofstream file(files[fileCount - 1], ios::binary);
    // Escreve o array ordenado em um arquivo temporário
    for (int i = 0; i < size; i++)
    {
        escreveRegistro(file, dataArr[i]);
    }

    memset((void *)&data, 0, sizeof(Fields));
    memset((void *)&dataArr, 0, size * sizeof(Fields));
    count = 0;

    cout << "FIM DA FASE DE DIVISAO \n";
    cout << fileCount << " ARQUIVOS PRODUZIDOS \n";
    intercalaArqs("files/arq1", "files/arq2");
}

