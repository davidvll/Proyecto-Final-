#include <mysql.h>
#include <iostream>
#include <string>
using namespace std;

class Puesto
{
private:
    int q_estado;
    MYSQL* conectar;
public:
    void add_connector(MYSQL* _conectar) {
        conectar = _conectar;
    }

    void crear() {
        string puesto, consulta;
        cout << "\nNombre del puesto: ";
        getline(cin, puesto);
        consulta = "INSERT INTO puestos(puesto) VALUES('" + puesto + "');";
        const char* i = consulta.c_str();
        q_estado = mysql_query(conectar, i);
        if (!q_estado) {
            cout << "Puesto ingresado con éxito" << endl;
            leer();
        }
        else {
            cout << "Error al ingresar puesto" << endl;
        }
    }

    void leer() {
        cout << imprimir();
    }

    void actualizar() {
        int id;
        string puesto, consulta;

        leer();

        cout << "\nId del puesto: ";
        cin >> id;

        cin.ignore();

        cout << "\nNombre del puesto: ";
        getline(cin, puesto);

        consulta = "UPDATE puestos SET puesto = '" + puesto + "' WHERE id = " + to_string(id);
        const char* i = consulta.c_str();
        q_estado = mysql_query(conectar, i);
        if (!q_estado) {
            cout << "Puesto actualizado con éxito" << endl;
            leer();
        }
        else {
            cout << "Error al actualizar puesto" << endl;
        }
    }

    void eliminar() {
        int id;
        string consulta;

        leer();

        cout << "\nId del puesto: ";
        cin >> id;

        consulta = "DELETE FROM puestos WHERE puestos.id = " + to_string(id);
        const char* i = consulta.c_str();
        q_estado = mysql_query(conectar, i);
        if (!q_estado) {
            cout << "Puesto eliminado con éxito" << endl;
            leer();
        }
        else {
            cout << "Error al eliminar puesto" << endl;
        }
    }

    string imprimir() {
        MYSQL_ROW fila;
        MYSQL_RES* resultado;
        string consulta, imprimir;
        consulta = "SELECT * FROM proyecto_final.puestos;";
        const char* i = consulta.c_str();
        q_estado = mysql_query(conectar, i);
        if (!q_estado) {
            resultado = mysql_store_result(conectar);
            imprimir = "\n--------------------------\n";
            imprimir += "id\t| puesto\n";
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
            imprimir = "Error al leer puestos\n";
        }
        return imprimir;
    }
};
