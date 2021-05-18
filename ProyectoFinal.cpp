#include <iostream>
#include <string>
#include <mysql.h>

#include "Supermarket.h"

using namespace std;

int main()
{
    string nombre;

    cout << "----------Proyecto Final----------"<<endl;

    Supermarket* super = new Supermarket();

    cout << "Ingrese nombre ";
    cin >> nombre;

    super->ingresarCliente(nombre);
}

