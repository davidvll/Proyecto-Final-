#include <mysql.h>
#include <iostream>
#include <string>
using namespace std;

class Marca
{
private:
    int q_estado;
    MYSQL* conectar;
public:
    void add_connector(MYSQL* _conectar) {
        conectar = _conectar;
    }

    void crear() {
        string marca, consulta;
        cout << "\nNombre de la marca: ";
        getline(cin, marca);
        consulta = "INSERT INTO marcas(marca) VALUES('" + marca + "');";
        const char* i = consulta.c_str();
        q_estado = mysql_query(conectar, i);
        if (!q_estado) {
            cout << "Marca ingresada con éxito" << endl;
            leer();
        }
        else {
            cout << "Error al ingresar marca" << endl;
        }
    }

    void leer() {
        cout << imprimir();
    }

    void actualizar() {
        int id;
        string marca, consulta;

        leer();

        cout << "\nId de la marca: ";
        cin >> id;

        cin.ignore();

        cout << "\nNombre de la marca: ";
        getline(cin, marca);

        consulta = "UPDATE marcas SET marca = '" + marca + "' WHERE id = " + to_string(id);
        const char* i = consulta.c_str();
        q_estado = mysql_query(conectar, i);
        if (!q_estado) {
            cout << "Marca actualizada con éxito" << endl;
            leer();
        }
        else {
            cout << "Error al actualizar marca" << endl;
        }
    }

    void eliminar() {
        int id;
        string consulta;

        leer();

        cout << "\nId de la marca: ";
        cin >> id;

        consulta = "DELETE FROM marcas WHERE marcas.id = " + to_string(id);
        const char* i = consulta.c_str();
        q_estado = mysql_query(conectar, i);
        if (!q_estado) {
            cout << "Marca eliminada con éxito" << endl;
            leer();
        }
        else {
            cout << "Error al eliminar marca" << endl;
        }
    }

    string imprimir() {
        MYSQL_ROW fila;
        MYSQL_RES* resultado;
        string consulta, imprimir;
        consulta = "SELECT * FROM proyecto_final.marcas;";
        const char* i = consulta.c_str();
        q_estado = mysql_query(conectar, i);
        if (!q_estado) {
            resultado = mysql_store_result(conectar);
            imprimir = "\n--------------------------\n";
            imprimir += "id\t| marca\n";
            imprimir += "--------------------------\n";
            while (fila = mysql_fetch_row(resultado)) {
                imprimir += fila[0];
                imprimir += "\t| ";
                imprimir += fila[1];
                imprimir += "\n";
                imprimir += "--------------------------\n";
            }
        }
        else {
            imprimir = "Error al leer marcas\n";
        }
        return imprimir;
    }
};
