#include "main.h"

#define carsTable "carros.csv"
#define keysFile "keys.csv"
#define order 3

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
                writeCar(key);  
                return true;
            }

            if (children.empty()) {
                cout << "Registro não encontrado para a chave: " << key << endl;
                return false;
            }

            int index = it - keys.begin();
            return children[index]->search(key);
        }

        void writeCar(const string& chave) {
        ifstream carFile(carsTable);
        if (carFile.is_open()) {
            string linha;
            while (getline(carFile, linha)) {
                if (linha.find(chave) != string::npos) {
                    cout << "Informações do Carro:\n" << linha << endl;
                    break;  // A chave é única, então podemos encerrar a busca
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
void cadCar(Car& novoCarro);

//pesquisa
bool verifyKeys(BTreeNode* root, const string& key);

ofstream file;

int main() {

    int option;

  

    setlocale(LC_ALL, "pt_BR.utf8");
    setup();

    bool state = true;

    while(state){
        option = showMenu();

        switch (option)
        {
        case 1:
            searchCar();
            break;
        case 2:
            {
                Car newCar;
                cadCar(newCar);
                cout << writeCar(newCar) << endl;
                system("pause");
                system("cls");
                //writeCar();
            }
            
            break;
        case 3:
            searchCar();
            break;
        case 4:
            searchCar();
            break;
        case 5:
            state = false;
            break;
        case 6:
            cout << "Escolha uma opção válida" << endl;
            system("Pause");
            system("cls");
            break;
        
        default:
            break;
        }
    }
    cout << "Você escolheu sair. Até a próxima!" << endl;
    system("pause");
    return 0;

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
    cout << "Qual ação deseja realizar?" << endl;
    cout << "1 - Consultar" << endl;
    cout << "2 - Cadastrar" << endl;
    cout << "3 - Modificar" << endl;
    cout << "4 - Listar" << endl;
    cout << "5 - Sair" << endl;
    cout << "Digite a opção escolhida: " << '\n';
    try{
        if(cin >> choise){
            return choise;
        }else return 6;
    }catch(const exception& e){
        return 6;
    }
    
}

void searchCar(void){
    string sn;
    cout << "Digite o SN do carro que deseja encontrar" << endl;
    cin >> sn;
    BTreeNode* rootNode = new BTreeNode();
    vector<string> primaryKeys = readKeys();
    rootNode->keys = primaryKeys;
    verifyKeys(rootNode, sn);
}

string writeCar(const Car& carro) {
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


void cadCar(Car& novoCarro) {
    cout << "Digite a marca do carro: ";
    cin >> novoCarro.marca;
    cout << "Digite o modelo do carro: ";
    cin >> novoCarro.modelo;
    cout << "Digite o ano do carro: ";
    cin >> novoCarro.ano;
    if(!checkSize(novoCarro.ano, 999)){
        cout << "Ano inválido. Inicie novamente" << endl;
        system("pause");
        system("cls");
        cadCar(novoCarro);
    }
    cout << "Digite o preço do carro: ";
    cin >> novoCarro.preco;
    cout << "Digite o número de série do carro: ";
    cin >> novoCarro.serialNumber;
    if(!checkSize(novoCarro.serialNumber, 9999)){
        cout << "Número de serie inválido. Inicie novamente" << endl;
        system("pause");
        system("cls");
        cadCar(novoCarro);
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

bool verifyKeys(BTreeNode* root, const string& key) {
    if (!root) {
        cout << "Árvore B vazia." << endl;
        return false;
    }
    
    return root->search(key);
}