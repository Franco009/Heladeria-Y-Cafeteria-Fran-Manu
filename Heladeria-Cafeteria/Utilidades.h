#include "Menus.h"

using namespace std;
class producto
{
protected:
    char nombre[100];
    float precio;
    int stock;
    int codigo;
    bool estado;
    int tipo;
    float stockqueusa;
    int maximogustos;
public:
    void guardar();
    void cargar(int t);
    bool mostrar(int t);
    int gettipo()
    {
        return tipo;
    }
    int getstock()
    {
        return stock;
    }
    int getcodigo()
    {
        return codigo;
    }
    float getprecio()
    {
        return precio;
    }
    char *getnombre()
    {
        return nombre;
    }
    void setnombre(const char *n)
    {
        strcpy(nombre, n);
    }
    void setcodigo(int c)
    {
        codigo=c;
    }
    void setstock(int s)
    {
        stock=s;
    }
    void setprecio(float p)
    {
        precio=p;
    }
    void setestado(bool e)
    {
        estado=e;
    }
    bool getestado()
    {
        return estado;
    }
    int getmaximogustos()
    {
        return maximogustos;
    }
    float getstockqueusa()
    {
        return stockqueusa;
    }
};
class stocks
{
protected:
    char nombre[20];
    float stock;
    int codigo;
    bool estado;
public:
    bool mostrar();
    void guardar();
    void cargar();
    float getstock()
    {
        return stock;
    }
    int getcodigo()
    {
        return codigo;
    }
    char *getnombre()
    {
        return nombre;
    }
    bool getestado()
    {
        return estado;
    }
    void setnombre(const char *n)
    {
        strcpy(nombre, n);
    }
    void setcodigo(int c)
    {
        codigo=c;
    }
    void setstock(float s)
    {
        stock=s;
    }
    void setestado(bool e)
    {
        estado=e;
    }
};
int cantidadregistrostocks()
{
    FILE *p;
    p=fopen("stockhelado.dat", "rb");
    if(p==NULL)
    {
        return 0;
    }
    fseek(p, 0, 2);
    int pesofinal=ftell(p);
    int cant=pesofinal/sizeof(stocks);
    fclose(p);
    return cant;
}
class ticketcabecera
{
private:
    int nventa;
    time_t tiempo;
    float importe;
    bool estado;
public:
    int getnventa()
    {
        return nventa;
    }
    bool getestado()
    {
        return estado;
    }
    time_t getfecha()
    {
        return tiempo;
    }
    float getimporte()
    {
        return importe;
    }
    float sumarimporte(float imp)
    {
        importe+=imp;
    }
    void setestado(bool e)
    {
        estado=e;
    }
    void empezarcabezera();
};
class ticketdetalle
{
private:
    int nventa;
    int codigoproducto;
    int cantidad;
    float importe;
public:
    void setnventa(int n)
    {
        nventa=n;
    }
    void setcodigoproducto(int n, int tipo)
    {
        codigoproducto=n;
    }
    void sumarcantidad()
    {
        cantidad++;
    }
    int getnventa()
    {
        return nventa;
    }
    int getcodigo()
    {
        return codigoproducto;
    }
    int getcantidad()
    {
        return cantidad;
    }
    float getimporte()
    {
        return importe;
    }
    void sumarimporte(float n)
    {
        importe+=n;
    }
    ticketcabecera cargarproducto(ticketcabecera tic);
    ticketdetalle()
    {
        cantidad=0;
        importe=0;
    }
};
int cantidadregistrosticketcabecera()
{
    FILE *p;
    p=fopen("ticketcabecera.dat", "rb");
    if(p==NULL)
    {
        return 0;
    }
    fseek(p, 0, 2);
    int pesofinal=ftell(p);
    int cant=pesofinal/sizeof(ticketcabecera);
    fclose(p);
    return cant;
}
int cantidadregistrosticketdetalle()
{
    FILE *p;
    p=fopen("ticketdetalle.dat", "rb");
    if(p==NULL)
    {
        return 0;
    }
    fseek(p, 0, 2);
    int pesofinal=ftell(p);
    int cant=pesofinal/sizeof(ticketdetalle);
    fclose(p);
    return cant;
}
int cantidadregistrosproductos()
{
    FILE *p;
    p=fopen("productos.dat", "rb");
    if(p==NULL)
    {
        return 0;
    }
    fseek(p, 0, 2);
    int pesofinal=ftell(p);
    int cant=pesofinal/sizeof(producto);
    fclose(p);
    return cant;
}
using namespace std;
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirecton dir;
enum eMenu {STOP1 = 0, UP1, DOWN1};
eMenu dir2;
void setCursorPosition(int x, int y)
{
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hOut, coord);
}

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}
int movimientos(int op, bool *loop)
{
    dir2 = STOP1;
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'w':
            dir2 = UP1;
            break;
        case 'W':
            dir2 = UP1;
            break;
        case (char)72:
            dir2 = UP1;
            break;
        case 's':
            dir2 = DOWN1;
            break;
        case 'S':
            dir2 = DOWN1;
            break;
        case (char)80:
            dir2 = DOWN1;
            break;
        case (char)13:
            *loop=false;
            break;
        }
    }
    switch(dir2)
    {
    case UP1:
        op--;
        break;
    case DOWN1:
        op++;
        break;
    }
    return op;
}

int menu(int n)
{
    setlocale(LC_ALL, "spanish");
    int op=0;
    bool    loop=true;
    while(loop)
    {
        op=movimientos(op, &loop);
        if(n==1)
        {
            op= menu1(op);
        }
        if(n==2)
        {
            op=menu2(op);
        }
        if(n==5)
        {
            op=menu3(op);
        }
        if(n==6)
        {
            op=menu4(op);
        }
        if(n==8)
        {
            op=menu5(op);
        }
        if(n==9)
        {
            op=menu9(op);
        }
        if(n==10)
        {
            op=menu10(op);
        }
        if(n==11)
        {
            op=menu11(op);
        }
        if(n==12)
        {
            op=menu12(op);
        }
        cout<<"-------------------------"<<endl;
        cout<<"Para confirmar, pulse ENTER"<<endl;
        setCursorPosition(0, 0);
        ShowConsoleCursor(false);
    }

    return op;
}
bool login()
{
    char usuario[9];
    char contrasenia[9];
    char c[9]= {"Persicco"};
    char u[9]= {"Persicco"};
    cout<<"Ingresar nombre de usuario: ";
    cin>>usuario;
    cout<<"Ingresar contraseña: ";
    cin>>contrasenia;
    cin.ignore();
    if(strcmp(c, contrasenia)==0&&strcmp(u, usuario)==0)
    {
        return true;
    }
    else
    {
        cout<<"Datos erroneos"<<endl;
        system("pause");
        system("cls");
        return false;
    }

}
