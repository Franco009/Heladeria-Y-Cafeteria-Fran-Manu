#include "Utilidades.h"
void stocks::guardar()
{
    FILE *p;
    p=fopen("stockhelado.dat","ab");
    if(p==NULL)
    {
        p=fopen("stockhelado.dat","wb");
        if(p==NULL)
        {
            return;
        }
    }
    fwrite(this, sizeof(*this), 1, p);
    fclose(p);
}
void stocks::cargar()
{
    bool Codigoutilizado=false;
    int i=0;
    FILE *p;
    p=fopen("stockhelado.dat", "rb");
    stocks sth;
    cout<<"Ingresar nombre: ";
    gets(nombre);
    /*  cin.ignore();
      cin.getline(nombre, 100);*/
      while (strlen(nombre) == 0||nombre[0]==' ' ){
          cout<<" Ingrese un nombre: "<<endl;
          cin>>gets(nombre);
        }

    cout<<"Ingresar stock (kilos): ";
    cin>>stock;
    while(stock<0)
    {
        cout<<"Ingrese un numero positivo: ";
        cin>>stock;
    }
    if(p==NULL)
    {
        Codigoutilizado=true;
        cout<<"Ingresar codigo: ";
        cin>>codigo;
        while(codigo<0)
        {
            cout<<"Ingrese un numero positivo: ";
            cin>>codigo;
        }
    }
    while(!Codigoutilizado)
    {
        i=0;
        cout<<"Ingresar codigo: ";
        cin>>codigo;
        while(codigo<0)
        {
            cout<<"Ingrese un numero positivo: ";
            cin>>codigo;
        }
        if(codigo>0)
        {
            fseek(p, 0, 0);
            while(fread(&sth, sizeof(sth), 1, p))
            {
                if(codigo==sth.getcodigo())
                {
                    i++;
                }
            }
            if(i==0)
            {
                Codigoutilizado=true;
            }
            else
            {
                cout<<"Ese codigo ya fue utilizado"<<endl;
            }
        }
        else
        {
            cout<<"El codigo debe ser mayor a 0"<<endl;
        }
    }
    estado=true;
    fclose(p);
    cin.ignore();
}
bool stocks::mostrar()
{
    if(estado)
    {
        if(stock<2)
        {
            cout<<termcolor::on_red<<termcolor::grey<<nombre<<" ("<<codigo<<")"<<": "<<stock<<termcolor::reset<<endl<<"--------------"<<endl;
        }
        if(stock==2)
        {
            cout<<termcolor::on_yellow<<termcolor::grey<<nombre<<" ("<<codigo<<")"<<": "<<stock<<termcolor::reset<<endl<<"--------------"<<endl;
        }
        if(stock>2)
        {
            cout<<termcolor::on_green<<termcolor::grey<<nombre<<" ("<<codigo<<")"<<": "<<stock<<termcolor::reset<<endl<<"--------------"<<endl;
        }
        return true;
    }
    else
    {
        return false;
    }
}
void aniadirstockhelado()
{
    stocks sth;
    sth.cargar();
    sth.guardar();
}
int seleccionarstockhelado()
{
    system("cls");
    FILE *p;
    p=fopen("stockhelado.dat","rb");
    if(p==NULL)
    {
        cout<<"No hay stock que modificar"<<endl;
        system("pause");
        return -1;
    }
    stocks sth;
    int limite=cantidadregistrostocks()-1;
    int op=0;
    int i;
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
        cout<<"Seleccionar helado"<<endl;
        cout<<"-----------------------"<<endl;
        while(fread(&sth, sizeof(sth), 1, p))
        {
            if(sth.getestado()==true)
            {
                if(op==i)
                {
                    std::cout << termcolor::on_white << termcolor::grey <<sth.getnombre() <<termcolor::reset<< std::endl;
                }
                else
                {
                    cout<<sth.getnombre()<<endl;
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
    fclose(p);
    return op;
}

void aumentarstockhelado(int n)
{
    if(n!=-1)
    {
        system("cls");
        ShowConsoleCursor(true);
        FILE *p;
        stocks sth;
        int stock;
        p=fopen("stockhelado.dat","rb+");
        if(n==-1)
        {
            return;
        }
        fseek(p,sizeof(sth)*n, 0);
        fread(&sth, sizeof(sth), 1, p);
        fseek(p,-sizeof(sth), 1);
        cout<<"Ingresar stock a aumentar: ";
        cin>>stock;
        while(stock<0)
        {
            cout<<"Ingrese un numero positivo: ";
            cin>>stock;
        }
        sth.setstock(stock+sth.getstock());
        fwrite(&sth, sizeof(sth), 1, p);
        fclose(p);
        cin.ignore();
    }

}
void restarstockhelado(int n)
{
    if(n!=-1)
    {
        // cin.ignore();

        system("cls");
        ShowConsoleCursor(true);
        FILE *p;
        stocks sth;
        float stock;
        p=fopen("stockhelado.dat","rb+");
        if(n==-1)
        {
            return;
        }
        fseek(p,sizeof(sth)*n, 0);
        fread(&sth, sizeof(sth), 1, p);
        fseek(p,-sizeof(sth), 1);

        cout<<"Ingresar stock a restar: ";
        cin>>stock;
        while(stock<0)
        {
            cout<<"Ingrese un numero positivo: ";
            cin>>stock;
        }
        if(sth.getstock()>0)
        {
            while(sth.getstock()<stock)
            {
                cout<<"El numero ingresado supera el stock que hay disponible ("<<sth.getstock()<<")"<<endl;
                cout<<"Ingresar stock a restar: ";
                cin>>stock;
                while(stock<0)
                {
                    cout<<"Ingrese un numero positivo: ";
                    cin>>stock;
                }
            }
            sth.setstock(sth.getstock()-stock);
            fwrite(&sth, sizeof(sth), 1, p);
        }
        else
        {
            cout<<"No queda mas stock, el stock disponible es 0"<<endl;
            system("pause");
        }
        fclose(p);
    }
}
void modificarnombreycodigostockhelado(int n)
{
    if(n!=-1)
    {
        system("cls");
        ShowConsoleCursor(true);
        FILE *p;
        stocks sth;
        char nombre[100];
        int codigo;
        p=fopen("stockhelado.dat","rb+");
        if(p==NULL)
        {
            cout<<"No se ha podido abrir el archivo de stockhelado"<<endl;
            system("pause");
            return;
        }
        fseek(p,sizeof(sth)*n, 0);
        fread(&sth, sizeof(sth), 1, p);
        fseek(p,-sizeof(sth), 1);
        cout<<"Ingresar nuevo nombre: ";
        cin.getline(nombre, 100);
        while (strlen(nombre) == 0||nombre[0]==' ' ){
          cout<<" Ingrese un nombre: "<<endl;
          cin>>gets(nombre);
        }

        cout<<"Ingresar nuevo codigo: ";
        cin>>codigo;
        while(codigo<0)
        {
            cout<<"Ingrese un numero positivo: ";
            cin>>codigo;
        }
        sth.setnombre(nombre);
        sth.setcodigo(codigo);
        fwrite(&sth, sizeof(sth), 1, p);
        fclose(p);
    }
}
void listarstockhelado()
{
    FILE *p;
    stocks sth;
    int i=0;
    p=fopen("stockhelado.dat","rb");
    if(p==NULL)
    {
        system("cls");
        cout<<"No hay stock que mostrar"<<endl;
        system("pause");
        return;
    }

    system("cls");
    while(fread(&sth, sizeof(sth), 1, p))
    {
        if(sth.mostrar())
            i++;
    }
    if(i==0)
        cout<<"No hay stocks"<<endl;
    system("pause");
    fclose(p);
}
void modificarestadostockhelado(int n)
{
    if(n!=-1)
    {
        system("cls");
        ShowConsoleCursor(true);
        FILE *p;
        stocks sth;
        p=fopen("stockhelado.dat","rb+");
        if(n==-1)
        {
            return;
        }
        fseek(p,sizeof(sth)*n, 0);
        fread(&sth, sizeof(sth), 1, p);
        fseek(p,-sizeof(sth), 1);
        sth.setestado(false);
        fwrite(&sth, sizeof(sth), 1, p);
        fclose(p);
    }
}
void menustockhelado()
{
    while(true)
    {
        system("cls");
        switch(menu(9))
        {
        case 0:
            system("cls");
            ShowConsoleCursor(true);
            aniadirstockhelado();
            break;
        case 1:
            system("cls");
            ShowConsoleCursor(true);
            aumentarstockhelado(seleccionarstockhelado());
            break;
        case 2:
            system("cls");
            ShowConsoleCursor(true);
            restarstockhelado(seleccionarstockhelado());
            break;
        case 3:
            system("cls");
            ShowConsoleCursor(true);
            modificarnombreycodigostockhelado(seleccionarstockhelado());
            break;
        case 4:
            system("cls");
            ShowConsoleCursor(true);
            listarstockhelado();
            break;
        case 5:
            system("cls");
            ShowConsoleCursor(true);
            modificarestadostockhelado(seleccionarstockhelado());
            break;
        case 6:
            return;
            break;
        }
    }
}
