#include <mysql.h>
#include <iostream>
#include <string>
using namespace std;

class Producto
{
private:
    int q_estado;
    MYSQL* conectar;
public:
    void add_connector(MYSQL* _conectar) {
        conectar = _conectar;
    }

    void crear(string marcas) {
        int existencia, id_marca;
        double precio_costo, precio_venta;
        string producto, descripcion, consulta;

        cout << "\nNombre del producto: ";
        getline(cin, producto);

        cout << "\nDescripción: ";
        getline(cin, descripcion);

        cout << "\nPrecio de costo: ";
        cin >> precio_costo;

        cout << "\nPrecio de venta: ";
        cin >> precio_venta;

        cout << "\nExistencia: ";
        cin >> existencia;

        cout << marcas;
        cout << "\nId de la marca: ";
        cin >> id_marca;

        consulta = "INSERT INTO productos(producto, descripcion, precio_costo, precio_venta, existencia, fecha_ingreso, id_marca) VALUES('" + producto + "', '" + descripcion + "', '" + to_string(precio_costo) + "', '" + to_string(precio_venta) + "', '" + to_string(existencia) + "', CURRENT_TIMESTAMP(), '" + to_string(id_marca) + "');";
        const char* i = consulta.c_str();
        q_estado = mysql_query(conectar, i);
        if (!q_estado) {
            cout << "Producto ingresado con éxito" << endl;
            leer();
        }
        else {
            cout << "Error al ingresar producto" << endl;
        }
    }

    void leer() {
        cout << imprimir();
    }

    void actualizar(string marcas) {
        int id_producto, existencia, id_marca;
        double precio_costo, precio_venta;
        string producto, descripcion, consulta;

        leer();

        cout << "\nId del producto: ";
        cin >> id_producto;
        cin.ignore();

        cout << "\nNombre del producto: ";
        getline(cin, producto);

        cout << "\nDescripción: ";
        getline(cin, descripcion);

        cout << "\nPrecio de costo: ";
        cin >> precio_costo;

        cout << "\nPrecio de venta: ";
        cin >> precio_venta;

        cout << "\nExistencia: ";
        cin >> existencia;

        cout << marcas;
        cout << "\nId de la marca: ";
        cin >> id_marca;

        consulta = "UPDATE productos SET producto = '" + producto + "', descripcion = '" + descripcion + "', precio_costo = '" + to_string(precio_costo) + "', precio_venta = '" + to_string(precio_venta) + "', existencia = '" + to_string(existencia) + "', fecha_ingreso = CURRENT_TIMESTAMP(), id_marca = " + to_string(id_marca) + " WHERE id = " + to_string(id_producto);
        const char* i = consulta.c_str();
        q_estado = mysql_query(conectar, i);
        if (!q_estado) {
            cout << "Producto actualizado con éxito" << endl;
            leer();
        }
        else {
            cout << "Error al actualizar producto" << endl;
        }
    }

    void eliminar() {
        int id;
        string consulta;

        leer();

        cout << "\nId del producto: ";
        cin >> id;

        consulta = "DELETE FROM productos WHERE productos.id = " + to_string(id);
        const char* i = consulta.c_str();
        q_estado = mysql_query(conectar, i);
        if (!q_estado) {
            cout << "Producto eliminado con éxito" << endl;
            leer();
        }
        else {
            cout << "Error al eliminar producto" << endl;
        }
    }

    string imprimir() {
        MYSQL_ROW fila;
        MYSQL_RES* resultado;
        string consulta, imprimir;
        consulta = "SELECT * FROM productos LEFT JOIN marcas ON productos.id_marca = marcas.id;";
        const char* i = consulta.c_str();
        q_estado = mysql_query(conectar, i);
        if (!q_estado) {
            resultado = mysql_store_result(conectar);
            imprimir = "\n-------------------------------------------------------------------------------------------------------------\n";
            imprimir += "id\t| producto\t| descripcion\t| precio_venta\t| existencia\t| fecha_ingreso\t| marca\n";
            imprimir += "-------------------------------------------------------------------------------------------------------------\n";
            while (fila = mysql_fetch_row(resultado)) {
                imprimir += fila[0];
                imprimir += "\t| ";
                imprimir += fila[1];
                imprimir += "\t| ";
                imprimir += fila[2];
                imprimir += "\t| ";
                imprimir += fila[4];
                imprimir += "\t| ";
                imprimir += fila[5];
                imprimir += "\t| ";
                imprimir += fila[6];
                imprimir += "\t| ";
                imprimir += fila[7];
                imprimir += "\t| ";
                imprimir += fila[10];
                imprimir += "\n";
                imprimir += "-------------------------------------------------------------------------------------------------------------\n";
            }
        }
        else {
            imprimir = "Error al leer productos\n";
        }
        return imprimir;
    }
};
