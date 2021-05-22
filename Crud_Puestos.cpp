// Crud_Puestos.cpp : Este archivo contiene la funciÃ³n "main". La ejecuciÃ³n del programa comienza y termina ahÃ­.
//

#include <mysql.h>
#include <iostream>
#include <locale.h>
#include <string>
using namespace std;

int q_estado;
MYSQL* conectar;
void menu();


void crud_puestos();
void crear_puestos();
void leer_puestos();
void actualizar_puestos();
void eliminar_puestos();



int main()
{
    conectar = mysql_init(0);
    conectar = mysql_real_connect(conectar, "localhost", "root", "42895097", "db_proyectofinal.puestos", 3306, NULL, 0);
    if (conectar) {

        menu();
    }
    else {
        cout << "Error en la conexiÃƒÂ³n..." << endl;
    }
    system("pause");
    return 0;
}

void menu() {
    int opcion;

    while (true) {

        cout << "----------->> Menu <<---------Âº" << endl;
        cout << "           1. Puestos" << endl;
        cout << "           2.Salir\n" << endl;

        cout << "Ingrese una opciÃƒÂ³n: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            crud_puestos();
            break;
        case 2:
            exit(1);
        default:
            cout << "\nLa opciÃƒÂ³n ingresada es incorrecta\n" << endl;
            break;
        }

        cout << "_________________________________________\n" << endl;

    }
}

void crud_puestos() {
    int opcion;
    bool bandera = true;

    while (bandera) {

        cout << "\n   Puestos " << endl;
        cout << "    1.Crear" << endl;
        cout << "    2.Leer" << endl;
        cout << "    3.Actualizar" << endl;
        cout << "    4.Eliminar" << endl;
        cout << "    5.Regresar\n" << endl;

        cout << "Ingrese una opciÃƒÂ³n: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            cin.ignore();
            crear_puestos();
            break;
        case 2:
            leer_puestos();
            break;
        case 3:
            actualizar_puestos();
            break;
        case 4:
            eliminar_puestos();
            break;
        case 5:
            bandera = false;
            break;
        default:
            cout << "\nLa opciÃƒÂ³n ingresada es erronea \n" << endl;
            break;
        }

        cout << "\n___________________________________" << endl;

    }
}

void crear_puestos() {
    string puesto, consulta;
    cout << "\nNombre del puesto : ";
    getline(cin, puestos);
    consulta = "INSERT INTO puestos(puesto) VALUES('" + puesto + "');";
    const char* i = consulta.c_str();
    q_estado = mysql_query(conectar, i);
    if (!q_estado) {
        cout << "Marca ingresada con ÃƒÂ©xito" << endl;
        leer_puestos();
    }
    else {
        cout << "Error al ingresar el puestos" << endl;
    }
}

void leer_puestos() {
    MYSQL_ROW fila;
    MYSQL_RES* resultado;
    string consulta;



    consulta = "SELECT * FROM parcial.marcas;";
    
    
    
    const char* i = consulta.c_str();
    q_estado = mysql_query(conectar, i);
    if (!q_estado) {
        resultado = mysql_store_result(conectar);
        cout << "\n--------------------------" << endl;
        cout << "id\t| marca" << endl;
        cout << "--------------------------" << endl;
        while (fila = mysql_fetch_row(resultado)) {
            cout << fila[0] << "\t| " << fila[1] << endl;
            cout << "--------------------------" << endl;
        }
    }
    else {
        cout << "Error al leer el puesto" << endl;
    }
}

void actualizar_puestos() {
    int id;
    string puesto, consulta;

    leer_puestos();

    cout << "\nId del puesto: ";
    cin >> id;

    cin.ignore();

    cout << "\nNombre del puesto: ";
    getline(cin, marca);

    consulta = "UPDATE puestos SET puesto = '" + puesto + "' WHERE id = " + to_string(id);
    const char* i = consulta.c_str();
    q_estado = mysql_query(conectar, i);
    if (!q_estado) {
        cout << "Puesto actualizada con ÃƒÂ©xito" << endl;
        leer_Puestos();
    }
    else {
        cout << "Error al actualizar el puesto" << endl;
    }
}

void eliminar_puestos() {
    int id;
    string puesto, consulta;

    leer_puestos();

    cout << "\nId del puesto : ";
    cin >> id;

    consulta = "DELETE FROM puestos WHERE puestos.id = " + to_string(id);
    const char* i = consulta.c_str();
    q_estado = mysql_query(conectar, i);
    if (!q_estado) {
        cout << "Puesto eliminado exitosamente" << endl;
        leer_puestos();
    }
    else {
        cout << "Error al eliminar m" << endl;
    }
}

}
// Ejecutar programa: Ctrl + F5 o menÃº Depurar > Iniciar sin depurar
// Depurar programa: F5 o menÃº Depurar > Iniciar depuraciÃ³n

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de cÃ³digo fuente
//   3. Use la ventana de salida para ver la salida de compilaciÃ³n y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de cÃ³digo, o a Proyecto > Agregar elemento existente para agregar archivos de cÃ³digo existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
