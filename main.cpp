#include "main.h"

#define carsTable "carros.csv"
#define keys "keys.csv"

using namespace std;

//ios::app para adicionar conteúdo


class Carro {
public:
    string marca;
    string modelo;
    int ano;
    double preco;
    string numeroSerie;
};


//funções da biblioteca files
void setup(void);
void createFile(string fileName);
bool fileExist(string path);

//funções da biblioteca interface
int showMenu(void);
int searchCar(void);
string writeCar(const Carro carro, int index);


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
            //writeCar();
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
    cin >> choise;
    return choise;
}

int searchCar(void){

}

string writeCar(const Carro carro, int index){
    try{
        fstream file(carsTable, ios::in | ios::out | ios::binary);
        
        if(!file.is_open()){
             throw runtime_error("Falha ao abrir o arquivo. Reinciar sistema!");
        }

        size_t sizeRegister = sizeof(Carro) * index;
        file.seekp(sizeRegister);
        file.write(reinterpret_cast<const char*>(&carro), sizeof(Carro));
        file.close();
        return "Carro adicionado com sucesso!";
    }catch(const exception& e){
        return "Erro ao inserir carro." + string(e.what());
    }
}