#include <mysql.h>
#include <iostream>
#include <string>
using namespace std;

class Cliente
{
private:
    int q_estado;
    MYSQL* conectar;
public:
    void add_connector(MYSQL* _conectar) {
        conectar = _conectar;
    }

    void crear() {
        string nombres, apellidos, nit, telefono, correo_electronico, consulta;

        cout << "\nNombres: ";
        getline(cin, nombres);

        cout << "\nApellidos: ";
        getline(cin, apellidos);

        cout << "\nNIT: ";
        getline(cin, nit);

        cout << "\nTeléfono: ";
        getline(cin, telefono);

        cout << "\nCorreo electrónio: ";
        getline(cin, correo_electronico);

        consulta = "INSERT INTO clientes(nombres, apellidos, nit, telefono, correo_electronico, fecha_ingreso) VALUES('" + nombres + "', '" + apellidos + "', '" + nit + "', '" + telefono + "', '" + correo_electronico + "', CURRENT_TIMESTAMP());";
        const char* i = consulta.c_str();
        q_estado = mysql_query(conectar, i);
        if (!q_estado) {
            cout << "Cliente ingresado con éxito" << endl;
            leer();
        }
        else {
            cout << "Error al ingresar cliente" << endl;
        }
    }

    void leer() {
        cout << imprimir();
    }

    void actualizar() {
        int id;
        string nombres, apellidos, nit, telefono, correo_electronico, consulta;

        leer();

        cout << "\nId del cliente: ";
        cin >> id;
        cin.ignore();

        cout << "\nNombres: ";
        getline(cin, nombres);

        cout << "\nApellidos: ";
        getline(cin, apellidos);

        cout << "\nNIT: ";
        getline(cin, nit);

        cout << "\nTeléfono: ";
        getline(cin, telefono);

        cout << "\nCorreo electrónio: ";
        getline(cin, correo_electronico);

        consulta = "UPDATE clientes SET nombres = '" + nombres + "', apellidos = '" + apellidos + "', nit = '" + nit + "', telefono = '" + telefono + "', correo_electronico = '" + correo_electronico + "', fecha_ingreso = CURRENT_TIMESTAMP() WHERE id = " + to_string(id);
        const char* i = consulta.c_str();
        q_estado = mysql_query(conectar, i);
        if (!q_estado) {
            cout << "Cliente actualizado con éxito" << endl;
            leer();
        }
        else {
            cout << "Error al actualizar cliente" << endl;
        }
    }

    void eliminar() {
        int id;
        string consulta;

        leer();

        cout << "\nId del cliente: ";
        cin >> id;

        consulta = "DELETE FROM clientes WHERE clientes.id = " + to_string(id);
        const char* i = consulta.c_str();
        q_estado = mysql_query(conectar, i);
        if (!q_estado) {
            cout << "Cliente eliminado con éxito" << endl;
            leer();
        }
        else {
            cout << "Error al eliminar cliente" << endl;
        }
    }

    string imprimir() {
        MYSQL_ROW fila;
        MYSQL_RES* resultado;
        string consulta, imprimir;
        consulta = "SELECT * FROM proyecto_final.clientes;";
        const char* i = consulta.c_str();
        q_estado = mysql_query(conectar, i);
        if (!q_estado) {
            resultado = mysql_store_result(conectar);
            imprimir = "\n-------------------------------------------------------------------------------------------------------------\n";
            imprimir += "id\t| nombres\t apellidos\t nit\t telefono\t correo_electronico\t fecha_ingreso\n";
            imprimir += "-------------------------------------------------------------------------------------------------------------\n";
            while (fila = mysql_fetch_row(resultado)) {
                imprimir += fila[0];
                imprimir += "\t| ";
                imprimir += fila[1];
                imprimir += "\t| ";
                imprimir += fila[2];
                imprimir += "\t| ";
                imprimir += fila[3];
                imprimir += "\t| ";
                imprimir += fila[5];
                imprimir += "\t| ";
                imprimir += fila[6];
                imprimir += "\t| ";
                imprimir += fila[7];
                imprimir += "\n";
                imprimir += "-------------------------------------------------------------------------------------------------------------\n";
            }
        }
        else {
            imprimir = "Error al leer clientes\n";
        }
        return imprimir;
    }
};
