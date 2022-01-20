#include "Productos.h"
bool checkstock()
{
    bool check=true;
    FILE *e,*c;
    e=fopen("stockhelado.dat","rb");
    c=fopen("productos.dat","rb");

    if(e==NULL||c==NULL)
        return check=false;
    stocks sth;
    int limitehelados=0;
    while(fread(&sth,sizeof(sth),1,e))
    {
        if(sth.getestado()==true)
            limitehelados++;
    }
    if(limitehelados==0)
        return check=false;
    producto pro;
    int limite0=0, limite1=0;
    while(fread(&pro, sizeof(pro),1,c))
    {
        if(pro.gettipo()==0&&pro.getestado()==true)
            limite0++;
        if(pro.gettipo()==1&&pro.getestado()==true)
            limite1++;
    }
    if(limite0==0||limite1==0)
        return check=false;
    return check=true;
    fclose(e);
    fclose(c);
}
bool mostrarpedido()
{
    float importe;
    float importetotal;
    float vuelto;
    ticketdetalle tid;
    ticketcabecera tic;
    producto pro;
    FILE *p,*b,*e;
    b=fopen("ticketcabecera.dat","rb");
    if(b==NULL)
    {
        cout<<"No se ha podido abrir el archivo ticketcabecera"<<endl;
        system("pause");
        exit(1);
    }
    p=fopen("ticketdetalle.dat","rb");
    if(p==NULL)
    {
        cout<<"No se ha podido abrir el archivo ticketdetalle"<<endl;
        system("pause");
        exit(1);
    }
    e=fopen("productos.dat","rb");
    if(e==NULL)
    {
        cout<<"No se ha podido abrir el archivo productos"<<endl;
        system("pause");
        exit(1);
    }
    int contar=cantidadregistrosticketcabecera()-1;
    system("cls");
    while(fread(&tic,sizeof(tic),1,b))
    {
        if(contar==tic.getnventa())
        {
            cout<<"Numero de venta "<<tic.getnventa()<<endl;
            fseek(p,0,0);
            while(fread(&tid,sizeof(tid),1,p))
            {
                if(tid.getnventa()==tic.getnventa())
                {
                    fseek(e,0,0);
                    while(fread(&pro,sizeof(pro),1,e))
                    {
                        if(tid.getcodigo()==pro.getcodigo()&&tid.getimporte()>0)
                            cout<<pro.getnombre()<<"  $"<<tid.getimporte()<<endl;
                    }
                }
            }
            importetotal=tic.getimporte();
            cout<<"Importe total $"<<tic.getimporte()<<endl<<"---------------"<<endl;
            system("pause");
        }
    }
    fclose(p);
    fclose(b);
    fclose(e);
    ShowConsoleCursor(true);
    while(true)
    {
        system("cls");
        switch(menu(12))
        {
        case 0:
            system("cls");
            ShowConsoleCursor(true);
            cout<<"Ingrese con cuanto va a abonar:  ";
            cin>>importe;
            while(importe<importetotal)
            {
                cout<<"No le alcanza"<<endl;
                cout<<"Ingrese el importe:  "<<endl;
                cin>>importe;
            }
            vuelto=importe-importetotal;
            cout<<"Su vuelto es:  "<<vuelto<<endl;
            cout<<"Gracias por su compra  "<<endl;
            system("pause");
            system("cls");
            return true;
            break;
        case 1:
            system("cls");
            ShowConsoleCursor(true);
            return false;
            break;
        }
    }

}
void restarstocks(ticketcabecera tic)
{
    int cant;
    int nventa=tic.getnventa(), i, j;
    FILE *p,*b,*e;
    p=fopen("productos.dat","rb+");
    b=fopen("stockhelado.dat","rb+");
    e=fopen("ticketdetalle.dat","rb");
    producto pro;
    ticketdetalle tid;
    stocks sth;
    while(fread(&tid, sizeof(tid),1,e))
    {
        if(tid.getnventa()==nventa)
        {
            fseek(p,0,0);
            while(fread(&pro, sizeof(pro),1,p))
            {
                if(pro.getcodigo()==tid.getcodigo())
                {
                    pro.setstock(pro.getstock()-tid.getcantidad());
                    fseek(p, -sizeof(pro),1);
                    fwrite(&pro,sizeof(pro),1,p);
                    fseek(p, sizeof(pro),1);
                    if(pro.gettipo()==0)
                    {
                        ShowConsoleCursor(true);
                        for(j=0; j<tid.getcantidad(); j++)
                        {
                            int op;
                            system("cls");
                            cout<<"Ingrese los gustos de su "<<pro.getnombre()<<" nº "<<j+1<<endl;
                            system("pause");
                            system("cls");
                            if(pro.getmaximogustos()>1)
                            {
                                cout<<"Ingrese de cuantos gustos sera el helado (maximo "<<pro.getmaximogustos()<<"): ";
                                cin>>cant;
                                while(cant<0)
                                {
                                    cout<<"Ingrese un numero positivo: ";
                                    cin>>cant;
                                }
                                while(cant>pro.getmaximogustos()||cant<=0)
                                {
                                    cout<<"La cantidad ingresada no es valida"<<endl;
                                    cout<<"Ingrese de cuantos gustos sera el helado (maximo "<<pro.getmaximogustos()<<"): ";
                                    cin>>cant;
                                    while(cant<0)
                                    {
                                        cout<<"Ingrese un numero positivo: ";
                                        cin>>cant;
                                    }
                                }
                                ShowConsoleCursor(false);
                            }
                            else
                            {
                                cant=1;
                            }
                            for(i=0; i<cant; i++)
                            {
                                op=seleccionarstockhelado();

                                fseek(b,sizeof(sth)*op,0);
                                fread(&sth,sizeof(sth),1,b);
                                fseek(b,-sizeof(sth),1);
                                sth.setstock(sth.getstock()-pro.getstockqueusa()/(float)cant);
                                if(sth.getstock()<0)
                                {
                                    cout<<"No hay suficiente stock de este gusto"<<endl;
                                    i--;
                                    system("pause");
                                }
                                else
                                {
                                    fwrite(&sth,sizeof(sth),1,b);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    fclose(p);
    fclose(b);
}
void ticketcabecera::empezarcabezera()
{
    nventa=cantidadregistrosticketcabecera();
    tiempo= time(NULL);
    importe=0;
    estado=false;
}
ticketcabecera ticketdetalle::cargarproducto(ticketcabecera tic)
{
    tic.setestado(true);
    system("cls");
    ShowConsoleCursor(true);
    FILE *p;
    p=fopen("productos.dat","rb");
    producto pro;
    fseek(p, sizeof(pro)*codigoproducto, 0);
    fread(&pro, sizeof(pro),1, p);
    if(pro.getstock()>0)
    {
        cout<<"Ingresar cantidad: ";
        cin>>cantidad;
        while(cantidad<0)
        {
            cout<<"Ingrese un numero positivo: ";
            cin>>cantidad;
        }
        while(cantidad>pro.getstock())
        {
            system("cls");
            cout<<"No hay suficiente stock, el stock disponible es "<<pro.getstock()<<", por favor ingrese nuevamente: ";
            cin>>cantidad;
            while(cantidad<0)
            {
                cout<<"Ingrese un numero positivo: ";
                cin>>cantidad;
            }
        }
    }
     else
    {
        cout<<"No hay stock de este producto"<<endl;
        system("pause");
        return tic;
    }

        int opcion;
        cout<<"1-EFECTIVO" <<endl;
            cout<<"2-Debito" <<endl;
            cout<<"3-Credito" <<endl;
            cout<<"ingrese la opcion:  "<<endl;
            cin>>opcion;
            while(opcion){
            switch(opcion){
            case 1:   fclose(p);

                importe=pro.getprecio()*cantidad;
                    tic.sumarimporte(importe);

                return tic;
            break;
            case 2:  fclose(p);
                  importe=pro.getprecio()*cantidad;
                  importe=importe*0.75;
                 tic.sumarimporte(importe);

                return tic;
            break;
            case 3:
            fclose(p);

                importe=pro.getprecio()*cantidad;
                  importe=importe*0.55;
                 tic.sumarimporte(importe);

                return tic;
            break;
            default:
             cout<<"ingrese la opcion correcta"<<endl;
             system("pause");
             system("cls");
            break;
            }
               cout<<"1-EFECTIVO" <<endl;
            cout<<"2-Debito" <<endl;
            cout<<"3-Credito" <<endl;
            cout<<"ingrese la opcion:  "<<endl;
            cin>>opcion;
            }



}


void Menupedidos()
{
    ticketcabecera tic;
    tic.empezarcabezera();
    ticketdetalle tid;
    tid.setnventa(tic.getnventa());
    FILE *p;
    p=fopen("ticketdetalle.dat","ab");
    if(p==NULL)
    {
        p=fopen("ticketdetalle.dat","wb");
        if(p==NULL)
        {
            cout<<"Hubo un problema al crear el archivo de ticketdetalle"<<endl;
            system("pause");
            return;
        }
    }
    FILE *e;
    e=fopen("ticketcabecera.dat","ab");
    if(e==NULL)
    {
        e=fopen("ticketcabecera.dat","wb");
        if(e==NULL)
        {
            cout<<"Hubo un problema al crear el archivo de ticketcabecera"<<endl;
            system("pause");
            return;
        }
    }
    while(true)
    {
        system("cls");
        switch(menu(2))
        {
        case 0:
            system("cls");
            ShowConsoleCursor(true);
            tid.setcodigoproducto(seleccionarproducto(0),0);
            tic=tid.cargarproducto(tic);
            fwrite(&tid, sizeof(tid), 1, p);
            break;
        case 1:
            system("cls");
            ShowConsoleCursor(true);
            tid.setcodigoproducto(seleccionarproducto(1),1);
            tic=tid.cargarproducto(tic);
            fwrite(&tid, sizeof(tid), 1, p);
            break;
        case 2:
            fclose(p);
            tic.setestado(false);
            fwrite(&tic,sizeof(tic),1,e);
            fclose(e);
            return;
            break;
        case 3:
            fclose(p);
            if(tic.getimporte()>0)
            {
                fwrite(&tic,sizeof(tic),1,e);
                fseek(e,-sizeof(tic),1);
                if(mostrarpedido())
                {
                    restarstocks(tic);
                }

                else
                {
                    tic.setestado(false);
                    fwrite(&tic,sizeof(tic),1,e);
                }
                fclose(e);
                return;
                break;
            }
            else
            {
                tic.setestado(false);
                fwrite(&tic,sizeof(tic),1,e);
                return;
            }
        }

    }
}
void consultafecha()
{
    FILE *p,*b, *e;
    p=fopen("ticketdetalle.dat","rb");
    if(p==NULL)
    {
        cout<<"No hay tickets que mostrar"<<endl;
        system("pause");
        return;
    }
    b=fopen("ticketcabecera.dat","rb");
    if(b==NULL)
    {
        cout<<"No hay tickets que mostrar"<<endl;
        system("pause");
        return;
    }
    e=fopen("productos.dat","rb");
    if(e==NULL)
    {
        cout<<"No se pudo abrir el archivo de productos"<<endl;
        system("pause");
        return;
    }
    int i=0,dia1,dia2,mes1,mes2,anio1,anio2;
    cout<<"Ingresar desde que fecha desea hacer la consulta (separada entre espacios): ";
    cin>>dia1;
    while(dia1<0)
    {
        cout<<"Ingrese un numero positivo: ";
        cin>>dia1;
    }
    cin>>mes1;
    while(mes1<0)
    {
        cout<<"Ingrese un numero positivo: ";
        cin>>mes1;
    }
    cin>>anio1;
    while(anio1<0)
    {
        cout<<"Ingrese un numero positivo: ";
        cin>>anio1;
    }
    cout<<"Ingresar hasta que fecha desea hacer la consulta (separada entre espacios): ";
    cin>>dia2;
    while(dia2<0)
    {
        cout<<"Ingrese un numero positivo: ";
        cin>>dia2;
    }
    cin>>mes2;
    while(mes2<0)
    {
        cout<<"Ingrese un numero positivo: ";
        cin>>mes2;
    }
    cin>>anio2;
    while(anio2<0)
    {
        cout<<"Ingrese un numero positivo: ";
        cin>>anio2;
    }
    system("cls");
    ticketdetalle tid;
    ticketcabecera tic;
    producto pro;
    time_t tiempo;
    struct tm *tmPtr;
    while(fread(&tic,sizeof(tic),1,b))
    {
        if(tic.getestado())
        {
            tiempo=tic.getfecha();
            tmPtr=localtime(&tiempo);
            if(1900+tmPtr->tm_year>anio1&&1900+tmPtr->tm_year<=anio2)
            {
                i++;
                printf("Fecha \n%d/%d/%d %d:%d:%d", tmPtr->tm_mday, tmPtr->tm_mon+1, 1900+tmPtr->tm_year, tmPtr->tm_hour, tmPtr->tm_min, tmPtr->tm_sec);
                cout<<endl<<"Numero de venta "<<tic.getnventa()<<endl;
                fseek(p,0,0);
                while(fread(&tid,sizeof(tid),1,p))
                {
                    if(tid.getnventa()==tic.getnventa())
                    {
                        fseek(e, 0,0);
                        while(fread(&pro,sizeof(pro),1,e))
                        {
                            if(tid.getcodigo()==pro.getcodigo()&&tid.getimporte()>0)
                                cout<<pro.getnombre()<<"  $"<<tid.getimporte()<<endl;
                        }
                    }
                }
                cout<<"Importe total $"<<tic.getimporte()<<endl<<"---------------"<<endl;
                system("pause");
            }
            else
            {
                if((1900+tmPtr->tm_year==anio1&&tmPtr->tm_mon+1>mes1)&&(1900+tmPtr->tm_year<anio2||(1900+tmPtr->tm_year==anio2&&tmPtr->tm_mon+1<mes2)||(1900+tmPtr->tm_year==anio2&&tmPtr->tm_mon+1==mes2&&tmPtr->tm_mday<=dia2)))
                {
                    i++;
                    printf("Fecha \n%d/%d/%d %d:%d:%d", tmPtr->tm_mday, tmPtr->tm_mon+1, 1900+tmPtr->tm_year, tmPtr->tm_hour, tmPtr->tm_min, tmPtr->tm_sec);
                    cout<<endl<<"Numero de venta "<<tic.getnventa()<<endl;
                    fseek(p,0,0);
                    while(fread(&tid,sizeof(tid),1,p))
                    {
                        if(tid.getnventa()==tic.getnventa())
                        {
                            fseek(e, 0,0);
                            while(fread(&pro,sizeof(pro),1,e))
                            {
                                if(tid.getcodigo()==pro.getcodigo()&&tid.getimporte()>0)
                                    cout<<pro.getnombre()<<"  $"<<tid.getimporte()<<endl;
                            }
                        }
                    }
                    cout<<"Importe total $"<<tic.getimporte()<<endl<<"---------------"<<endl;
                    system("pause");
                }
                else
                {
                    if(1900+tmPtr->tm_year==anio1&&tmPtr->tm_mon+1==mes1&&tmPtr->tm_mday>=dia1&&(1900+tmPtr->tm_year<anio2||(1900+tmPtr->tm_year==anio2&&tmPtr->tm_mon+1<mes2)||(1900+tmPtr->tm_year==anio2&&tmPtr->tm_mon+1==mes2&&tmPtr->tm_mday<=dia2)))
                    {
                        i++;
                        printf("Fecha \n%d/%d/%d %d:%d:%d", tmPtr->tm_mday, tmPtr->tm_mon+1, 1900+tmPtr->tm_year, tmPtr->tm_hour, tmPtr->tm_min, tmPtr->tm_sec);
                        cout<<endl<<"Numero de venta "<<tic.getnventa()<<endl;
                        fseek(p,0,0);
                        while(fread(&tid,sizeof(tid),1,p))
                        {
                            if(tid.getnventa()==tic.getnventa())
                            {
                                fseek(e, 0,0);
                                while(fread(&pro,sizeof(pro),1,e))
                                {
                                    if(tid.getcodigo()==pro.getcodigo()&&tid.getimporte()>0)
                                        cout<<pro.getnombre()<<"  $"<<tid.getimporte()<<endl;
                                }
                            }
                        }
                        cout<<"Importe total $"<<tic.getimporte()<<endl<<"---------------"<<endl;
                        system("pause");
                    }
                }
            }
        }
    }
    if(i==0)
    {
        cout<<"No hay tickets en ese periodo de tiempo"<<endl;
        system("pause");
    }
    fclose(p);
    fclose(b);
    fclose(e);
}
void consultaimporte()
{
    FILE *p,*b,*e;
    p=fopen("ticketdetalle.dat","rb");
    if(p==NULL)
    {
        cout<<"No hay tickets que mostrar"<<endl;
        system("pause");
        return;
    }
    b=fopen("ticketcabecera.dat","rb");
    if(p==NULL)
    {
        cout<<"No hay tickets que mostrar"<<endl;
        system("pause");
        return;
    }
    e=fopen("productos.dat","rb");
    if(e==NULL)
    {
        cout<<"No se pudo abrir el archivo de productos"<<endl;
        system("pause");
        return;
    }
    float importe1, importe2, i=0;
    cout<<"Ingresar desde que cantidad de importe desea hacer la consulta: ";
    cin>>importe1;
    while(importe1<0)
    {
        cout<<"Ingrese un numero positivo: ";
        cin>>importe1;
    }
    cout<<"Ingresar hasta que cantidad de importe desea hacer la consulta: ";
    cin>>importe2;
    while(importe2<0)
    {
        cout<<"Ingrese un numero positivo: ";
        cin>>importe2;
    }
    system("cls");
    ticketdetalle tid;
    ticketcabecera tic;
    producto pro;
    time_t tiempo;
    struct tm *tmPtr;
    while(fread(&tic,sizeof(tic),1,b))
    {
        if(tic.getestado())
        {
            if(importe1<=tic.getimporte()&&importe2>=tic.getimporte())
            {
                tiempo=tic.getfecha();
                tmPtr=localtime(&tiempo);
                i++;
                printf("Fecha \n%d/%d/%d %d:%d:%d", tmPtr->tm_mday, tmPtr->tm_mon+1, 1900+tmPtr->tm_year, tmPtr->tm_hour, tmPtr->tm_min, tmPtr->tm_sec);
                cout<<endl<<"Numero de venta "<<tic.getnventa()<<endl;
                fseek(p,0,0);
                while(fread(&tid,sizeof(tid),1,p))
                {
                    if(tid.getnventa()==tic.getnventa())
                    {
                        fseek(e, 0,0);
                        fseek(e, 0,0);
                        while(fread(&pro,sizeof(pro),1,e))
                        {
                            if(tid.getcodigo()==pro.getcodigo()&&tid.getimporte()>0)
                                cout<<pro.getnombre()<<"  $"<<tid.getimporte()<<endl;
                        }
                    }
                }
                cout<<"Importe total $"<<tic.getimporte()<<endl<<"---------------"<<endl;
                system("pause");
            }
        }
    }
    if(i==0)
    {
        cout<<"No hay tickets dentro de su consulta"<<endl;
        system("pause");
    }
    fclose(p);
    fclose(b);
    fclose(e);
}
void consultacodigo()
{
    FILE *p,*b,*e;
    p=fopen("ticketcabecera.dat","rb");
    if(p==NULL)
    {
        cout<<"No se a podido abrir el archivo de ticketcabecera"<<endl;
        system("pause");
        exit(1);
    }
        b=fopen("ticketdetalle.dat","rb");
    if(b==NULL)
    {
        cout<<"No se a podido abrir el archivo de ticketdetalle"<<endl;
        system("pause");
        return;
    }
            e=fopen("productos.dat","rb");
    if(e==NULL)
    {
        cout<<"No se a podido abrir el archivo de productos"<<endl;
        system("pause");
        return;
    }
    int codigo;
    ticketcabecera tic;
    ticketdetalle tid;
    producto pro;
    time_t tiempo;
    struct tm *tmPtr;
    cout<<"Ingresar codigo: ";
    cin>>codigo;
    while(fread(&tic,sizeof(tic),1,p))
    {
        if(codigo==tic.getnventa()&&tic.getestado()==true)
        {
        tiempo=tic.getfecha();
                tmPtr=localtime(&tiempo);
                printf("Fecha \n%d/%d/%d %d:%d:%d", tmPtr->tm_mday, tmPtr->tm_mon+1, 1900+tmPtr->tm_year, tmPtr->tm_hour, tmPtr->tm_min, tmPtr->tm_sec);
                cout<<endl<<"Numero de venta "<<tic.getnventa()<<endl;
                fseek(b,0,0);
                while(fread(&tid,sizeof(tid),1,b))
                {
                    if(tid.getnventa()==tic.getnventa())
                    {
                        fseek(e, 0,0);
                        while(fread(&pro,sizeof(pro),1,e))
                        {
                            if(tid.getcodigo()==pro.getcodigo()&&tid.getimporte()>0)
                                cout<<pro.getnombre()<<"  $"<<tid.getimporte()<<endl;
                        }
                    }
                }
                cout<<"Importe total $"<<tic.getimporte()<<endl<<"---------------"<<endl;
                system("pause");
        }
    }
fclose(p);
fclose(b);
fclose(e);
}
void consultavecesproducto(int tipo){
FILE *p,*b,*e;
p=fopen("ticketdetalle.dat","rb");
if(p==NULL){
    cout<<"No se ha podido abrir el archivo de ticketdetalle"<<endl;
    system("pause");
    return;
}
b=fopen("productos.dat","rb");
if(b==NULL){
    cout<<"No se ha podido abrir el archivo de productos"<<endl;
    system("pause");
    return;
}
e=fopen("ticketcabecera.dat","rb");
if(e==NULL){
    cout<<"No se ha podido abrir el archivo de ticketcabecera"<<endl;
    system("pause");
    return;
}
int cantidad=0;
ticketdetalle tid;
ticketcabecera tic;
producto pro;
while(fread(&pro,sizeof(pro),1,b)){
    fseek(p,0,0);
    if(tipo==pro.gettipo()){
    while(fread(&tid,sizeof(tid),1,p)){
            fseek(e,sizeof(tic)*tid.getnventa(),0);
    fread(&tic,sizeof(tic),1,e);
        if(pro.getcodigo()==tid.getcodigo()&&tic.getestado()==true&&pro.getestado()==true){
            cantidad+=tid.getimporte()/pro.getprecio();
        }
    }
    if(pro.getestado()){
    cout<<pro.getnombre()<<": "<<cantidad<<endl;
    cantidad=0;
    }
    }
}
system("pause");
fclose(p);
fclose(b);
fclose(e);
}

void menuconsultas()
{
    while(true)
    {
        system("cls");
        switch(menu(11))
        {
        case 0:
            system("cls");
            ShowConsoleCursor(true);
            consultacodigo();
            break;
        case 1:
            system("cls");
            ShowConsoleCursor(true);
            consultafecha();
            break;
        case 2:
            system("cls");
            ShowConsoleCursor(true);
            consultaimporte();
            break;
        case 3:
                        system("cls");
            ShowConsoleCursor(true);
            consultavecesproducto(0);
            break;
        case 4:
            system("cls");
            ShowConsoleCursor(true);
            consultavecesproducto(1);
            break;
        case 5:
            return;
            break;
        }
    }
}

void menuusuario()
{
    while(true)
    {
        system("cls");
        switch(menu(5))
        {
        case 0:
            system("cls");
            ShowConsoleCursor(true);
            MenumanageHelado();
            break;
        case 1:
            system("cls");
            ShowConsoleCursor(true);
            MenumanageCafe();
            break;
                    case 2:
            system("cls");
            ShowConsoleCursor(true);
            menuconsultas();
            break;
        case 3:
            return;
            break;
        }
    }
}

