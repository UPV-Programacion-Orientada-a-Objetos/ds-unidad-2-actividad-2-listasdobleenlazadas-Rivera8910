/**
 * @file RotorDeMapeo.cpp
 * @brief Implementación de la clase RotorDeMapeo
 */

#include "RotorDeMapeo.h"
#include <iostream>

RotorDeMapeo::RotorDeMapeo() : cabeza(nullptr), tamanio(0) {
    
    const char* alfabeto = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    NodoRotor* primero = nullptr;
    NodoRotor* actual = nullptr;
    
    for (int i = 0; alfabeto[i] != '\0'; i++) {
        NodoRotor* nuevo = new NodoRotor(alfabeto[i]);
        
        if (primero == nullptr) {
          
            primero = nuevo;
            actual = nuevo;
            cabeza = nuevo;  
        } else {
           
            actual->siguiente = nuevo;
            nuevo->previo = actual;
            actual = nuevo;
        }
        tamanio++;
    }
    
    // Cerrar el círculo
    if (actual != nullptr && primero != nullptr) {
        actual->siguiente = primero;
        primero->previo = actual;
    }
}

RotorDeMapeo::~RotorDeMapeo() {
    if (cabeza == nullptr) return;
    
    // Romper el círculo
    NodoRotor* ultimo = cabeza->previo;
    ultimo->siguiente = nullptr;
    
    // Eliminar todos los nodos
    NodoRotor* actual = cabeza;
    while (actual != nullptr) {
        NodoRotor* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
}

void RotorDeMapeo::rotar(int n) {
    if (cabeza == nullptr) return;
    
    n = n % tamanio;
    
    if (n > 0) {
        for (int i = 0; i < n; i++) {
            cabeza = cabeza->siguiente;
        }
    } else if (n < 0) {
       
        for (int i = 0; i > n; i--) {
            cabeza = cabeza->previo;
        }
    }
}

char RotorDeMapeo::getMapeo(char in) {
    
    if (in >= 'a' && in <= 'z') {
        in = in - 32;
    }
    
    if (in < 'A' || in > 'Z') {
        return in;
    }
   
    NodoRotor* nodoEntrada = buscarNodo(in);
    if (nodoEntrada == nullptr) {
        return in;  
    }
    
    int distancia = calcularDistancia(cabeza, nodoEntrada);
   
    NodoRotor* nodoSalida = cabeza;
    for (int i = 0; i < distancia; i++) {
        nodoSalida = nodoSalida->siguiente;
    }
    
    return nodoSalida->dato;
}

NodoRotor* RotorDeMapeo::buscarNodo(char c) {
    if (cabeza == nullptr) return nullptr;
    
    NodoRotor* actual = cabeza;
    do {
        if (actual->dato == c) {
            return actual;
        }
        actual = actual->siguiente;
    } while (actual != cabeza);
    
    return nullptr;
}

int RotorDeMapeo::calcularDistancia(NodoRotor* desde, NodoRotor* hasta) {
    if (desde == nullptr || hasta == nullptr) return 0;
    
    int distancia = 0;
    NodoRotor* actual = desde;
    
    while (actual != hasta) {
        actual = actual->siguiente;
        distancia++;
        if (distancia > tamanio) {
            return 0;  
        }
    }
    
    return distancia;
}

void RotorDeMapeo::imprimirEstado() {
    if (cabeza == nullptr) {
        std::cout << "Rotor vacio" << std::endl;
        return;
    }
    
    std::cout << "Estado del Rotor (cabeza en '" << cabeza->dato << "'): ";
    NodoRotor* actual = cabeza;
    do {
        std::cout << actual->dato;
        if (actual == cabeza) std::cout << "*";
        std::cout << " ";
        actual = actual->siguiente;
    } while (actual != cabeza);
    std::cout << std::endl;
}