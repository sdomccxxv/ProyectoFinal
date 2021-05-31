#pragma once

#include <string>
#include "conexion.h"

using namespace std;
class Puestos {
	//atributos
private:
	string puesto;

	//constructor
public:
	Puestos() {
	}
	Puestos(string _puesto) {
		puesto = _puesto;
	}



	// metodo


	void crear() {
		int q_estado;
		conexion cn = conexion();
		cn.abrir_conexion();
		if (cn.getConectar()) {
			string puesto;
			cout << "Ingrese puesto: " << endl;
			cin >> puesto;
			string insert = "INSERT INTO puestos (puesto) VALUES ('" + puesto + "')";
			const char* i = insert.c_str();
			q_estado = mysql_query(cn.getConectar(), i);
			if (!q_estado) {
				cout << "Ingreso Exitoso...." << endl;
			}
			else {
				cout << "---- Error al Ingresar ----" << endl;
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
			string consulta = "select * from puestos";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				cout << "-----------------------------Puestos----------------------------" << endl;
				while (fila = mysql_fetch_row(resultado)) {
					cout << fila[0] << " , " << fila[1] << endl;
				}
			}
			else {
				cout << "---- Error al Consultar ----" << endl;
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
			string  puesto;

			cout << "Ingrese Puesto que desea actualizar : " << endl;
			cin >> puesto;

			string update = "UPDATE puestos SET puesto = '" + puesto + "' WHERE puesto = " + puesto + ";";
			const char* i = update.c_str();
			q_estado = mysql_query(cn.getConectar(), i);
			if (!q_estado) {
				cout << " Registro Actualizado Exitosamente... " << endl;
			}
			else {
				cout << "---- Error al actualizar el Registro ---- " << endl;
			}

		}
		else {
			cout << "Error en la conexion... " << endl;
		}
		cn.cerrar_conexion();
	}

	void eliminar() {
		conexion cn = conexion();
		cn.abrir_conexion();
		if (cn.getConectar()) {
			int q_estado;
			string puest;
			cout << "Ingrese el nombre que desea eliminar" << endl;
			cin >> puest;
			string eliminar = "Delete from puestos where puesto = '" + puest + "' ";
			const char* i = eliminar.c_str();
			q_estado = mysql_query(cn.getConectar(), i);
			if (!q_estado) {
				cout << " Registro Eliminado Exitosamente... " << endl;
			}
			else {
				cout << "---- Error al eliminar el Registro ---- " << endl;
			}

		}
		else {
			cout << "Error en la conexion... " << endl;
		}
		cn.cerrar_conexion();
	}

};