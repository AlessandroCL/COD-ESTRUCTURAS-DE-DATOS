#include <functional>
#include <iostream>
using namespace std;
using namespace System;

template <class T>
class Nodo {
public:
	T elemento;
	Nodo* izq;
	Nodo* der;
	Nodo* padre;
};

template <class T>
class ArbolBB {
	typedef function<int(T, T)> Comp; //Lambda

	Nodo<T>* raiz;
	void(*procesar)(T); //Puntero a funcion

	Comp comparar; // lambda de criterio de comparación



public:
	ArbolBB(void(*otroPunteroAFuncion)(T)) {
		this->procesar = otroPunteroAFuncion;
		/*this->comparar = [](T a, T b)->int {return a - b; };*/
		this->comparar = [](string a, string b)->int {return a.compare(b); };
		raiz = nullptr;
	}
	Nodo<T>* getRaiz() { return raiz; }

	bool insertar(T e) {
		return _insertar(raiz, e);
	}
	void enOrden() {
		_enOrden(raiz);
	}
	void preOrden() {
		_preOrden(raiz);
	}
	void postOrden() {
		_postOrden(raiz);
	}
	int cantidad() {
		return _cantidad(raiz);
	}
	int altura() {
		return _altura(raiz);
	}
	bool Buscar(T e) {
		return _buscar(raiz, e);
	}
	Nodo<T>* Obtener(T e)
	{
		return _obtener(raiz, e);
	}

	// Propuesto 1: Elaborar un algoritmo para obtener el nodo cuyo valor es el mínimo del árbol.
	T Minimo() {
		return _minimo(raiz);
	}

	// Propuesto 2: Elaborar un algoritmo para obtener el nodo cuyo valor es el  máximo del árbol.
	T Maximo() {
		return _maximo(raiz);
	}
	bool Eliminar() {
		return _eliminar(raiz, e);
	}
	/*void merge() {
		return merge(raiz, inicio, mitad, final);
	}*/
	// [REZC] Propuestos ------------------------------------

	// Propuesto 3 [REZC]: Elaborar un algoritmo para obtener el nodo predecesor dado un nodo seleccionado del árbol.
	Nodo<T>* Predecesor(T e) {
		if (raiz->elemento == e) //Si es la raiz
			return nullptr;
		else
			return _predecesor(raiz, e, raiz);
	}

	// Propuesto 4 [REZC]: Elaborar un algoritmo para obtener el nodo sucesor dado un nodo seleccionado del árbol.
	Nodo<T>* Sucesor(T e) {
		return _sucesor(raiz, e, raiz);
	}

	// Propuesto 5 [REZC]: Elaborar un algoritmo para devolver el número de nodos por nivel del árbol.
	int NodosxNivel(int nivel) {
		return _NodosxNivel(raiz, nivel);
	}

	//Adicional [REZC]: Graficar Arbol
	void graficarArbol() {
		_graficarArbol(raiz, 45, 2, 0);
	}



private:
	bool _buscar(Nodo<T>* nodo, T e) {
		if (nodo == nullptr) return false;
		else {
			int r = comparar(nodo->elemento, e);
			if (r == 0) return true;
			else if (r < 0) {
				return _buscar(nodo->der, e);
			}
			else {
				return _buscar(nodo->izq, e);
			}
		}
	}
	Nodo<T>* _obtener(Nodo<T>* nodo, T e) {
		if (nodo == nullptr) return nullptr;
		else {
			int r = comparar(nodo->elemento, e);
			if (r == 0) {
				return nodo;
			}
			else if (r < 0) {
				return _obtener(nodo->der, e);
			}
			else {
				return _obtener(nodo->izq, e);
			}
		}
	}
	bool _insertar(Nodo<T>*& nodo, T e) {
		if (nodo == nullptr) {
			nodo = new Nodo<T>();
			nodo->elemento = e;
			return true;
		}
		else {
			int r = comparar(nodo->elemento, e);
			if (r == 0) return false;
			else if (r < 0) {
				return _insertar(nodo->der, e);
			}
			else {
				return _insertar(nodo->izq, e);
			}
		}
	}
	void _enOrden(Nodo<T>* nodo) {	//Izq => Raiz => Der
		if (nodo == nullptr) return;
		_enOrden(nodo->izq);
		procesar(nodo->elemento);
		_enOrden(nodo->der);
	}

