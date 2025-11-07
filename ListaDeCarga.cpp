/**
 * @file ListaDeCarga.cpp
 * @brief Implementación de la clase ListaDeCarga
 */

#include "ListaDeCarga.h"
#include <iostream>

ListaDeCarga::ListaDeCarga() : cabeza(nullptr), cola(nullptr), tamanio(0) {}

ListaDeCarga::~ListaDeCarga() {
    NodoCarga* actual = cabeza;
    while (actual != nullptr) {
        NodoCarga* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
}

void ListaDeCarga::insertarAlFinal(char dato) {
    NodoCarga* nuevo = new NodoCarga(dato);
    
    if (cabeza == nullptr) {
       
        cabeza = nuevo;
        cola = nuevo;
    } else {
    
        cola->siguiente = nuevo;
        nuevo->previo = cola;
        cola = nuevo;
    }
    
    tamanio++;
}

void ListaDeCarga::imprimirMensaje() {
    if (cabeza == nullptr) {
        std::cout << "[Mensaje vacio]" << std::endl;
        return;
    }
    
    NodoCarga* actual = cabeza;
    while (actual != nullptr) {
        std::cout << actual->dato;
        actual = actual->siguiente;
    }
}