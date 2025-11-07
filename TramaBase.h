/**
 * @file TramaBase.h
 * @brief Clase base abstracta para el sistema de tramas PRT-7
 * @author Equipo de Desarrollo
 * @date 2025
 */

#ifndef TRAMABASE_H
#define TRAMABASE_H

// Forward declarations
class ListaDeCarga;
class RotorDeMapeo;

/**
 * @class TramaBase
 * @brief Clase base abstracta que define la interfaz para todas las tramas
 * 
 * Esta clase utiliza polimorfismo para permitir el procesamiento
 * uniforme de diferentes tipos de tramas (LOAD y MAP)
 */
class TramaBase {
public:
    /**
     * @brief Método virtual puro para procesar la trama
     * @param carga Puntero a la lista donde se almacenan los datos decodificados
     * @param rotor Puntero al rotor de mapeo (lista circular)
     */
    virtual void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) = 0;
    
    /**
     * @brief Destructor virtual (OBLIGATORIO para limpieza polimórfica)
     */
    virtual ~TramaBase() {}
    
    /**
     * @brief Obtiene la representación en string de la trama
     * @return Cadena que representa la trama
     */
    virtual const char* obtenerRepresentacion() = 0;
};

#endif // TRAMABASE_H