	void _preOrden(Nodo<T>* nodo) {	//Raiz => Izq => Der
		if (nodo == nullptr) return;
		procesar(nodo->elemento);
		_preOrden(nodo->izq);
		_preOrden(nodo->der);
	}

	void _postOrden(Nodo<T>* nodo) {	//Izq => Der => Raiz
		if (nodo == nullptr) return;
		_postOrden(nodo->izq);
		_postOrden(nodo->der);
		procesar(nodo->elemento);
	}

	bool _vacio() {
		return raiz == nullptr;
	}
	int _cantidad(Nodo<T>* nodo) {
		//La cantidad de nodos del árbol es:
		//	0 si es vacío
		//	1 + la cantidad de nodos por la izquierda + la cantidad de nodos por la derecha

		if (nodo == nullptr)
			return 0;
		else
		{
			int ci, cd;
			ci = _cantidad(nodo->izq);
			cd = _cantidad(nodo->der);
			return 1 + ci + cd;
		}

	}
	int _altura(Nodo<T>* nodo) {
		//La altura del árbol es:
		//	0 si es vacío
		//	la mayor de las alturas por la izquierda y por la derecha, las cuáles son 0 si son vacías ó 1 + la altura por la izq(o der) en caso contrario

		if (nodo == nullptr)
			return 0;
		else
		{
			int ai, ad;
			ai = 1 + _altura(nodo->izq);
			ad = 1 + _altura(nodo->der);
			return ai > ad ? ai : ad;
		}
	}

	// Propuesto 1: Elaborar un algoritmo para obtener el nodo cuyo valor es el mínimo del árbol. 
	T _minimo(Nodo<T>* nodo) {	//El mínimo debe estar en la hoja izquierda de menor valor
		if (nodo->izq == nullptr) return nodo->elemento;
		else
			return _minimo(nodo->izq);
	}

	// Propuesto 2: Elaborar un algoritmo para obtener el nodo cuyo valor es el  máximo del árbol.
	T _maximo(Nodo<T>* nodo) {	//El maximo debe estar en la hoja derecha de mayor valor
		if (nodo->der == nullptr) return nodo->elemento;
		else
			return _maximo(nodo->der);
	}

	bool _eliminar(Nodo<T>*& nodo, T e) {
		if (nodo == nullptr) return false;
		//Buscamos el Nodo que contiene el elemento e
		else {
			int r = comparar(nodo->elemento, e);
			if (r < 0) {	//si (nodo->elemento < e)
				return _eliminar(nodo->der, e);
			}
			else if (r > 0) {	//si (nodo->elemento > e)
				return _eliminar(nodo->izq, e);
			}

			//Analizamos el escenario en el que se encuentra el Nodo a eliminar
			else { // r==0 es porque se encontró el elemento e en el arbol	| si (nodo->elemento == e)
				if (nodo->der == nullptr && nodo->izq == nullptr) {	//Caso 1: Hoja
					nodo = nullptr;
					delete nodo;	//*REZC: Sí se puede hacer delete nullptr, porque nullptr es un puntero
					return true;
				}
				else if (nodo->izq == nullptr) { //Caso 2: Izq Vacío y Der No Vacío
					nodo = nodo->der;
					return true;
				}
				else if (nodo->der == nullptr) { //Caso 3: Der Vacío e Izq No Vacío
					nodo = nodo->izq;
					return true;
				}
				else { //Caso 4: Izq y Der No Vacíos
					Nodo<T>* aux = nodo->der; //Se establece buscar el menor elemento por la derecha [PPT: Nodo es la Raiz, aux es 35]
					while (aux->izq != nullptr)
					{
						aux = aux->izq; //Se obtiene la hoja menor
					}
					nodo->elemento = aux->elemento; //Se actualiza el elemento en el nodo raiz y
					return _eliminar(nodo->der, aux->elemento); //se envía a eliminar el elemento en el arbol por la derecha
				}
			}
		}
	}


