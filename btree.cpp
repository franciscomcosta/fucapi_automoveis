#include "btree.h"
 
bool BTreeNode::search(const string& key) {
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

void BTreeNode::modify(const string& key) {

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


void BTreeNode::delCar(const string& key){

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


void BTreeNode::printCar(const string& chave) {
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