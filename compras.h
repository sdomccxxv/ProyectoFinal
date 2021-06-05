#include <string>
# include <time.h>

#include "conexion.h"
#include "gotoxy.h"

class compras
{
public:
	struct compra {
		int norden, idprov, fecha, idprod, cant, idcomp;
		float precio, total;
		string prod, nitprov;
	}comprs[100];

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
	compra registrocompras;

	short f;

	int no_orden() {
		int orden = 0;
		cn.abrir_conexion();

		if (cn.getConectar()) {
			string consulta = "SELECT MAX(no_orden_compra) FROM compras;";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);

			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());

				while (fila = mysql_fetch_row(resultado)) {
					orden = atoi(fila[0]);
					gotoxy(25, 3); 
					cout << "No Orden: " << orden + 1;
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
		return orden;
	}

	void buscarprov(string nitp) {

		char addp;
		cn.abrir_conexion();

		if (cn.getConectar()) {
			string consulta = "SELECT * FROM proveedores WHERE nit = '" + nitp + "'";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);

			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());

				uint64_t rows = mysql_num_rows(resultado);

				if (mysql_num_rows(resultado) > 0) {
					while (fila = mysql_fetch_row(resultado)) {
						gotoxy(35, 4);  
						cout << "Proveedor: " << fila[1] << endl;
						int id = atoi(fila[0]);

						compraenca(id);
					}
				}
				else {
					cout << "El proveedor no se encuentra en la base, desea agregarlo S/N: ";
					cin >> addp;
					if (addp == 'S') {
						cout << "Agregar "; // aqui debe ir la funcion para agregar nuevo proveedor.
					}
					else if (addp == 'N')
					{
						cout << "Por favor vuelva a ingresar el nit del proveedor: ";

						cin >> registrocompras.nitprov;
						buscarprov(registrocompras.nitprov);
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

	void compraenca(int prov) {
		cn.abrir_conexion();

		string pr = to_string(prov);

		if (cn.getConectar()) {
			string ord = to_string(no_orden()+1);

			string insertc = "INSERT INTO compras (no_orden_compra,idproveedor,fecha_orden,fecha_ingreso) VALUES(" + ord + ", " + pr + ", " + fecha() + ", now());";

			const char* i = insertc.c_str();
			q_estado = mysql_query(cn.getConectar(), i);

			if (!q_estado) {
				compradet();
			}
			else {
				cout << "Error al ingresar encabezado de compra" << endl;
				cout << insertc << endl << mysql_error(cn.getConectar()) << endl;
			}
		}
		else {
			cout << "Conexion fallida..." << endl;
			cn.cerrar_conexion();
		}
		cn.cerrar_conexion();
	}

	void compradet() {

		int x = 14, y = 10, prod;
		char SN;
		string prodto, str, canti;
		float acumulador=0;

		gotoxy(10, 8); cout << "ID Producto";
		gotoxy(27, 8); cout << "Producto";
		gotoxy(57, 8); cout << "Cantidad";
		gotoxy(72, 8); cout << "Precio Unitario";
		gotoxy(90, 8); cout << "Precio Total";

		cn.abrir_conexion();

		do {
			gotoxy(x + 1, y);
			cin >> prod; // ID Producto
			prodto = to_string(prod);
			cin.ignore();

			str = "SELECT * FROM productos WHERE idProducto = " + prodto; cout << endl;

			if (cn.getConectar()) {
				const char* c = str.c_str();
				q_estado = mysql_query(cn.getConectar(), c);

				if (!q_estado) {
					resultado = mysql_store_result(cn.getConectar());

					uint64_t rows = mysql_num_rows(resultado);

					if (mysql_num_rows(resultado) > 0) {
						while (fila = mysql_fetch_row(resultado)) {
							registrocompras.precio = stof(fila[6]);
							string price = to_string(registrocompras.precio);

							gotoxy(x + 15, y);
							cout << fila[3] << endl; // Nombre Producto
							gotoxy(x + 47, y);
							cin >> registrocompras.cant; // Cantidad producto
							canti = to_string(registrocompras.cant);
							cin.ignore();

							gotoxy(x + 60, y);
							cout << fila[6] << endl;

							gotoxy(x + 80, y);
							comprs[f].total = registrocompras.cant * registrocompras.precio; // Precio total
							printf("%.2f", comprs[f].total);
							acumulador += comprs[f].total;
							fflush(stdin);

							string str = "INSERT INTO compras_detalle (idcompra,idproducto,cantidad,precio_costo_unitario)VALUES((SELECT MAX(idcompra) FROM compras), " + prodto + ", " + canti + ", " + price + ");";

							const char* i = str.c_str();
							q_estado = mysql_query(cn.getConectar(), i);

							if (!q_estado) {
								//cout << "Ingreso exitoso..." << endl;
							}
							else {
								cout << "Error al ingresar detalle de compra" << endl;
								cout << str << endl << mysql_error(cn.getConectar()) << endl;
								cn.cerrar_conexion();
							}
						}
					}
				}
			}
			else {
				cout << "Conexion fallida..." << endl;
				cn.cerrar_conexion();
			}

			gotoxy(80, 7);
			cout << "Agregar mas? (S/N): ";
			gotoxy(100, 7);
			cin >> SN;
			if (SN == 'N' || SN == 'n') {
				return;
			}
			f++;
			y += 2;
		} while (SN == 'S' || SN == 's');
	}
};