	// --------------------------------------------------------------------------
	// Propuesto 3 [REZC]: Elaborar un algoritmo para obtener el nodo predecesor dado un nodo seleccionado del árbol.
	Nodo<T>* _predecesor(Nodo<T>*& nodo, T e, Nodo<T>*& _padre)
	{
		//cout << "Nodo: " << nodo->elemento << endl;
		//Almacenamos el Padre
		if (nodo == raiz)
		{
			nodo->padre = nullptr;
		}
		else
			if (nodo != nullptr) nodo->padre = _padre; //Para elementos que no existen en el arbol (nodo == nullptr)

		if (nodo == nullptr) return nullptr;

		//Buscamos el elemento en el Arbol
		else if (e < nodo->elemento)
		{
			return _predecesor(nodo->izq, e, nodo);
		}

		else if (e > nodo->elemento)
		{
			return _predecesor(nodo->der, e, nodo);
		}

		// Se encontró el elmento en el Nodo "nodo"
		//cout << "Nodo Encontrado: " << nodo->elemento << endl;
///*
		// Si tiene nodo izquierdo [allí estará el predecesor]
		else if (nodo->izq != nullptr)
		{
			cout << "[Pred]Nodo ENCONTRADO 1: " << nodo->elemento << endl;
			cout << "[Pred]PADRE ENCONTRADO 1: " << nodo->padre->elemento << endl;

			T mayor = _maximo(nodo->izq); cout << "Mayor: " << mayor << endl;
			//Guardamos el Mayor en un Nodo
			Nodo<T>* aux = new Nodo<T>();
			aux->elemento = mayor;
			return aux;
		}
		else // Si no tiene nodo izquierdo [ Buscaremos el Nodo Padre como Predecesor]
		{
			cout << "[Pred]Nodo ENCONTRADO 2: " << nodo->elemento << endl;
			cout << "[Pred]PADRE ENCONTRADO 2: " << nodo->padre->elemento << endl;

			Nodo<T>* nodo_aux = nodo;	//Nodo
			Nodo<T>* y = nodo->padre;	//Padre del Nodo
			while (y != nullptr)
			{
				if (nodo_aux == y->izq)
				{
					nodo_aux = y;
					y = y->padre;

				}
				else
					break;
			}
			return y; // Encuentra Predecesor

		}
		//*/
	}

