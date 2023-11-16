#include "main.h"
using namespace std;
#include "methods.h"

//ios::app para adicionar conteúdo


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
    system("pause");
    return 0;

}

