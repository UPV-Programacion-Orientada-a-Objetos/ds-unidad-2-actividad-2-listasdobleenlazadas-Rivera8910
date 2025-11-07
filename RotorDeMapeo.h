/**
 * @file RotorDeMapeo.h
 * @brief Implementación de Lista Circular Doblemente Enlazada para el mapeo de caracteres
 * @author Equipo de Desarrollo
 * @date 2025
 */

#ifndef ROTORDEMAPEO_H
#define ROTORDEMAPEO_H

/**
 * @struct NodoRotor
 * @brief Nodo de la lista circular que contiene un carácter
 */
struct NodoRotor {
    char dato;
    NodoRotor* siguiente;
    NodoRotor* previo;
    
    NodoRotor(char c) : dato(c), siguiente(nullptr), previo(nullptr) {}
};

/**
 * @class RotorDeMapeo
 * @brief Lista circular doblemente enlazada que simula un disco de cifrado
 * 
 * Funciona como una rueda de César que puede rotar en ambas direcciones.
 * El puntero cabeza indica la posición 'cero' actual del alfabeto.
 */
class RotorDeMapeo {
private:
    NodoRotor* cabeza;  ///< Posición actual 'cero' del rotor
    int tamanio;        ///< Número de elementos en el rotor
    
public:
    /**
     * @brief Constructor que inicializa el rotor con el alfabeto A-Z
     */
    RotorDeMapeo();
    
    /**
     * @brief Destructor que libera toda la memoria
     */
    ~RotorDeMapeo();
    
    /**
     * @brief Rota el rotor N posiciones
     * @param n Número de posiciones a rotar (positivo=adelante, negativo=atrás)
     */
    void rotar(int n);
    
    /**
     * @brief Obtiene el carácter mapeado según la rotación actual
     * @param in Carácter de entrada
     * @return Carácter decodificado según el estado actual del rotor
     */
    char getMapeo(char in);
    
    /**
     * @brief Imprime el estado actual del rotor (para debug)
     */
    void imprimirEstado();
    
private:
    /**
     * @brief Encuentra un nodo que contiene el carácter dado
     * @param c Carácter a buscar
     * @return Puntero al nodo encontrado o nullptr
     */
    NodoRotor* buscarNodo(char c);
    
    /**
     * @brief Calcula la distancia entre dos nodos en la lista circular
     * @param desde Nodo inicial
     * @param hasta Nodo final
     * @return Número de pasos entre los nodos
     */
    int calcularDistancia(NodoRotor* desde, NodoRotor* hasta);
};

#endif // ROTORDEMAPEO_H