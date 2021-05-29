#pragma once

#include <string>
#include "conexion.h"

using namespace std;
class Proveedores {
	//atributos
private:
	string nit, direccion, proveedor;
	int telefono = 0;
	//constructor
public:
	Proveedores() {
	}
	Proveedores(string dir, string prov, int tel, string n) {
		nit = n;
		proveedor = prov;
		direccion = dir;
		telefono = tel;
	}



	// metodo


	void crear() {
		int q_estado;
		conexion cn = conexion();
		cn.abrir_conexion();
		if (cn.getConectar()) {
			string t = to_string(telefono);
			string nit, dir, proveedor;
			cin.ignore();
			cout << "Ingrese NIT: " << endl;
			getline(cin, nit);
			cout << "Ingrese Direccion: " << endl;
			getline(cin, dir);
			cout << "Ingrese Proveedor: " << endl;
			getline(cin, proveedor);
			cout << "Ingrese Telefono: " << endl;
			cin >> t;
			cin.ignore();

			string insert = "INSERT INTO proveedores(nit,direccion,proveedor) VALUES ('" + nit + "','" + dir + "','" + proveedor + ", '" + t + "', now())";
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
			string consulta = "select * from proveedores";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				cout << "-----------------------------Proveedores----------------------------" << endl;
				while (fila = mysql_fetch_row(resultado)) {
					cout << fila[0] << " , " << fila[1] << " , " << fila[2] << " , " << fila[3] << " , " << fila[4] << endl;
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
			string id, dir, prove, nit;
			string tel = to_string(telefono);
			cout << "Ingrese el Id del Proveedor que desea Actualizar: " << endl;
			cin >> id;
			cin.ignore();

			cout << "Ingrese Proveedor: " << endl;
			getline(cin, prove);

			cout << "Ingrese Nit: " << endl;
			getline(cin, nit);

			cout << "Ingrese Direccion: " << endl;
			getline(cin, dir);

			cout << "Ingrese Telefono: " << endl;
			cin >> tel;
			cin.ignore();

			string update = "UPDATE proveedores SET proveedor ='" + prove + "', nit ='" + nit + "',direccion ='" + dir + "'telefono = '" + tel + "'  WHERE idCliente = '" + id + "'";
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
			string prov;
			cout << "Ingrese el id del Proveedor que desea eliminar" << endl;
			cin >> prov;
			string eliminar = "Delete from proveedores where proveedor = '" + prov + "' ";
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
