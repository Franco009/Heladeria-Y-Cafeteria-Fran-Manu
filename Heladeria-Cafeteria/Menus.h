#include <conio.h>
#include <windows.h>
#include "Color.h"
#include <iostream>
#include <cstring>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <clocale>
using namespace std;
int menu1(int op)
{
    if(op<0)
        op=2;
    if(op>2)
        op=0;
    cout<<"Heladeria"<<endl;
    cout<<"----------"<<endl;
    if(op==0)
    {
        std::cout << termcolor::on_white << termcolor::grey <<"Hacer pedido" <<termcolor::reset<< std::endl;
    }
    else
    {
        cout<<"Hacer pedido"<<endl;
    }
    if(op==1)
    {
        std::cout << termcolor::on_white << termcolor::grey <<"Iniciar sesion" <<termcolor::reset<< std::endl;
    }
    else
    {
        cout<<"Iniciar sesion"<<endl;
    }
    cout<<"------"<<endl;
    if(op==2)
    {
        std::cout << termcolor::on_white << termcolor::grey <<"Salir" <<termcolor::reset<< std::endl;
    }
    else
    {
        cout<<"Salir"<<endl;
    }
    return op;
}
int menu2(int op)
{
    if(op<0)
        op=3;
    if(op>3)
        op=0;
    cout<<"¿Que desea pedir?"<<endl;
    cout<<"---------------"<<endl;
    if(op==0)
    {
        std::cout << termcolor::on_white << termcolor::grey <<"Helado" <<termcolor::reset<< std::endl;
    }
    else
    {
        cout<<"Helado"<<endl;
    }
    if(op==1)
    {
        std::cout << termcolor::on_white << termcolor::grey <<"Cafeteria" <<termcolor::reset<< std::endl;
    }
    else
    {
        cout<<"Cafeteria"<<endl;
    }
    cout<<"------"<<endl;
    if(op==2)
    {
        std::cout << termcolor::on_white << termcolor::grey <<"Cancelar" <<termcolor::reset<< std::endl;
    }
    else
    {
        cout<<"Cancelar"<<endl;
    }
    if(op==3)
    {
        std::cout << termcolor::on_white << termcolor::grey <<"Finalizar" <<termcolor::reset<< std::endl;
    }
    else
    {
        cout<<"Finalizar"<<endl;
    }
    return op;
}
int menu3(int op)
{
    if(op<0)
        op=3;
    if(op>3)
        op=0;
    cout<<"Elija una opcion"<<endl;
    cout<<"---------------"<<endl;
    if(op==0)
    {
        std::cout << termcolor::on_white << termcolor::grey <<"Gestion de helado" <<termcolor::reset<< std::endl;
    }
    else
    {
        cout<<"Gestion de helado"<<endl;
    }
    if(op==1)
    {
        std::cout << termcolor::on_white << termcolor::grey <<"Gestion de cafeteria" <<termcolor::reset<< std::endl;
    }
    else
    {
        cout<<"Gestion de cafeteria"<<endl;
    }
        if(op==2)
    {
        std::cout << termcolor::on_white << termcolor::grey <<"Consultas" <<termcolor::reset<< std::endl;
    }
    else
    {
        cout<<"Consultas"<<endl;
    }
    cout<<"------"<<endl;
    if(op==3)
    {
        std::cout << termcolor::on_white << termcolor::grey <<"Finalizar" <<termcolor::reset<< std::endl;
    }
    else
    {
        cout<<"Finalizar"<<endl;
    }
    return op;

}
int menu4(int op)
{
    if(op<0)
        op=7;
    if(op>7)
        op=0;
    cout<<"Elija una opcion"<<endl;
    cout<<"---------------"<<endl;
    if(op==0)
    {
        std::cout << termcolor::on_white << termcolor::grey <<"Añadir producto" <<termcolor::reset<< std::endl;
    }
    else
    {
        cout<<"Añadir producto"<<endl;
    }
    if(op==1)
    {
        std::cout << termcolor::on_white << termcolor::grey <<"Modificar nombre de un producto" <<termcolor::reset<< std::endl;
    }
    else
    {
        cout<<"Modificar nombre de un producto"<<endl;
    }
    if(op==2)
    {
        std::cout << termcolor::on_white << termcolor::grey <<"Modificar precio de un producto" <<termcolor::reset<< std::endl;
    }
    else
    {
        cout<<"Modificar precio de un producto"<<endl;
    }
    if(op==3)
    {
        std::cout << termcolor::on_white << termcolor::grey <<"Aumentar stock de un producto" <<termcolor::reset<< std::endl;
    }
    else
    {
        cout<<"Aumentar stock de un producto"<<endl;
    }
    if(op==4)
    {
        std::cout << termcolor::on_white << termcolor::grey <<"Restar stock de un producto" <<termcolor::reset<< std::endl;
    }
    else
    {
        cout<<"Restar stock de un producto"<<endl;
    }
    if(op==5)
    {
        std::cout << termcolor::on_white << termcolor::grey <<"Listar productos" <<termcolor::reset<< std::endl;
    }
    else
    {
        cout<<"Listar productos"<<endl;
    }

    if(op==6)
    {
        std::cout << termcolor::on_white << termcolor::grey <<"Eliminar un producto" <<termcolor::reset<< std::endl;
    }
    else
    {
        cout<<"Eliminar un producto"<<endl;
    }
    cout<<"---------"<<endl;
    if(op==7)
    {
        std::cout << termcolor::on_white << termcolor::grey <<"Finalizar" <<termcolor::reset<< std::endl;
    }
    else
    {
        cout<<"Finalizar"<<endl;
    }
    return op;

}
int menu5(int op)
{
    if(op<0)
        op=8;
    if(op>8)
        op=0;
    cout<<"Menu envases de helado"<<endl;
    cout<<"---------------"<<endl;
    if(op==0)
    {
        std::cout << termcolor::on_white << termcolor::grey <<"Añadir envase" <<termcolor::reset<< std::endl;
    }
    else
    {
        cout<<"Añadir envase"<<endl;
    }
    if(op==1)
    {
        std::cout << termcolor::on_white << termcolor::grey <<"Modificar nombre" <<termcolor::reset<< std::endl;
    }
    else
    {
        cout<<"Modificar nombre"<<endl;
    }
    if(op==2)
    {
        std::cout << termcolor::on_white << termcolor::grey <<"Modificar precio" <<termcolor::reset<< std::endl;
    }
    else
    {
        cout<<"Modificar precio"<<endl;
    }
    if(op==3)
    {
        std::cout << termcolor::on_white << termcolor::grey <<"Aumentar stock" <<termcolor::reset<< std::endl;
    }
    else
    {
        cout<<"Aumentar stock"<<endl;
    }
    if(op==4)
    {
        std::cout << termcolor::on_white << termcolor::grey <<"Restar stock" <<termcolor::reset<< std::endl;
    }
    else
    {
        cout<<"Restar stock"<<endl;
    }
    if(op==5)
    {
        std::cout << termcolor::on_white << termcolor::grey <<"Listar envases" <<termcolor::reset<< std::endl;
    }
    else
    {
        cout<<"Listar envases"<<endl;
    }
    if(op==6)
    {
        std::cout << termcolor::on_white << termcolor::grey <<"Eliminar envase" <<termcolor::reset<< std::endl;
    }
    else
    {
        cout<<"Eliminar envase"<<endl;
    }
    if(op==7)
    {
        std::cout << termcolor::on_white << termcolor::grey <<"Stock" <<termcolor::reset<< std::endl;
    }
    else
    {
        cout<<"Stock"<<endl;
    }
    cout<<"--------"<<endl;
    if(op==8)
    {
        std::cout << termcolor::on_white << termcolor::grey <<"Finalizar" <<termcolor::reset<< std::endl;
    }
    else
    {
        cout<<"Finalizar"<<endl;
    }


    return op;
}
int menu9(int op)
{
    if(op<0)
        op=6;
    if(op>6)
        op=0;
    cout<<"Menu stock helado"<<endl;
    cout<<"---------------"<<endl;
    if(op==0)
    {
        std::cout << termcolor::on_white << termcolor::grey <<"Añadir stock de helado" <<termcolor::reset<< std::endl;
    }
    else
    {
        cout<<"Añadir stock de helado"<<endl;
    }
    if(op==1)
    {
        std::cout << termcolor::on_white << termcolor::grey <<"Aumentar stock" <<termcolor::reset<< std::endl;
    }
    else
    {
        cout<<"Aumentar stock"<<endl;
    }
    if(op==2)
    {
        std::cout << termcolor::on_white << termcolor::grey <<"Restar stock" <<termcolor::reset<< std::endl;
    }
    else
    {
        cout<<"Restar stock"<<endl;
    }
    if(op==3)
    {
        std::cout << termcolor::on_white << termcolor::grey <<"Modificar nombre y codigo de stock" <<termcolor::reset<< std::endl;
    }
    else
    {
        cout<<"Modificar nombre y codigo de stock"<<endl;
    }
    if(op==4)
    {
        std::cout << termcolor::on_white << termcolor::grey <<"Ver stock" <<termcolor::reset<< std::endl;
    }
    else
    {
        cout<<"Ver stock"<<endl;
    }
    if(op==5)
    {
        std::cout << termcolor::on_white << termcolor::grey <<"Eliminar stock" <<termcolor::reset<< std::endl;
    }
    else
    {
        cout<<"Eliminar stock"<<endl;
    }
    cout<<"--------"<<endl;
    if(op==6)
    {
        std::cout << termcolor::on_white << termcolor::grey <<"Finalizar" <<termcolor::reset<< std::endl;
    }
    else
    {
        cout<<"Finalizar"<<endl;
    }
    return op;
}
int menu10(int op)
{
    if(op<0)
        op=1;
    if(op>1)
        op=0;
    cout<<"¿Desea añadir otro gusto?"<<endl;
    cout<<"---------------"<<endl;
    if(op==0)
    {
        std::cout << termcolor::on_white << termcolor::grey <<"Si" <<termcolor::reset<< std::endl;
    }
    else
    {
        cout<<"Si"<<endl;
    }
    if(op==1)
    {
        std::cout << termcolor::on_white << termcolor::grey <<"No" <<termcolor::reset<< std::endl;
    }
    else
    {
        cout<<"No"<<endl;
    }
    return op;
}
int menu11(int op)
{
    if(op<0)
        op=5;
    if(op>5)
        op=0;
    cout<<"Elija una opciòn"<<endl;
    cout<<"---------------"<<endl;
    if(op==0)
    {
        std::cout << termcolor::on_white << termcolor::grey <<"Consulta de ticket por codigo" <<termcolor::reset<< std::endl;
    }
    else
    {
        cout<<"Consulta de ticket por codigo"<<endl;
    }
    if(op==1)
    {
        std::cout << termcolor::on_white << termcolor::grey <<"Consulta de ticket por rango de fecha" <<termcolor::reset<< std::endl;
    }
    else
    {
        cout<<"Consulta de ticket por rango de fecha"<<endl;
    }
    if(op==2)
    {
        std::cout << termcolor::on_white << termcolor::grey <<"Consulta de ticket por rango de importe" <<termcolor::reset<< std::endl;
    }
    else
    {
        cout<<"Consulta de ticket por rango de importe"<<endl;
    }
        if(op==3)
    {
        std::cout << termcolor::on_white << termcolor::grey <<"Lista de envases de helado con su cantidad de veces pedida" <<termcolor::reset<< std::endl;
    }
    else
    {
        cout<<"Lista de envases de helado con su cantidad de veces pedida"<<endl;
    }
        if(op==4)
    {
        std::cout << termcolor::on_white << termcolor::grey <<"Lista de productos de cafeteria con su cantidad de veces pedida" <<termcolor::reset<< std::endl;
    }
    else
    {
        cout<<"Lista de productos de cafeteria con su cantidad de veces pedida"<<endl;
    }
    cout<<"---------------"<<endl;
    if(op==5)
    {
        std::cout << termcolor::on_white << termcolor::grey <<"Finalizar" <<termcolor::reset<< std::endl;
    }
    else
    {
        cout<<"Finalizar"<<endl;
    }
    return op;
}
int menu12(int op)
{
    if(op<0)
        op=1;
    if(op>1)
        op=0;
    cout<<"Elija una opciòn"<<endl;
    cout<<"---------------"<<endl;
    if(op==0)
    {
        std::cout << termcolor::on_white << termcolor::grey <<"Confirmar compra" <<termcolor::reset<< std::endl;
    }
    else
    {
        cout<<"Confirmar compra"<<endl;
    }
    if(op==1)
    {
        std::cout << termcolor::on_white << termcolor::grey <<"Cancelar compra" <<termcolor::reset<< std::endl;
    }
    else
    {
        cout<<"Cancelar compra"<<endl;
    }
    cout<<"---------------"<<endl;
    return op;
}
