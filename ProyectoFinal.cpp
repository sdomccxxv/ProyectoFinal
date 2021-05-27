#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <stdio.h>  
#include <windows.h>
# include <time.h>
#include <mysql.h>

#include "Ventas.h"
#include "gotoxy.h"

using namespace std;

Ventas* super = new Ventas();
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
void crud(string tipo);
void mostrarventa();

int main()
{
    system("mode con: cols=120 lines=31");

    menu();
    //ventas();

}

void menu() {
    system("cls");
    borde();

    string str = "MENU PRINCIPAL";

    gotoxy(53, 8);
    cout << str;
    gotoxy(51, 10);
    cout << "1. Ingresar.....: " << endl;
    gotoxy(51, 11);
    cout << "2. Modificar....: " << endl;
    gotoxy(51, 12);
    cout << "3. Eliminar.....: " << endl;
    gotoxy(52, 14);
    cout << "Ingrese opcion: " << endl;
    gotoxy(68, 14);
    cin >> opcionm;

    switch(opcionm) {
        case 1: crud("INGRESAR");
            break;
        case 2: crud("MODIFICAR");
            break;
        case 3: crud("ELIMINAR");
            break;
    }
}

void crud(string tipo) {
    cout << opcionm;
    system("cls");
    borde();

    int opcion;

    string str = tipo + " EN";
    gotoxy(54, 8);
    cout << str;
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

    switch (opcion) {
        case 7: 
            switch (opcionm) {
                case 1: ventas(); break;
                case 2: system("cls"); mostrarventa();  break;
                case 3: system("cls"); super->eliminarventa(); break;
            }
            break;
        case 9: menu();
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
    int f;
    cout << "Ingrese el numero de factura que desea modificar: ";
    cin >> f;

    super->mostrarventa(f);
}
