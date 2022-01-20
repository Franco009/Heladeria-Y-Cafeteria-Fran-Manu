#include "Stockhelado.h"
using namespace std;
bool producto::mostrar(int t)
{
    if(estado&&t==tipo)
    {
        cout<<"Nombre: "<<nombre<<endl<<"---------------"<<endl;
        cout<<"Precio: "<<precio<<endl<<"---------------"<<endl;
        cout<<"Stock: "<<stock<<endl<<"---------------"<<endl;
        if(tipo==0)
        {
            cout<<"Stock que utiliza: "<<stockqueusa<<endl<<"---------------"<<endl;
            cout<<"Maximo de gustos: "<<maximogustos<<endl<<"---------------"<<endl;
        }
        cout<<endl;
        return true;
    }
    else
    {
        return false;
    }
}
void producto::guardar()
{
    FILE *p;
    p=fopen("productos.dat","ab");
    if(p==NULL)
    {
        p=fopen("productos.dat","wb");
        if(p==NULL)
        {
            return;
        }
    }
    fwrite(this, sizeof(*this), 1, p);
    fclose(p);
}
void producto::cargar(int t)
{
    cout<<"Ingresar nombre: ";
    gets(nombre);
    /*cin.ignore();
    cin.getline(nombre, 100);*/
    cout<<"Ingresar precio: ";
    cin>>precio;
    while(precio<0)
    {
        cout<<"Ingrese un numero positivo: ";
        cin>>precio;
    }
    codigo=cantidadregistrosproductos();
    cout<<"Ingresar stock: ";
    cin>>stock;
    while(stock<0)
    {
        cout<<"Ingrese un numero positivo: ";
        cin>>stock;
    }
    tipo=t;
    if(tipo==0)
    {
        cout<<"Ingresar stock que usa: ";
        cin>>stockqueusa;
        while(stockqueusa<0)
        {
            cout<<"Ingrese un numero positivo: ";
            cin>>stockqueusa;
        }
        cout<<"Ingresar maximo de gustos: ";
        cin>>maximogustos;
        while(maximogustos<0)
        {
            cout<<"Ingrese un numero positivo: ";
            cin>>maximogustos;
        }
    }
    estado=true;
}
void Aniadirproducto(int t)
{
    producto pro;
    pro.cargar(t);
    pro.guardar();
    cin.ignore();
}

