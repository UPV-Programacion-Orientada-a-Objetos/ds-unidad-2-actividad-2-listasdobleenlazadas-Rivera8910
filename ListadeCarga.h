/**
 * @file ListaDeCarga.h
 * @brief Lista doblemente enlazada para almacenar caracteres decodificados
 * @author Equipo de Desarrollo
 * @date 2025
 */

#ifndef LISTADECARGA_H
#define LISTADECARGA_H

/**
 * @struct NodoCarga
 * @brief Nodo de la lista doblemente enlazada
 */
struct NodoCarga {
    char dato;
    NodoCarga* siguiente;
    NodoCarga* previo;
    
    NodoCarga(char c) : dato(c), siguiente(nullptr), previo(nullptr) {}
};

/**
 * @class ListaDeCarga
 * @brief Lista doblemente enlazada que almacena los caracteres decodificados
 * 
 * Mantiene el orden de llegada de los fragmentos de datos procesados
 */
class ListaDeCarga {
private:
    NodoCarga* cabeza;  
    NodoCarga* cola;   
    int tamanio;        
    
public:
    /**
     * @brief Constructor que inicializa una lista vacía
     */
    ListaDeCarga();
    
    /**
     * @brief Destructor que libera toda la memoria
     */
    ~ListaDeCarga();
    
    /**
     * @brief Inserta un carácter al final de la lista
     * @param dato Carácter a insertar
     */
    void insertarAlFinal(char dato);
    
    /**
     * @brief Imprime el mensaje completo ensamblado
     */
    void imprimirMensaje();
    
    /**
     * @brief Obtiene el tamaño actual de la lista
     * @return Número de caracteres almacenados
     */
    int obtenerTamanio() const { return tamanio; }
    
    /**
     * @brief Verifica si la lista está vacía
     * @return true si está vacía, false en caso contrario
     */
    bool estaVacia() const { return cabeza == nullptr; }
};

#endif // LISTADECARGA_H