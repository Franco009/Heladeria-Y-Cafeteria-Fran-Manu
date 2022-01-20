#include "Compras.h"
using namespace std;
int main()
{
    while(true)
    {
        system("cls");
        switch(menu(1))
        {
        case 0:
            system("cls");
            ShowConsoleCursor(true);
            if(checkstock())
            {
                Menupedidos();
            }
            else
            {
                cout<<"Faltan ingresar datos para hacer un pedido"<<endl;
                system("pause");
            }
            break;
        case 1:
            system("cls");
            ShowConsoleCursor(true);
            if(login())
                menuusuario();
            break;
        case 2:
            system("cls");
            exit(1);
            break;
        }
    }
    return 0;
}
