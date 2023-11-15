#include "main.h"
using namespace std;

//ios::app para adicionar conteúdo


class Car {
public:
    string marca;
    string modelo;
    int ano;
    double preco;
    int serialNumber;
};

void cadCar(Car& newCar, bool modify);

class BTreeNode {
    public:
        vector<string> keys;
        vector<BTreeNode*> children;

        BTreeNode() {}

        // Função para buscar uma chave na árvore B
        bool search(const string& key) {
            auto it = lower_bound(keys.begin(), keys.end(), key);

            if (it != keys.end() && *it == key) {
                cout << "Registro encontrado para a chave: " << key << endl;
                return true;
            }

            if (children.empty()) {
                cout << "Registro nao encontrado para a chave: " << key << endl;
                system("pause");
                return false;
            }

            int index = it - keys.begin();
            return children[index]->search(key);
        }

        void modify(const string& key) {

            ofstream tempFile(tempTable, ios::out);

            Car newReg;
            cadCar(newReg, true);
            newReg.serialNumber = stoi(key);
            bool isReg = false;
            ifstream carFile(carsTable);
                if (carFile.is_open()) {
                    string line;
                    while (getline(carFile, line)) {
                        if (line.find(key) != string::npos) {
                            line = newReg.marca + "," + newReg.modelo + "," + to_string(newReg.ano) + "," + to_string(newReg.preco) + "," + to_string(newReg.serialNumber)  + "\n";
                            cout << "Registro alterado com sucesso!" << endl;
                            isReg = true;
                            break;
                        }

                        tempFile << line << endl;
                        carFile.close();
                        tempFile.close();
                    }

                    if(isReg){
                        if (std::remove(carsTable) != 0) {
                            std::cerr << "Erro ao excluir o arquivo original." << std::endl;
                            return;
                        }

                        if (std::rename(tempTable, carsTable) != 0) {
                            std::cerr << "Erro ao renomear o arquivo temporário." << std::endl;
                            return;
                        }

                        std::cout << "Registro modificado com sucesso." << std::endl;
                    }

                    
                } else {
                    cerr << "Erro ao abrir o arquivo de carros." << endl;
                }
        }


        void delCar(const string& key){

            vector<string> files = {carsTable, keysFile};

            for(int i = 0; i<=1; i++){

                string file = files[i];
                ifstream inputFile(file);
                ofstream tempFile(tempTable, ios::out);
                if (!inputFile.is_open() || !tempFile.is_open()) {
                    cerr << "Erro ao abrir arquivos." << endl;
                    return;
                }

                string linha;

                while (getline(inputFile, linha)) {
                    if (linha.find(key) == string::npos) {
                       
                        tempFile << linha << endl;
                    }
                }

                inputFile.close();
                tempFile.close();

                if (remove(file.c_str()) != 0) {
                    cerr << "Erro ao excluir o arquivo original." << endl;
                    return;
                }

                if (rename(tempTable,file.c_str()) != 0) {
                    cerr << "Erro ao renomear o arquivo temporário." << endl;
                    return;
                }

                
            }
            cout << "Registro deletado com sucesso." << endl;
            system("pause");
            system("cls");
        }


        void printCar(const string& chave) {
        ifstream carFile(carsTable);
        if (carFile.is_open()) {
            string linha;
            while (getline(carFile, linha)) {
                if (linha.find(chave) != string::npos) {
                    cout << "Informações do Carro:\n" << linha << endl;
                    system("pause");
                    system("cls");
                    break;
                }
            }
            carFile.close();
        } else {
            cerr << "Erro ao abrir o arquivo de carros." << endl;
        }
    }
};

//funções da biblioteca files
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
ofstream file;

int main() {

    int option;

  

    setlocale(LC_ALL, "pt_BR.utf8");
    setup();

    bool state = true;

    while(state){
        system("cls");
        option = showMenu();

        switch (option)
        {
        case 1:
            searchCar();
            break;
        case 2:
            {
                Car newCar;
                cadCar(newCar, false);
                cout << writeCar(newCar) << endl;
                system("pause");
                system("cls");
                //writeCar();
            }
            
            break;
        case 3:
            modifyCar();
            break;
        case 4:
            delCar();
            break;
        case 5:
            listCars();
            break;
        case 6:
            state = false;
            break;
        case 7:
            cout << "Escolha uma opção valida" << endl;
            system("Pause");
            system("cls");
            break;
        
        default:
            break;
        }
    }
    cout << "Voce escolheu sair. Ate a proxima!" << endl;
    system("pause");
    return 0;

}

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
