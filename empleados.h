#pragma once

#include "conexion.h"
#include <string>

using namespace std;

class empleados {

	//atributos
private:

	string idemple, id_puesto, nombres, apellidos, genero, direccion,
		fecha_ingreso, dpi, fecha_nacimiento, fecha_iniciolabor;

	int telefono = 0;

	//constructor
public:
	empleados() {

	}
	empleados(string _idemple, string _direccion, string nom, string ape,
		string gen, int tel, string fi, string _dpi, string _fecha_nacimiento,
		string _id_puesto, string _fecha_iniciolabor) {

		direccion = _direccion;
		nombres = nom;
		apellidos = ape;
		genero = gen;
		telefono = tel;
		fecha_ingreso = fi;
		dpi = _dpi;
		fecha_nacimiento = _fecha_nacimiento;
		id_puesto = _id_puesto;
		fecha_iniciolabor = _fecha_iniciolabor;
		idemple = _idemple;

	}

	// metodo
	void crear() {
		int q_estado;
		conexion cn = conexion();
		cn.abrir_conexion();
		if (cn.getConectar()) {

			string t = to_string(telefono);

			cout << "Ingrese su Id de empleado " << endl;
			cin >> idemple;
			cout << "Ingrese Nombres: " << endl;
			cin.ignore();
			getline(cin, nombres);
			cout << "Ingrese Apellidos: " << endl;
			cin.ignore();
			getline(cin, apellidos);

			/*cout << "Ingrese su genero mujer = 1 hombre = 0" << endl;
				cin >> genero;*/

			cout << "Ingrese su direccion " << endl;
			getline(cin, direccion);
			cout << "Ingrese Telefono: " << endl;
			cin >> t;
			cin.ignore();
			cout << "Ingrese DPI: " << endl;
			cin.ignore();
			getline(cin, dpi);
			cout << "Ingrese su fecha nacimiento " << endl;
			getline(cin, fecha_nacimiento);
			cout << "Ingrese el ID_puesto de la tabla puesto para poder realizar la incercion: " << endl;
			getline(cin, id_puesto);
			cout << "Ingrese fecha de inicio de labores " << endl;
			getline(cin, fecha_iniciolabor);

			string insert = "INSERT INTO empleados(idEmpleado,nombres,apellidos,direccion,telefono,DPI,genero,fecha_nacimiento,idPuesto,fecha_inicio_labores)VALUES('" + idemple + "', '" + nombres + "', '" + apellidos + "', '" + direccion + "', '" + t + "', '" + dpi + "', '" + genero + "', '" + fecha_nacimiento + "', '" + id_puesto + "', '" + fecha_iniciolabor + "', current_time()); ";

			const char* i = insert.c_str();

			q_estado = mysql_query(cn.getConectar(), i);

			if (!q_estado) {
				cout << "Ingreso Exitoso...." << endl;
			}
			else {
				cout << "xxxx Error al Ingresar xxxxx" << endl;
			}
		}
		else {
			cout << "Error en la Conexion..." << endl;
		}
		cn.cerrar_conexion();
	}

	void leer() {

		int q_estado;
		conexion cn = conexion();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;

		cn.abrir_conexion();

		if (cn.getConectar()) {
			string consulta = "select * from empleados";

			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);

			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());

				cout << "-----------------------------empleados----------------------------" << endl;
				while (fila = mysql_fetch_row(resultado)) {
					cout << fila[0] << " , " << fila[1] << " , " << fila[2] << " , " << fila[3] << " , " << fila[4] << " , " << fila[5] << " , " << fila[6] << " , " << fila[7] <<" , " << fila[8] << " , " << fila[9] << " , " << fila[10] << endl;
				}
			}
			else {
				cout << "xxxx Error al Consultar xxxxx" << endl;
			}
		}
		else {
			cout << "Error en la Conexion..." << endl;
		}
		cn.cerrar_conexion();
	}

	void actualizar() {
		conexion cn = conexion();
		cn.abrir_conexion();

		if (cn.getConectar()) {
			int q_estado;

			cout << "Ingrese el Nombre del Empleado que desea Actualizar: " << endl;
			cin.ignore();
			cin >> nombres;
			cout << "Ingrese Apellido: " << endl;
			getline(cin, apellidos);
			cout << "Ingrese direccion: " << endl;
			cin.ignore();
			getline(cin, direccion);
			cout << "Ingrese DPI: " << endl;
			getline(cin, dpi);
			cout << "Ingrese genero mujer = 1 hombre = 2: " << endl;
			cin >> genero;
			cin.ignore();
			cout << "Ingrese fecha nacimiento: " << endl;
			getline(cin, fecha_nacimiento);
			cout << "Ingrese fecha inicio labores: " << endl;
			getline(cin, fecha_iniciolabor);
			cout << "Ingrese ID puesto : " << endl;
			getline(cin, id_puesto);
			cout << "Ingrese fecha inicio labores : " << endl;
			getline(cin, fecha_iniciolabor);

			string tel = to_string(telefono);

			string update = "UPDATE empleados SET  fecha_nacimiento ='" + fecha_nacimiento + "',fecha_inico_labores ='" + fecha_iniciolabor + "',apellidos ='" + apellidos + "',direccion ='" + direccion + "',telefono = '" + tel + "',DPI ='" + dpi + "',genero ='" + genero + "'  WHERE nombres = '" + nombres + "'";

			const char* i = update.c_str();

			q_estado = mysql_query(cn.getConectar(), i);

			if (!q_estado) {
				cout << " Registro Actualizado Exitosamente... " << endl;
			}
			else {
				cout << "xxx Error al actualizar el Registro xxx " << endl;
			}
		}
		else {
			cout << "Error en la conexion... " << endl;
		}
		cn.cerrar_conexion();
	}

	void eliminar()
	{
		conexion cn = conexion();
		cn.abrir_conexion();

		if (cn.getConectar()) {
			int q_estado;
			cout << "Ingrese el nombre del empleado que desea eliminar" << endl;
			cin >> nombres;

			string eliminar = "Delete from empleados where nombres ='" + nombres + "'";

			const char* i = eliminar.c_str();
			q_estado = mysql_query(cn.getConectar(), i);

			if (!q_estado) {
				cout << " Registro Eliminado Exitosamente... " << endl;
			}
			else {
				cout << "xxx Error al eliminar el Registro xxx " << endl;
			}
		}
		else {
			cout << "Error en la conexion... " << endl;
		}
		cn.cerrar_conexion();
	}


};
