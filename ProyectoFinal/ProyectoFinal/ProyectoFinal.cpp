// ProyectoFinal.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <mysql.h>
#include <iostream>
#include "Puesto.cpp"
#include "Empleado.cpp"
#include "Cliente.cpp"
#include "Venta.cpp"
#include "Marca.cpp"
#include "Producto.cpp"
using namespace std;

const string PUESTOS = "Puestos";
const string EMPLEADOS = "Empleados";
const string CLIENTES = "Clientes";
const string VENTAS = "Ventas";
const string MARCAS = "Marcas";
const string PRODUCTOS = "Productos";
const string PROVEEDORES = "Proveedores";
const string COMPRAS = "Compras";
MYSQL* conectar;
Puesto puestos = Puesto();
Empleado empleados = Empleado();
Cliente clientes = Cliente();
Venta ventas = Venta();
Marca marcas = Marca();
Producto productos = Producto();

void menu();
void crud(string);
void crear(string);
void leer(string);
void actualizar(string);
void eliminar(string);

int main()
{
    conectar = mysql_init(0);
    conectar = mysql_real_connect(conectar, "localhost", "root", "david2021", "proyecto_final", 3306, NULL, 0);
    if (conectar) {
        puestos.add_connector(conectar);
        empleados.add_connector(conectar);
        clientes.add_connector(conectar);
        ventas.add_connector(conectar);
        marcas.add_connector(conectar);
        productos.add_connector(conectar);
        menu();
    }
    else {
        cout << "Error en la conexión..." << endl;
    }
    system("pause");
    return 0;
}

void menu() {
    int opcion;

    while (true) {

        cout << "Menú" << endl;
        cout << "    1.Puestos" << endl;
        cout << "    2.Empleados" << endl;
        cout << "    3.Clientes" << endl;
        cout << "    4.Ventas" << endl;
        cout << "    5.Marcas" << endl;
        cout << "    6.Productos" << endl;
        cout << "    7.Proveedores" << endl;
        cout << "    8.Compras" << endl;
        cout << "    9.Salir\n" << endl;

        cout << "Ingrese una opción: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            crud(PUESTOS);
            break;
        case 2:
            crud(EMPLEADOS);
            break;
        case 3:
            crud(CLIENTES);
            break;
        case 4:
            crud(VENTAS);
            break;
        case 5:
            crud(MARCAS);
            break;
        case 6:
            crud(PRODUCTOS);
            break;
        case 7:
            crud(PROVEEDORES);
            break;
        case 8:
            crud(COMPRAS);
            break;
        case 9:
            exit(1);
        default:
            cout << "\nLa opción ingresada es incorrecta\n" << endl;
            break;
        }

        cout << "---------------------------------------\n" << endl;

    }
}

void crud(string entidad) {
    int opcion;
    bool bandera = true;

    while (bandera) {

        cout << "\n" + entidad << endl;
        cout << "    1.Crear" << endl;
        cout << "    2.Leer" << endl;
        cout << "    3.Actualizar" << endl;
        cout << "    4.Eliminar" << endl;
        cout << "    5.Regresar\n" << endl;

        cout << "Ingrese una opción: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            cin.ignore();
            crear(entidad);
            break;
        case 2:
            leer(entidad);
            break;
        case 3:
            actualizar(entidad);
            break;
        case 4:
            eliminar(entidad);
            break;
        case 5:
            bandera = false;
            break;
        default:
            cout << "\nLa opción ingresada es incorrecta\n" << endl;
            break;
        }

        cout << "\n---------------------------------------" << endl;

    }
}

void crear(string entidad) {
    if (entidad == "Puestos") {
        puestos.crear();
    }
    else if (entidad == "Empleados") {
        empleados.crear(puestos.imprimir());
    }
    else if (entidad == "Clientes") {
        clientes.crear();
    }
    else if (entidad == "Ventas") {
        ventas.crear(clientes.imprimir(), empleados.imprimir(), productos.imprimir());
    }
    else if (entidad == "Marcas") {
        marcas.crear();
    }
    else if (entidad == "Productos") {
        productos.crear(marcas.imprimir());
    }
    else if (entidad == "Proveedores") {
        cout << "\nPendiente..." << endl;
    }
    else {
        cout << "\nPendiente..." << endl;
    }
}

void leer(string entidad) {
    if (entidad == "Puestos") {
        puestos.leer();
    }
    else if (entidad == "Empleados") {
        empleados.leer();
    }
    else if (entidad == "Clientes") {
        clientes.leer();
    }
    else if (entidad == "Ventas") {
        ventas.leer();
    }
    else if (entidad == "Marcas") {
        marcas.leer();
    }
    else if (entidad == "Productos") {
        productos.leer();
    }
    else if (entidad == "Proveedores") {
        cout << "\nPendiente..." << endl;
    }
    else {
        cout << "\nPendiente..." << endl;
    }
}

void actualizar(string entidad) {
    if (entidad == "Puestos") {
        puestos.actualizar();
    }
    else if (entidad == "Empleados") {
        empleados.actualizar(puestos.imprimir());
    }
    else if (entidad == "Clientes") {
        clientes.actualizar();
    }
    else if (entidad == "Ventas") {
        ventas.actualizar(clientes.imprimir(), empleados.imprimir(), productos.imprimir());
    }
    else if (entidad == "Marcas") {
        marcas.actualizar();
    }
    else if (entidad == "Productos") {
        productos.actualizar(marcas.imprimir());
    }
    else if (entidad == "Proveedores") {
        cout << "\nPendiente..." << endl;
    }
    else {
        cout << "\nPendiente..." << endl;
    }
}

void eliminar(string entidad) {
    if (entidad == "Puestos") {
        puestos.eliminar();
    }
    else if (entidad == "Empleados") {
        empleados.eliminar();
    }
    else if (entidad == "Clientes") {
        clientes.eliminar();
    }
    else if (entidad == "Ventas") {
        ventas.eliminar();
    }
    else if (entidad == "Marcas") {
        marcas.eliminar();
    }
    else if (entidad == "Productos") {
        productos.eliminar();
    }
    else if (entidad == "Proveedores") {
        cout << "\nPendiente..." << endl;
    }
    else {
        cout << "\nPendiente..." << endl;
    }
}
