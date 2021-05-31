#include <mysql.h>
#include <iostream>
#include <string>
using namespace std;

class Empleado
{
private:
    int q_estado;
    MYSQL* conectar;
public:
    void add_connector(MYSQL* _conectar) {
        conectar = _conectar;
    }

    void crear(string puestos) {
        int id_puesto;
        string nombres, apellidos, direccion, telefono, dpi, fecha_nacimiento, fecha_inicio_labores, consulta;

        cout << "\nNombres: ";
        getline(cin, nombres);

        cout << "\nApellidos: ";
        getline(cin, apellidos);

        cout << "\nDirección: ";
        getline(cin, direccion);

        cout << "\nTeléfono: ";
        getline(cin, telefono);

        cout << "\nDPI: ";
        getline(cin, dpi);

        cout << "\nFecha de nacimiento (YYYY-MM-DD): ";
        getline(cin, fecha_nacimiento);

        cout << "\nFecha inicio de labores (YYYY-MM-DD): ";
        getline(cin, fecha_inicio_labores);

        cout << puestos;
        cout << "\nId del puesto: ";
        cin >> id_puesto;

        consulta = "INSERT INTO empleados(nombres, apellidos, direccion, telefono, dpi, fecha_nacimiento, fecha_inicio_labores, fecha_ingreso, id_puesto) VALUES('" + nombres + "', '" + apellidos + "', '" + direccion + "', '" + telefono + "', '" + dpi + "', '" + fecha_nacimiento + "', '" + fecha_inicio_labores + "', CURRENT_TIMESTAMP(), " + to_string(id_puesto) + ");";
        const char* i = consulta.c_str();
        q_estado = mysql_query(conectar, i);
        if (!q_estado) {
            cout << "Empleado ingresado con éxito" << endl;
            leer();
        }
        else {
            cout << "Error al ingresar empleado" << endl;
        }
    }

    void leer() {
        cout << imprimir();
    }

    void actualizar(string puestos) {
        int id_empleado, id_puesto;
        string nombres, apellidos, direccion, telefono, dpi, fecha_nacimiento, fecha_inicio_labores, consulta;

        leer();

        cout << "\nId del empleado: ";
        cin >> id_empleado;
        cin.ignore();

        cout << "\nNombres: ";
        getline(cin, nombres);

        cout << "\nApellidos: ";
        getline(cin, apellidos);

        cout << "\nDirección: ";
        getline(cin, direccion);

        cout << "\nTeléfono: ";
        getline(cin, telefono);

        cout << "\nDPI: ";
        getline(cin, dpi);

        cout << "\nFecha de nacimiento (YYYY-MM-DD): ";
        getline(cin, fecha_nacimiento);

        cout << "\nFecha inicio de labores (YYYY-MM-DD): ";
        getline(cin, fecha_inicio_labores);

        cout << puestos;
        cout << "\nId del puesto: ";
        cin >> id_puesto;

        consulta = "UPDATE empleados SET nombres = '" + nombres + "', apellidos = '" + apellidos + "', direccion = '" + direccion + "', telefono = '" + telefono + "', dpi = '" + dpi + "', fecha_nacimiento = '" + fecha_nacimiento + "', fecha_inicio_labores = '" + fecha_inicio_labores + "', fecha_ingreso = CURRENT_TIMESTAMP(), id_puesto = "  + to_string(id_puesto) + " WHERE id = " + to_string(id_empleado);
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

        cout << "\nId del empleado: ";
        cin >> id;

        consulta = "DELETE FROM empleados WHERE empleados.id = " + to_string(id);
        const char* i = consulta.c_str();
        q_estado = mysql_query(conectar, i);
        if (!q_estado) {
            cout << "Empleado eliminado con éxito" << endl;
            leer();
        }
        else {
            cout << "Error al eliminar Empleado" << endl;
        }
    }

    string imprimir() {
        MYSQL_ROW fila;
        MYSQL_RES* resultado;
        string consulta, imprimir;
        consulta = "SELECT * FROM empleados LEFT JOIN puestos ON empleados.id_puesto = puestos.id;";
        const char* i = consulta.c_str();
        q_estado = mysql_query(conectar, i);
        if (!q_estado) {
            resultado = mysql_store_result(conectar);
            imprimir = "\n--------------------------------------------------------------------------------------------------------------------------------------------------------\n";
            imprimir += "id\t| nombres\t| apellidos\t| direccion\t| telefono\t| dpi\t| fecha_nacimiento\t| fecha_inicio_labores\t| fecha_ingreso\t| puesto\n";
            imprimir += "--------------------------------------------------------------------------------------------------------------------------------------------------------\n";
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
                imprimir += fila[7];
                imprimir += "\t| ";
                imprimir += fila[8];
                imprimir += "\t| ";
                imprimir += fila[9];
                imprimir += "\t| ";
                imprimir += fila[12];
                imprimir += "\n";
                imprimir += "--------------------------------------------------------------------------------------------------------------------------------------------------------\n";
            }
        }
        else {
            imprimir = "Error al leer empleados\n";
        }
        return imprimir;
    }
};