void listar(int t)
{
    FILE *p;
    producto pro;
    int i=0;
    p=fopen("productos.dat","rb");
    if(p==NULL)
    {
        cout<<"No hay productos que mostrar"<<endl;
        system("pause");
        return;
    }
    while(fread(&pro, sizeof(pro), 1, p))
    {
        if(pro.mostrar(t))
            i++;
    }
    if(i==0&&p!=NULL)
        cout<<"No hay productos"<<endl;
    system("pause");
    fclose(p);
}
int seleccionarproducto(int t)
{
    system("cls");
    FILE *p;
    p=fopen("productos.dat","rb");
    if(p==NULL)
    {
        cout<<"No hay producto para listar"<<endl;
        system("pause");
        return -1;
    }
    producto pro;
    int i;
    int    limite=cantidadregistrosproductos()-1;
    while(fread(&pro, sizeof(pro), 1, p))
    {
        if(!pro.getestado())
        {
            limite--;
        }
    }
    if(limite>=0)
    {
        limite=cantidadregistrosproductos()-1;
        int op=0;

        bool    loop=true;
        while(loop)
        {
            op=movimientos(op, &loop);
            if(op<0)
                op=limite;
            if(op>limite)
                op=0;
            i=0;
            fseek(p, 0, 0);
            while(fread(&pro, sizeof(pro), 1, p))
            {
                if(pro.getestado()&&pro.gettipo()==t)
                {
                    if(op==i)
                    {
                        std::cout << termcolor::on_white << termcolor::grey <<pro.getnombre() <<termcolor::reset<< std::endl;
                    }
                    else
                    {
                        cout<<pro.getnombre()<<endl;
                    }
                    i++;
                }
                else
                {
                    if(op==i)
                        op++;
                    i++;
                }
            }
            cout<<"-------------------------"<<endl;
            cout<<"Para confirmar, pulse 'X'"<<endl;
            setCursorPosition(0, 0);
            ShowConsoleCursor(false);
        }

        return op;
    }
    else
    {
        cout<<"No hay productos que mostrar"<<endl;
        system("pause");
        fclose(p);
        return -1;
    }
}
void aumentarstockproducto(int n)
{
    if(n!=-1)
    {
        system("cls");
        ShowConsoleCursor(true);
        FILE *p;
        producto pro;
        int stock;
        p=fopen("productos.dat","rb+");
        if(n==-1)
        {
            return;
        }
        fseek(p,sizeof(pro)*n, 0);
        fread(&pro, sizeof(pro), 1, p);
        fseek(p,-sizeof(pro), 1);
        cout<<"Ingresar stock a aumentar: ";
        cin>>stock;
        while(stock<0)
        {
            cout<<"Ingrese un numero positivo: ";
            cin>>stock;
        }
        pro.setstock(stock+pro.getstock());
        fwrite(&pro, sizeof(pro), 1, p);
        fclose(p);
        cin.ignore();
    }
}
void restarstockproducto(int n)
{
    if(n!=-1)
    {
        system("cls");
        ShowConsoleCursor(true);
        FILE *p;
        producto pro;
        int stock;
        p=fopen("productos.dat","rb+");
        if(n==-1)
        {
            return;
        }
        fseek(p,sizeof(pro)*n, 0);
        fread(&pro, sizeof(pro), 1, p);
        fseek(p,-sizeof(pro), 1);
        if(pro.getstock()>0)
        {
            cout<<"Ingresar stock a restar (numero entero): ";
            cin>>stock;
            while(stock<0)
            {
                cout<<"Ingrese un numero positivo: ";
                cin>>stock;
            }
            while(pro.getstock()<stock)
            {
                cout<<"El numero ingresado supera el stock que hay disponible ("<<pro.getstock()<<")"<<endl;
                cout<<"Ingresar stock a restar: ";
                cin>>stock;
                while(stock<0)
                {
                    cout<<"Ingrese un numero positivo: ";
                    cin>>stock;
                }
            }
            pro.setstock(pro.getstock()-stock);
            fwrite(&pro, sizeof(pro), 1, p);
        }
        else
        {
            cout<<"No queda mas stock, el stock disponible es 0"<<endl;
            system("pause");
        }
        fclose(p);
        // cin.ignore();
    }
}
void modificarnombreproducto(int n)
{
    if(n!=-1)
    {
        system("cls");
        ShowConsoleCursor(true);
        FILE *p;
        producto pro;
        char nombre[100];
        p=fopen("productos.dat","rb+");
        if(p==NULL)
        {
            cout<<"No se ha podido abrir el archivo de productos"<<endl;
            system("pause");
            return;
        }
        fseek(p,sizeof(pro)*n, 1);
        fread(&pro, sizeof(pro), 1, p);
        fseek(p,-sizeof(pro), 1);
        cout<<"Ingresar nuevo nombre: ";
        cin.getline(nombre, 100);
        pro.setnombre(nombre);
        fwrite(&pro, sizeof(pro), 1, p);
        fclose(p);
    }
}
void modificarprecioproducto(int n)
{
    if(n!=-1)
    {
        system("cls");
        ShowConsoleCursor(true);
        FILE *p;
        producto pro;
        float precio;
        p=fopen("productos.dat","rb+");
        if(p==NULL)
        {
            cout<<"No se ha podido abrir el archivo de productos"<<endl;
            system("pause");
            return;
        }
        fseek(p,sizeof(pro)*n, 1);
        fread(&pro, sizeof(pro), 1, p);
        cout<<"Ingresar nuevo precio: ";
        cin>>precio;
        while(precio<0)
        {
            cout<<"Ingrese un numero positivo: ";
            cin>>precio;
        }
        pro.setprecio(precio);
        fseek(p,-sizeof(pro), 1);
        fwrite(&pro, sizeof(pro), 1, p);
        fclose(p);
    }
}
void modificarestadoproducto(int n)
{
    if(n!=-1)
    {
        system("cls");
        ShowConsoleCursor(true);
        FILE *p;
        producto pro;
        p=fopen("productos.dat","rb+");
        if(p==NULL)
        {
            cout<<"No se ha podido abrir el archivo de productos"<<endl;
            system("pause");
            return;
        }
        fseek(p,sizeof(pro)*n, 1);
        fread(&pro, sizeof(pro), 1, p);
        fseek(p,-sizeof(pro), 1);
        pro.setestado(false);
        fwrite(&pro, sizeof(pro), 1, p);
        fclose(p);
    }
}
void MenumanageCafe()
{
    while(true)
    {
        system("cls");
        switch(menu(6))
        {
        case 0:
            system("cls");
            ShowConsoleCursor(true);
            Aniadirproducto(1);
            break;
        case 1:
            system("cls");
            ShowConsoleCursor(true);
            modificarnombreproducto(seleccionarproducto(1));
            break;
        case 2:
            system("cls");
            ShowConsoleCursor(true);
            modificarprecioproducto(seleccionarproducto(1));
            break;
        case 3:
            system("cls");
            ShowConsoleCursor(true);
            aumentarstockproducto(seleccionarproducto(1));
            break;
        case 4:
            system("cls");
            ShowConsoleCursor(true);
            restarstockproducto(seleccionarproducto(1));
            break;
        case 5:
            system("cls");
            ShowConsoleCursor(true);
            listar(1);
            break;
        case 6:
            system("cls");
            ShowConsoleCursor(true);
            modificarestadoproducto(seleccionarproducto(1));
            break;
            break;
        case 7:
            system("cls");
            ShowConsoleCursor(true);
            return;
            break;
        }
    }
}
void MenumanageHelado()
{
    while(true)
    {
        system("cls");
        switch(menu(8))
        {
        case 0:
            system("cls");
            ShowConsoleCursor(true);
            Aniadirproducto(0);
            break;
        case 1:
            system("cls");
            ShowConsoleCursor(true);
            modificarnombreproducto(seleccionarproducto(0));
            break;
        case 2:
            system("cls");
            ShowConsoleCursor(true);
            modificarprecioproducto(seleccionarproducto(0));
            break;
        case 3:
            system("cls");
            ShowConsoleCursor(true);
            aumentarstockproducto(seleccionarproducto(0));
            break;
        case 4:
            system("cls");
            ShowConsoleCursor(true);
            restarstockproducto(seleccionarproducto(0));
            break;
        case 5:
            system("cls");
            ShowConsoleCursor(true);
            listar(0);
            break;
        case 6:
            system("cls");
            ShowConsoleCursor(true);
            modificarestadoproducto(seleccionarproducto(0));
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
