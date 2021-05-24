#include <iostream>
#include <string>
#include <mysql.h>

#include "Ventas.h"

using namespace std;

int main()
{
    string nombre;

    cout << "----------Proyecto Final----------"<<endl;

    Ventas* super = new Ventas();

    cout << "Ingrese nombre ";
    cin >> nombre;

    super->ingresarCliente(nombre);
}

