#include "methods.h"
#include "btree.h"

void listCars(void){
    ifstream file(carsTable);
    system("cls");
    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo: " << carsTable << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        std::cout << line << std::endl;
    }

    file.close();
    system("pause");
    system("cls");
}


void setup(void){
    if(fileExist(carsTable)){
        return;
    }else{
        createFile(carsTable);
    }
}

bool fileExist(string path){
    ifstream isExists(path);
    if(isExists.good()){
        cout << "Arquivo encontrado!" << endl;
        isExists.close();
        return true;
    }else return false;
}

void createFile(string fileName){
    ofstream newFile;
    newFile.open(fileName);
    if(!newFile.is_open()){
        cout << "Erro ao criar o arquivo." << endl;
    }
    cout << "Arquivo criado!" << endl;
    newFile.close();
    return;
}

int showMenu(void){
    int choise;
    cout << "Fucapi automotiva." << endl;
    cout << "Qual acao deseja realizar?" << endl;
    cout << "1 - Consultar" << endl;
    cout << "2 - Cadastrar" << endl;
    cout << "3 - Modificar" << endl;
    cout << "4 - Deletar" << endl;
    cout << "5 - Listar" << endl;
    cout << "6 - Sair" << endl;
    cout << "Digite a opcao escolhida: " << '\n';
    try{
        if(cin >> choise){
            return choise;
        }else return 6;
    }catch(const exception& e){
        return 6;
    }
    
}

void searchCar(void){
    system("cls");
    string sn;
    cout << "Digite o SN do carro que deseja encontrar" << endl;
    cin >> sn;
    BTreeNode* rootNode = new BTreeNode();
    vector<string> primaryKeys = readKeys();
    rootNode->keys = primaryKeys;
    if(verifyKeys(rootNode)){
        if(rootNode->search(sn)){
            rootNode->printCar(sn);
        }
    };
}

void modifyCar(void){
    system("cls");
    string sn;
    cout << "Digite o SN do carro que deseja modificar" << endl;
    cin >> sn;
    BTreeNode* rootNode = new BTreeNode();
    vector<string> primaryKeys = readKeys();
    rootNode->keys = primaryKeys;
    if(verifyKeys(rootNode)){
        if(rootNode->search(sn)){
            rootNode->modify(sn);
        }
    }
}

void delCar(void){
    system("cls");
    string sn;
    cout << "Digite o SN do carro que deseja modificar" << endl;
    cin >> sn;
    BTreeNode* rootNode = new BTreeNode();
    vector<string> primaryKeys = readKeys();
    rootNode->keys = primaryKeys;
    if(verifyKeys(rootNode)){
        if(rootNode->search(sn)){
            rootNode->delCar(sn);
        }
    }
}

string writeCar(const Car& carro) {
    system("cls");
    try {
        ofstream file(carsTable, ios::app); // Abre o arquivo em modo de adição (append)

        if (!file.is_open()) {
            throw runtime_error("Falha ao abrir o arquivo CSV. Reiniciar sistema!");
        }

        // Escreve os dados do carro no arquivo CSV
        file << carro.marca << "," << carro.modelo << "," << carro.ano << "," << carro.preco << "," << carro.serialNumber << "\n";

        file.close();

        ofstream keys(keysFile, ios::app);
        if (!keys.is_open()) {
            throw runtime_error("Falha ao abrir o arquivo de chaves primárias. Reiniciar o sistema!");
        }

        // Adicionar a chave primária (número de série) ao arquivo de chaves
        keys << carro.serialNumber << endl;
        keys.close();

        
        return "Carro adicionado com sucesso!";
    } catch (const exception& e) {
        return "Erro ao inserir carro. " + string(e.what());
    }
}


void cadCar(Car& newCar, bool modify) {
    cout << "Digite a marca do carro: ";
    cin >> newCar.marca;
    cout << "Digite o modelo do carro: ";
    cin >> newCar.modelo;
    cout << "Digite o ano do carro: ";
    cin >> newCar.ano;
    if(!checkSize(newCar.ano, 999)){
        cout << "Ano inválido. Inicie novamente" << endl;
        system("pause");
        system("cls");
        cadCar(newCar, modify);
    }
    cout << "Digite o preço do carro: ";
    cin >> newCar.preco;
    cout << "Digite o número de série do carro: ";
    
    if(!modify){
        cin >> newCar.serialNumber;
        if(!checkSize(newCar.serialNumber, 9999)){
            cout << "Número de serie inválido. Inicie novamente" << endl;
            system("pause");
            system("cls");
            cadCar(newCar, modify);
        }
    }
    
    
}


bool checkSize(int& input, int size){
    return input > size;
}

vector<string> readKeys() {
    ifstream file(keysFile);
    vector<string> keys;

    if (file.is_open()) {
        string key;
        while (getline(file, key)) {
            keys.push_back(key);
        }
        file.close();
    } else {
        cerr << "Erro ao abrir o arquivo de chaves primárias." << endl;
    }

    return keys;
}

bool verifyKeys(BTreeNode* root) {
    if (!root) {
        cout << "Árvore B vazia." << endl;
        return false;
    }
    
    return true;
}