#ifndef METHODS_H
#define METHODS_H

#include "libraries.h"
#include "btree.h"
class Car {
public:
    string marca;
    string modelo;
    int ano;
    double preco;
    int serialNumber;
};

void setup(void);
void createFile(string fileName);
bool fileExist(string path);
vector<string> readKeys();

//funções da biblioteca interface
int showMenu(void);
void searchCar(void);
string writeCar(const Car& carro);
bool checkSize(int&input, int size);

//função para cadastrar carro
void delCar(void);
void listCars(void);
//pesquisa
bool verifyKeys(BTreeNode* root);
void modifyCar(void);
void cadCar(Car& newCar, bool modify);

ofstream file;

#endif