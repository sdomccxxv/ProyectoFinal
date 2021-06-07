#pragma once

#include "conexion.h"
#include <string>

using namespace std;

class Productos {



private:

	string idproducto, producto, idmarca, descripcion, imagen, precio_costo, precio_venta, existencia, fechaingreso;



public:
	Productos() {

	}

	Productos(string _idproducto, string _producto, string _idmarca, string _descripcion, string _imagen,
		string _precio_costo, string _precio_venta, string _existencia, string _fechaingreso) {

		idproducto = _idproducto;
		producto = _producto;
		idmarca = _idmarca;
		descripcion = _descripcion;
		imagen = _imagen;
		precio_costo = _precio_costo;
		precio_venta = _precio_venta;
		existencia = _existencia;
		fechaingreso = _fechaingreso;

	}


	void crear() {
		int q_estado;
		conexion cn = conexion();
		cn.abrir_conexion();
		if (cn.getConectar()) {

			cout << "Ingrese Producto: " << endl;
			cin.ignore();
			getline(cin, producto);
			cout << "Ingrese idmarca de la tabla marcas: " << endl;
			cin.ignore();
			getline(cin, idmarca);
			cout << "Ingrese descripcion: " << endl;
			cin.ignore();
			getline(cin, descripcion);
			cout << "Ingrese precio costo: " << endl;
			cin.ignore();
			getline(cin, precio_costo);
			cout << "Ingrese precio venta: " << endl;
			cin.ignore();
			getline(cin, precio_venta);
			cout << "Ingrese existencias: " << endl;
			cin.ignore();
			getline(cin, existencia);

			string insert = "INSERT INTO productos(producto,idMarca,descripcion,imagen,precio_costo,precio_venta,existencia,fechaingreso) VALUES('" + producto + "', '" + descripcion + "', '" + precio_costo + "', '" + precio_venta + "', '" + existencia + "', current_time()); ";

				const char* i = insert.c_str();

			q_estado = mysql_query(cn.getConectar(), i);

			if (!q_estado) {
				cout << "Ingreso Exitoso...." << endl;
			}
			else {
				cout << "xxxx Error al Ingresar xxxxx" << endl;
				cout << insert << endl << mysql_error(cn.getConectar()) << endl;
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
			string consulta = "SELECT idProducto, producto, descripcion, precio_costo, precio_venta, existencia,fechaingreso, p.idMarca FROM productos e INNER JOIN marcas p ON e.idMarca = p.idMarca;";

			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);

			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());

				cout << "-----------------------------empleados----------------------------" << endl;
				while (fila = mysql_fetch_row(resultado)) {
					cout << fila[0] << " , " << fila[1] << " , " << fila[2] << " , " << fila[3] << " , " << fila[4] << " , " << fila[5] << " , " << fila[6] << " , " << fila[7] << " , " << fila[8] << endl;
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

			cout << "Ingrese el Id del producto que desea actualizar: " << endl;
			cin.ignore();
			cin >> idproducto;
			cout << "Ingrese producto: " << endl;
			cin.ignore();
			getline(cin, producto);
			cout << "Ingrese idMarca de la tabla marcas: " << endl;
			cin.ignore();
			getline(cin, idmarca);
			cout << "Ingrese descripcion: " << endl;
			cin.ignore();
			getline(cin, descripcion);
			cout << "Ingrese precio costo: " << endl;
			getline(cin, precio_costo);
			cout << "Ingrese precio venta" << endl;
			cin.ignore();
			getline(cin, precio_venta);
			cout << "Ingrese existencia " << endl;
			cin.ignore();
			getline(cin, existencia);
			cout << "Ingrese fecha ingreso: " << endl;
			cin >> fechaingreso;

			string update = "UPDATE productos SET producto = '" + producto + "', idMarca = '" + idmarca + "', descripcion = '" + descripcion + "', precio costo = '" + precio_costo + "', precio venta = '" + precio_venta + "', existencia = " + existencia + ", fechaingreso = '" + fechaingreso + "' WHERE idproducto = '" + idproducto + "'";
			const char* i = update.c_str();

			q_estado = mysql_query(cn.getConectar(), i);

			if (!q_estado) {
				cout << " Registro Actualizado Exitosamente... " << endl;
			}
			else {
				cout << "xxx Error al actualizar el Registro xxx " << endl;
				cout << update << endl << mysql_error(cn.getConectar()) << endl;
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
			cout << "Ingrese el idproducto que desea elimimnar" << endl;
			cin >> idproducto;

			string eliminar = "Delete from productos where idProducto ='" + idproducto + "'";

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



