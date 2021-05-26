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


void lineas() {
    for (int i = 0; i < 50; i++) {
        gotoxy(i, 4); cout << "*";
    }
}

void ventas();

int main()
{
    ventas();

}

void ventas() {


    string nombre, nit;

    Ventas* super = new Ventas();

    gotoxy(5, 2);
    cout << "Fecha: " << super->fecha() << endl;

    gotoxy(5, 5); cout << "NIT: ";
    cin >> nit;
    super->buscarcl(nit);

    

}
