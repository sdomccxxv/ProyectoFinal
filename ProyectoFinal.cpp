#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <stdio.h>  
#include <windows.h>
# include <time.h>
#include <mysql.h>

#include "Ventas.h"
#include "empleados.h"
#include "gotoxy.h"
#include "Marcas.h"
#include "Proveedores.h"
#include "Cliente.h"
#include "Puestos.h"

using namespace std;

Ventas* super = new Ventas();
empleados* emp = new empleados();
Marcas* marc = new Marcas();
Proveedores* prov = new Proveedores();
Cliente* clie = new Cliente();
Puestos * pue = new Puestos();
int opcionm;

void lineas(int x, int y, string xx) {
    for (int i = x; i < 118; i++) {
        gotoxy(i, y); cout << xx;
    }
}

void borde() {
    int i;
    for (i = 1; i < 119; i++) {
        gotoxy(i, 0);
        printf("%c", 219);
        gotoxy(i, 30);
        printf("%c", 219);
    }

    for (i = 0; i < 31; i++) {
        gotoxy(0, i);
        printf("%c", 219);
        gotoxy(119, i);
        printf("%c", 219);
    }
}

void ventas();
void menu();
void crud(string tipo, int opcionm);
void mostrarventa();

int main()
{
    system("mode con: cols=120 lines=31");

    menu();
    //ventas();

}

void menu() {
    int opcionm;
    system("cls");
    borde();

    string str = "MENU PRINCIPAL";

    gotoxy(53, 8);
    cout << str;
    gotoxy(51, 10);
    cout << "1. Ingresar.....: " << endl;
    gotoxy(51, 11);
    cout << "2. Mostrar......: " << endl;
    gotoxy(51, 12);
    cout << "3. Modificar....: " << endl;
    gotoxy(51, 13);
    cout << "4. Eliminar.....: " << endl;
    gotoxy(52, 15);
    cout << "Ingrese opcion: " << endl;
    gotoxy(68, 15);
    cin >> opcionm;

    switch (opcionm) {
    case 1: crud("INGRESAR", opcionm); break;
    case 2: crud("MOSTRAR", opcionm); break;
    case 3: crud("MODIFICAR", opcionm); break;
    case 4: crud("ELIMINAR", opcionm); break;
    }
}

void crud(string tipo, int opcionm) {
    system("cls");
    borde();

    int opcion = 0;


    gotoxy(54, 8);
    string str = tipo + " A";

    gotoxy(50, 10);
    cout << "1. Clientes........ " << endl;
    gotoxy(50, 11);
    cout << "2. Empleados....... " << endl;
    gotoxy(50, 12);
    cout << "3. Puestos......... " << endl;
    gotoxy(50, 13);
    cout << "4. Productos....... " << endl;
    gotoxy(50, 14);
    cout << "5. Marcas.......... " << endl;
    gotoxy(50, 15);
    cout << "6. Proveedores..... " << endl;
    gotoxy(50, 16);
    cout << "7. Ventas.......... " << endl;
    gotoxy(50, 17);
    cout << "8. Compras......... " << endl;
    gotoxy(50, 18);
    cout << "9. Menu............ " << endl;
    gotoxy(50, 20);
    cout << "Ingrese opcion..... " << endl;
    gotoxy(70, 20);
    cin >> opcion;

    switch (opcion)
    {
        //Clientes--
    case 1:
        switch (opcionm)
        {
        case 1: system("cls"); clie->crear(); break;
        case 2: system("cls"); clie->leer(); break;
        case 3: system("cls"); clie->actualizar(); break;
        case 4: system("cls"); clie->eliminar(); break;
        default:
            break;
        }
        break;
        //Empleados
    case 2:
        switch (opcionm)
        {
        case 1: system("cls"); emp->crear(); break;
        case 2: system("cls"); emp->leer(); break;
        case 3: system("cls"); emp->actualizar(); break;
        case 4: system("cls"); emp->eliminar(); break;
        default:
            break;
        }
        break;
        //Puestos--
    case 3:
        switch (opcionm)
        {
        case 1: system("cls"); pue->crear(); break;
        case 2: system("cls"); pue->leer(); break;
        case 3: system("cls"); pue->actualizar(); break;
        case 4: system("cls"); pue->eliminar(); break;
        default:
            break;
        }
        break;
        //Productos--
    case 4:
        switch (opcionm)
        {
        case 1: cout << "Ingresar productos"; break;
        case 2: cout << "Mostrar productos"; break;
        case 3: cout << "Modificar productos"; break;
        case 4: cout << "Eliminar productos"; break;
        default:
            break;
        }
        break;
        //Marcas
    case 5:
        switch (opcionm)
        {
        case 1: system("cls"); marc->crear(); break;
        case 2: system("cls"); marc->leer(); break;
        case 3: system("cls"); marc->actualizar(); break;
        case 4: system("cls"); marc->eliminar(); break;
        default:
            break;
        }
        break;
        //Proveedores
    case 6:
        switch (opcionm)
        {
        case 1: system("cls"); prov->crear(); break;
        case 2: system("cls"); prov->leer(); break;
        case 3: system("cls"); prov->actualizar(); break;
        case 4: system("cls"); prov->eliminar(); break;
        default:
            break;
        }
        break;
        //Ventas
    case 7:
        switch (opcionm)
        {
        case 1: ventas(); break;
        case 2: system("cls"); mostrarventa();  break;
        case 3: system("cls"); super->eliminarventa(); break;
        default:
            break;
        }
        break;
        //Compras
    case 8:
        switch (opcionm)
        {
        case 1: cout << "Ingresar Compras"; break;
        case 2: cout << "Mostrar Compras"; break;
        case 3: cout << "Modificar Compras"; break;
        case 4: cout << "Eliminar Compras"; break;
        default:
            break;
        }
        break;
        //Menu principal
    case 9: menu(); break;
    default:
        break;
    }
}

void ventas() {
    string nombre, nit;
    int nofact = 1;

    system("cls");

    gotoxy(5, 3);
    cout << "Fecha: " << super->fecha() << endl;

    super->numerofact();
    //gotoxy(25, 2); cout << "No.: " << nofact;

    gotoxy(36, 3); cout << "Serie: ";

    gotoxy(5, 4); cout << "NIT: ";
    cin >> nit;
    super->buscarcl(nit);
}

void mostrarventa() {

    borde();
    int f;
    gotoxy(5, 4); cout << "Ingrese el numero de factura que desea modificar: ";
    cin >> f;

    super->mostrarventa(f);
}
