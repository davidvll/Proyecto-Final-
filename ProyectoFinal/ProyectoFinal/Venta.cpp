#include <mysql.h>
#include <iostream>
#include <string>
using namespace std;

class Venta
{
private:
    int q_estado;
    int n_factura = 1;
    int id_venta = 1;
    MYSQL* conectar;
public:
    void add_connector(MYSQL* _conectar) {
        conectar = _conectar;
    }

    void crear(string clientes, string empleados, string productos) {
        int id_cliente, id_empleado, id_producto, cantidad;
        char serie = 'A';
        double precio_unitario;
        string fecha_factura, consulta;

        cout << "\nFecha de factura (YYYY-MM-DD): ";
        getline(cin, fecha_factura);

        cout << clientes;
        cout << "\nId del cliente: ";
        cin >> id_cliente;

        cout << empleados;
        cout << "\nId del empleado: ";
        cin >> id_empleado;

        cout << productos;
        cout << "\nId del producto: ";
        cin >> id_producto;

        cout << "\nCantidad: ";
        cin >> cantidad;

        cout << "\nPrecio unitario: ";
        cin >> precio_unitario;

        consulta = "INSERT INTO ventas(no_factura, serie, fecha_factura, fecha_ingreso, id_cliente, id_empleado) VALUES('" + to_string(n_factura) + "', '" + serie + "', '" + fecha_factura + "', CURRENT_TIMESTAMP(), '" + to_string(id_cliente) + "', '" + to_string(id_empleado) + "');";
        const char* i = consulta.c_str();
        q_estado = mysql_query(conectar, i);
        if (!q_estado) {
            consulta = "INSERT INTO ventas_detalle(id_venta, id_producto, cantidad, precio_unitario) VALUES('" + to_string(id_venta) + "', '" + to_string(id_producto) + "', '" + to_string(cantidad) + "', '" + to_string(precio_unitario) + "')";
            const char* i = consulta.c_str();
            q_estado = mysql_query(conectar, i);
            if (!q_estado) {
                cout << "Venta ingresada con éxito" << endl;
                id_venta++;
                n_factura++;
                leer();
            }
            else {
                cout << "Error al ingresar detalle" << endl;
            }
        }
        else {
            cout << "Error al ingresar venta" << endl;
        }
    }

    void leer() {
        cout << imprimir();
    }

    void actualizar(string clientes, string empleados, string productos) {
        int _id_venta, id_cliente, id_empleado, id_producto, cantidad;
        char serie = 'A';
        double precio_unitario;
        string fecha_factura, consulta;

        leer();

        cout << "\nId de la venta: ";
        cin >> _id_venta;
        cin.ignore();

        cout << "\nFecha de factura (YYYY-MM-DD): ";
        getline(cin, fecha_factura);

        cout << clientes;
        cout << "\nId del cliente: ";
        cin >> id_cliente;

        cout << empleados;
        cout << "\nId del empleado: ";
        cin >> id_empleado;

        cout << productos;
        cout << "\nId del producto: ";
        cin >> id_producto;

        cout << "\nCantidad: ";
        cin >> cantidad;

        cout << "\nPrecio unitario: ";
        cin >> precio_unitario;

        consulta = "UPDATE ventas SET fecha_factura = '" + fecha_factura + "', fecha_ingreso = CURRENT_TIMESTAMP(), id_cliente = '" + to_string(id_cliente) + "', id_empleado = '" + to_string(id_empleado) + "' WHERE id = " + to_string(_id_venta);
        const char* i = consulta.c_str();
        q_estado = mysql_query(conectar, i);
        if (!q_estado) {
            consulta = "UPDATE ventas_detalle SET cantidad = '" + to_string(cantidad) + "', precio_unitario = '" + to_string(precio_unitario) + "', id_producto = '" + to_string(id_producto) + "' WHERE id = " + to_string(_id_venta);
            const char* i = consulta.c_str();
            q_estado = mysql_query(conectar, i);
            if (!q_estado) {
                cout << "Venta actualizada con éxito" << endl;
                leer();
            }
            else {
                cout << "Error al actualizar detalle" << endl;
            }
        }
        else {
            cout << "Error al actualizar venta" << endl;
        }
    }

    void eliminar() {
        int id;
        string consulta;

        leer();

        cout << "\nId de la venta: ";
        cin >> id;

        consulta = "DELETE FROM ventas WHERE ventas.id = " + to_string(id);
        const char* i = consulta.c_str();
        q_estado = mysql_query(conectar, i);
        if (!q_estado) {
            cout << "Venta eliminada con éxito" << endl;
            leer();
        }
        else {
            cout << "Error al eliminar venta" << endl;
        }
    }

    string imprimir() {
        MYSQL_ROW fila;
        MYSQL_RES* resultado;
        string consulta, imprimir;
        consulta = "SELECT * FROM ventas RIGHT JOIN ventas_detalle ON  ventas.id = ventas_detalle.id;";
        const char* i = consulta.c_str();
        q_estado = mysql_query(conectar, i);
        if (!q_estado) {
            resultado = mysql_store_result(conectar);
            imprimir = "\n-----------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
            imprimir += "id\t| no_factura\t| serie\t| fecha_factura\t| fecha_ingreso\t| id_cliente\t| id_empleado\t| id_detalle\t| cantidad\t| precio_unitario\t| id_venta\t| id_producto\n";
            imprimir += "-----------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
            while (fila = mysql_fetch_row(resultado)) {
                imprimir += fila[0];
                imprimir += "\t| ";
                imprimir += fila[1];
                imprimir += "\t| ";
                imprimir += fila[2];
                imprimir += "\t| ";
                imprimir += fila[3];
                imprimir += "\t| ";
                imprimir += fila[4];
                imprimir += "\t| ";
                imprimir += fila[5];
                imprimir += "\t| ";
                imprimir += fila[6];
                imprimir += "\t| ";
                imprimir += fila[7];
                imprimir += "\t| ";
                imprimir += fila[8];
                imprimir += "\t| ";
                imprimir += fila[9];
                imprimir += "\t| ";
                imprimir += fila[10];
                imprimir += "\t| ";
                imprimir += fila[11];
                imprimir += "\n";
                imprimir += "-----------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
            }
        }
        else {
            imprimir = "Error al leer venta\n";
        }
        return imprimir;
    }
};
