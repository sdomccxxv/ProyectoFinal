#pragma once

#include <string>
# include <time.h>

#include "conexion.h"
#include "gotoxy.h"

using namespace std;

class Ventas
{
protected: int nofact, idcl, idemp, idpr;
		 string serie, fechafact;

public:

	/*Ventas() {

	}
	Ventas(int nf, string ser, string ffact, int idc, int ide) {
		nofact = nf;
		serie = ser;
		fechafact = ffact;
		idcl = idc;
		idemp = ide;
	}*/

	struct registroVentas {
		float cantidad;
		float precio;
		float total;
		float totalPagar;
	}factura[100];

	string fecha() {
		time_t now = time(0);
		tm time;
		char buf[80];
		time = *localtime(&now);

		strftime(buf, sizeof(buf), "%Y-%m-%d", &time);
		return buf;
	}

	conexion cn = conexion();
	int q_estado;
	MYSQL_ROW fila;
	MYSQL_RES* resultado;

	short z, x = 14, y = 12, f, cantcompra;
	
	void buscarcl(string nit) {
		
		char addnit;

		cn.abrir_conexion();

		if (cn.getConectar()) {
			string consulta = "SELECT * FROM clientes WHERE nit = '" + nit + "'";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);

			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				
				unsigned int rows = mysql_num_rows(resultado);

				if (mysql_num_rows(resultado) > 0) {
					while (fila = mysql_fetch_row(resultado)) {
						gotoxy(25, 5);  cout << "Nombre: " << fila[1] << " " << fila[2] << endl;
						int id = atoi(fila[0]);
						int id_empl;

						gotoxy(65, 5); cout << "Ingrese su ID de empleado: ";
						cin >> id_empl;

						ingresarventa(id, id_empl);
					}
				}
				else {
					cout << "El NIT del cliente no se encuentra en la base, desea agregarlo S/N: ";
					cin >> addnit;
					if (addnit == 'S') {
						cout << "Agregar "; // aqui debe ir la funcion para agregar nuevo cliente.
					}
					else if(addnit == 'N')
					{
						string nit;
						cout << "Por favor vuelva a ingresar el nit: ";
						
						cin >> nit;
						buscarcl(nit);
					}
				}
			}
			else {
				cout << "Error al consultar..." << endl;
				cout << consulta << endl << mysql_error(cn.getConectar()) << endl;
			}
		}
		else {
			cout << "Conexion fallida..." << endl;
		}
	}

	void ingresarventa(int id_c, int id_e) {
		cn.abrir_conexion();

		if (cn.getConectar()) {
			string nf = to_string(nofact);
			string idcl1 = to_string(id_c);
			string idem = to_string(id_e);

			/*START TRANSACTION;
			INSERT INTO ventas(nofactura, serie, fechafactura, idcliente, idempleado, fechaingreso) VALUES(1, 'A', '2021-05-25', 2, 7, now());
			INSERT INTO ventasdetalle(idventa, idProducto, cantidad, precio_unitario) VALUES (LAST_INSERT_ID(), 1, 1, 20);
			COMMIT;*/

			facturar();

			string insertv = "START TRANSACTION; INSERT INTO ventas(nofactura, serie, fechafactura, idcliente, idempleado, fechaingreso) VALUES (" + nf + ", 'A', '" + fecha() + "', " + idcl1 + ", " + idem + ", now()); ";
			


		}
	}

	void facturar() {
		x = 14;
		y = 10;

		registroVentas registro;

		int cant;
		float acumulador = 0;
		int prod;
		char SN;
		string str, prodto;

		gotoxy(10, 8); cout << "ID Producto ";
		gotoxy(27, 8); cout << "Producto ";
		gotoxy(57, 8); cout << "Cantidad ";
		gotoxy(72, 8); cout << "Precio ";

		cn.abrir_conexion();

		do {
			gotoxy(x, y);
			cin >> prod;
			prodto = to_string(prod);
			cin.ignore();
			//getline(cin, prodto);

			str = "SELECT * FROM productos WHERE idProducto = " + prodto; cout << endl;
			
			if (cn.getConectar()) {
				const char* c = str.c_str();
				q_estado = mysql_query(cn.getConectar(), c);
				if (!q_estado) {
					resultado = mysql_store_result(cn.getConectar());

					unsigned int rows = mysql_num_rows(resultado);

					if (mysql_num_rows(resultado) > 0) {
						while (fila = mysql_fetch_row(resultado)) {
							int precio = atoi(fila[6]);

							gotoxy(x + 15, y);
							cout << fila[3] << endl;
							gotoxy(x + 47, y);
							scanf("%f", &factura[f].cantidad);
							gotoxy(x + 60, y);
							factura[f].total = factura[f].cantidad * precio;
							printf("%.2f", factura[f].total);
							acumulador += factura[f].total;
						}
					}
				}
			}

			gotoxy(80, 7);
			fflush(stdin);
			factura[f].totalPagar = acumulador;

			gotoxy(80, 7);
			cout << "Agregar mas? (S/N): ";
			gotoxy(100, 7);
			cin >> SN;
			f++;
			cantcompra++;
			y += 2;
		} while (SN == 'S' || SN == 's');

		gotoxy(60, y + 4);
		printf("Total a pagar: %.2f", acumulador);
	}
	
};