	// Propuesto 4 [REZC]: Elaborar un algoritmo para obtener el nodo sucesor dado un nodo seleccionado del árbol.
	Nodo<T>* _sucesor(Nodo<T>*& nodo, T e, Nodo<T>*& _padre)
	{
		//cout << "Nodo: " << nodo->elemento << endl;
		//Almacenamos el Padre
		if (nodo == raiz)
			nodo->padre = nullptr;
		else
			if (nodo != nullptr) nodo->padre = _padre; //Para elementos que no existen en el arbol (nodo == nullptr)

		if (nodo == nullptr) return nullptr;

		//Buscamos el elemento en el Arbol
		else if (e < nodo->elemento)
		{
			return _sucesor(nodo->izq, e, nodo);
		}

		else if (e > nodo->elemento)
		{
			return _sucesor(nodo->der, e, nodo);
		}

		// Se encontró el elemento en el Nodo "nodo"
		//cout << "Nodo Encontrado: " << nodo->elemento << endl;
///*
		// Si tiene nodo derecho [allí estará el sucesor]
		else if (nodo->der != nullptr)
		{
			cout << "[Suc]Nodo ENCONTRADO 1: " << nodo->elemento << endl;
			if (nodo->padre != nullptr) cout << "[Suc]PADRE ENCONTRADO 1: " << nodo->padre->elemento << endl;
			else cout << "[Suc]PADRE ENCONTRADO 1: NULL" << endl;

			T menor = _minimo(nodo->der); cout << "Menor: " << menor << endl;
			//Guardamos el Menor en un Nodo
			Nodo<T>* aux = new Nodo<T>();
			aux->elemento = menor;
			return aux;
		}
		else // Si no tiene nodo derecho [ Buscaremos el Nodo Padre como Sucesor]
		{
			cout << "[Suc]Nodo ENCONTRADO 2: " << nodo->elemento << endl;
			cout << "[Suc]PADRE ENCONTRADO 2: " << nodo->padre->elemento << endl;

			Nodo<T>* nodo_aux = nodo;	//Nodo
			Nodo<T>* y = nodo->padre;	//Padre del Nodo
			while (y != nullptr)
			{
				if (nodo_aux == y->der)
				{
					nodo_aux = y;
					y = y->padre;

				}
				else
					break;
			}
			return y; // Encuentra Sucesor

		}
		//*/
	}

	// Propuesto 5 [REZC]: Elaborar un algoritmo para devolver el número de nodos por nivel del árbol.
	int _NodosxNivel(Nodo<T>*& nodo, T nivel)
	{
		if (nodo != nullptr)
		{
			if (nivel == 0)
				return _NodosxNivel(nodo->izq, nivel - 1) + _NodosxNivel(nodo->der, nivel - 1) + 1;
			return _NodosxNivel(nodo->izq, nivel - 1) + _NodosxNivel(nodo->der, nivel - 1);
		}
		return 0;
	}

	//Adicional [REZC]: Graficar Arbol
	void _graficarArbol(Nodo<T>*& nodo, int x, int y, int n)
	{
		if (nodo == nullptr) return;

		Console::SetCursorPosition(x, y); cout << nodo->elemento;
		_graficarArbol(nodo->izq, x - 15 + n * 6, y + 2, n + 1);
		_graficarArbol(nodo->der, x + 15 - n * 6, y + 2, n + 1);

	}

	// --------------------------------------------------------------------------
	//void _merge(Nodo<T>*& nodo, int inicio,int mitad, int final) {
	//	int i, j, k;
	//	int elementosIzq = mitad - inicio + 1;
	//	int elementosDer = final - mitad;

	//	Nodo<T>izq(elementosIzq);
	//	Nodo<T>der(elementosDer);

	//	for (int i = 0; i < elementosIzq; i++) {
	//		izquierda[i] = nodo(inicio + i);
	//	}
	//	for (int j = 0; j < elementosDer; j++) {
	//		derecha[i] = nodo(mitad + 1 + j);
	//	}

	//	i = 0;
	//	j = 0;
	//	k = inicio;

	//	while (i < elementosIzq && j < elementosDer) {
	//		if (izquierda[i] <= derecha[j]) {
	//			arreglo[k] = izquierda[i];
	//			i++;
	//		}
	//		else {
	//			arreglo[k] = derecha[j];
	//			j++
	//		}
	//		k++;
	//	}
	//	while (j < elementosDer) {
	//		arreglo[k] = derecha[j];
	//		j++;
	//		k++;
	//	}
	//	while (i < elementosIzq) {
	//		arreglo[k] = izquierda[i];
	//		i++;
	//		k++;
	//	}
	//}
	//void _mergeSort(Nodo<T>*& nodo, int inicio, int final) {
	//	if (inicio < final) {
	//		int mitad = inicio + (final - inicio) / 2;
	//		_mergeSort(nodo, inicio, mitad);
	//		_mergeSort(nodo, mitad + 1, final);
	//		_merge(nodo, inicio, mitad, final);
	//	}
	//}

};
