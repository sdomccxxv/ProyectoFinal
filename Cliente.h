#pragma once
#include <string>
#include "conexion.h"
using namespace std;
class Cliente {
	//atributos
private:
	string nit, nombres, apellidos, genero, correo_electronico, fecha_ingreso;
	int telefono = 0;
	//constructor
public:
	Cliente() {
	}
	Cliente(string nom, string ape, string gen, int tel, string correo, string fi, string n) {
		nit = n;
		nombres = nom;
		apellidos = ape;
		genero = gen;
		correo_electronico = correo;
		telefono = tel;
		fecha_ingreso = fi;
	}
	// metodo
	void crear() {
		int q_estado;
		conexion cn = conexion();
		cn.abrir_conexion();
		if (cn.getConectar()) {
			string t = to_string(telefono);
			string nit, nombres, apellidos, genero, correo_electronico, fecha_ingreso;
			cin.ignore();
			cout << "Ingrese NIT: " << endl;
			getline(cin, nit);
			cout << "Ingrese Nombres: " << endl;
			getline(cin, nombres);
			cout << "Ingrese Apellidos: " << endl;
			getline(cin, apellidos);

			cout << "Ingrese Telefono: " << endl;
			cin >> t;
			cin.ignore();
			cout << "Ingrese Correo Electronico: " << endl;
			getline(cin, correo_electronico);
			cout << "Ingrese Fecha de Ingreso: " << endl;
			getline(cin, fecha_ingreso);


			string insert = "INSERT INTO clientes(nit,nombres,apellidos,genero,correo_electronico,telefono,fecha_ingreso) VALUES ('" + nit + "','" + nombres + "','" + apellidos + "','" + genero + "','" + correo_electronico + "','" + t + "',current_time());";
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
			string consulta = "select * from clientes";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				cout << "-----------------------------Clientes----------------------------" << endl;
				while (fila = mysql_fetch_row(resultado)) {
					cout << fila[0] << " , " << fila[1] << " , " << fila[2] << " , " << fila[3] << " , " << fila[4] << " , " << fila[5] << " , " << fila[6] << " , " << fila[7] << endl;
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
			string id, nom, ape, nit, gen, correo, fi;
			string tel = to_string(telefono);
			cout << "Ingrese el Nombre del Cliente que desea Actualizar: " << endl;
			cin >> id;
			cin.ignore();

			cout << "Ingrese nombres: " << endl;
			getline(cin, nom);

			cout << "Ingrese apellidos: " << endl;
			getline(cin, ape);

			cout << "Ingrese Nit: " << endl;
			getline(cin, nit);

			cout << "Ingrese Telefono: " << endl;
			cin >> tel;
			cin.ignore();

			cout << "Ingrese Correo Electronico: " << endl;
			getline(cin, correo);

			cout << "Ingrese Fecha de Ingreso: " << endl;
			getline(cin, fi);

			string update = "UPDATE clientes SET nombres ='" + nom + "',apellidos ='" + ape + "',nit ='" + nit + "',telefono = '" + tel + "',correo_electronico ='" + correo + "',fecha_ingreso ='" + fi + "'  WHERE idCliente = '" + id + "'";
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
	void eliminar() {
		conexion cn = conexion();
		cn.abrir_conexion();
		if (cn.getConectar()) {
			int q_estado;
			string nom;
			cout << "Ingrese el del cliente que desea eliminar" << endl;
			cin >> nom;
			string eliminar = "Delete from clientes where nombres ='" + nom + "'";
			const char* i = eliminar.c_str();
			q_estado = mysql_query(cn.getConectar(), i);
			if (!q_estado) {
				cout << " Registro Eliminado Exitosamente... " << endl;
			}
			else {
				cout << "--- Error al eliminar el Registro --- " << endl;
			}

		}
		else {
			cout << "Error en la conexion... " << endl;
		}
		cn.cerrar_conexion();
	}

};