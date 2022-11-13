#pragma once 
#include <conio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include "ARBOL_BB.h"
#define nombre_archivo "CUENTAS_ALEATORIAS.csv"
using namespace std;
using namespace System;
void lecturaDatosDeArchivo_Arbol(ArbolBB<string>* arbol) {
	ifstream archIN;
	archIN.open(nombre_archivo, ios::in);

	if (!archIN.is_open())
	{
		cout << "Error: No se pudo abrir el archivo !!!" << endl;
		exit(1);
	}

	string linea;
	char delimitador = ';';
	getline(archIN, linea);

	while (getline(archIN, linea)) {
		stringstream stream(linea);

		string col1, col2, col3, col4, col5, col6, col7;
		//extrae los valores de la fila
		getline(stream, col1, delimitador);
		getline(stream, col2, delimitador);
		getline(stream, col3, delimitador);
		getline(stream, col4, delimitador);
		getline(stream, col5, delimitador);
		getline(stream, col6, delimitador);
		getline(stream, col7, delimitador);

		//imprime
		cout << "----------------------------------------" << endl;
		cout << "|| " << col1;
		cout << " ||" << col2;
		cout << " ||" << col3;
		cout << " ||" << col4;
		cout << " ||" << col5;
		cout << " ||" << col6;
		cout << " ||" << col7;
		cout << endl;

		arbol->insertar(col2);
	}

	archIN.close();

}
void imprimir(string e) {
	cout << e << endl;
}
class CCajero {
private:
	long saldo;
	int opc;
public:
	CCajero(long _saldo, int _opc) {
		this->saldo = _saldo;
		this->opc = _opc;
	}
		
	void Menu() {
		titulo("CAJERO BBVA");
		cout << "1. RETIRA" << endl;
		cout << "2. DEPOSITA" << endl;
		cout << "3. PAGA" << endl;
		cout << "4. TRANSFIERE" << endl;
		cout << "5. SALIR" << endl;
		cout << "6. CONSULTA" << endl;
		cout << "opc: ";
		cin >> opc;
		switch (opc)
		{
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			cout << "|| NOMBRE || APELLIDO || CONTRASENIA || SOLES || DOLARES || CREDITO" << endl;
			ArbolBB<string>*arbol = new ArbolBB<string>(imprimir);

			lecturaDatosDeArchivo_Arbol(arbol);

			cout << "Cantidad: " << arbol->cantidad() << endl;
			cout << "Minimo: " << arbol->Minimo() << endl;
			cout << "Maximo: " << arbol->Maximo() << endl;

			cout << "-----EnOrden-----" << endl;
			arbol->enOrden();
			cout << "----postOrden----" << endl;
			arbol->postOrden();
			cout << "-----PreOrden---" << endl;
			arbol->preOrden();
			cout << endl;
			cout << "-----MergerSort---" << endl;
			break;
		}
	}
	void titulo(string tittulo) {
		cout << "==============================================" << endl;
		cout << tittulo << endl;
		cout << "==============================================" << endl;
	}
	
};
