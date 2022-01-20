#include "Stockhelado.h"
/*void MenumanageHelado()
{
    while(true)
    {
        system("cls");
        switch(menu(8))
        {
        case 0:
            system("cls");
            ShowConsoleCursor(true);
            Aniadirenvase();
            break;
        case 1:
            system("cls");
            ShowConsoleCursor(true);
            modificarnombrehelado(seleccionarhelado());
            break;
        case 2:
            system("cls");
            ShowConsoleCursor(true);
            modificarpreciohelado(seleccionarhelado());
            break;
                    case 3:
            system("cls");
            ShowConsoleCursor(true);
            aumentarenvasehelado(seleccionarhelado());
            break;
                    case 4:
            system("cls");
            ShowConsoleCursor(true);
            restarenvasehelado(seleccionarhelado());
            break;
        case 5:
            system("cls");
            ShowConsoleCursor(true);
            listarhelados();
            break;
        case 6:
            system("cls");
            ShowConsoleCursor(true);
            modificarestadohelado(seleccionarhelado());
            break;
        case 7:
            system("cls");
            ShowConsoleCursor(true);
            menustockhelado();
            break;
        case 8:
            system("cls");
            ShowConsoleCursor(true);
            return;
            break;
        }
    }

}
ticket MenuHelado(ticket ti)
{
    helado hel;
    FILE *p;
    p=fopen("helados.dat","rb");
    int op=seleccionarhelado();
    while(fread(&hel, sizeof(hel), 1, p)){
        if(op==hel.getcodigo()&&hel.getstock()<=0){
                system("cls");
            cout<<"No hay stock de este producto"<<endl;
            system("pause");
            op=-2;
        }
    }
    ti.setcodigocafe(op);

    return ti;
}
*/
