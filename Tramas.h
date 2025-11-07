/**
 * @file Tramas.h
 * @brief Clases derivadas para tramas LOAD y MAP
 * @author Equipo de Desarrollo
 * @date 2025
 */

#ifndef TRAMAS_H
#define TRAMAS_H

#include "TramaBase.h"
#include "ListaDeCarga.h"
#include "RotorDeMapeo.h"

/**
 * @class TramaLoad
 * @brief Trama de tipo LOAD que contiene un fragmento de datos
 * 
 * Representa una trama L,X donde X es un carácter a decodificar
 */
class TramaLoad : public TramaBase {
private:
    char caracter;           ///< Carácter contenido en la trama
    char buffer[10];         ///< Buffer para representación en string
    
public:
    /**
     * @brief Constructor que inicializa la trama con un carácter
     * @param c Carácter a almacenar
     */
    TramaLoad(char c) : caracter(c) {
        buffer[0] = 'L';
        buffer[1] = ',';
        buffer[2] = c;
        buffer[3] = '\0';
    }
    
    /**
     * @brief Procesa la trama LOAD: decodifica y almacena el carácter
     * @param carga Lista donde se insertará el carácter decodificado
     * @param rotor Rotor usado para el mapeo
     */
    void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) override {
        
        char decodificado = rotor->getMapeo(caracter);
        
        carga->insertarAlFinal(decodificado);
        
        std::cout << "Fragmento '" << caracter << "' decodificado como '" 
                  << decodificado << "'. Mensaje: [";
        carga->imprimirMensaje();
        std::cout << "]" << std::endl;
    }
    
    /**
     * @brief Obtiene la representación en string
     * @return Cadena "L,X"
     */
    const char* obtenerRepresentacion() override {
        return buffer;
    }
};

/**
 * @class TramaMap
 * @brief Trama de tipo MAP que contiene instrucciones de rotación
 * 
 * Representa una trama M,N donde N es el número de posiciones a rotar
 */
class TramaMap : public TramaBase {
private:
    int rotacion;      
    char buffer[20];    
    
public:
    /**
     * @brief Constructor que inicializa la trama con un valor de rotación
     * @param n Número de posiciones a rotar (positivo o negativo)
     */
    TramaMap(int n) : rotacion(n) {
        
        buffer[0] = 'M';
        buffer[1] = ',';
        
        int num = n;
        int pos = 2;
        if (num < 0) {
            buffer[pos++] = '-';
            num = -num;
        }
      
        if (num == 0) {
            buffer[pos++] = '0';
        } else {
           
            char digitos[10];
            int idx = 0;
            while (num > 0) {
                digitos[idx++] = '0' + (num % 10);
                num /= 10;
            }
           
            for (int i = idx - 1; i >= 0; i--) {
                buffer[pos++] = digitos[i];
            }
        }
        buffer[pos] = '\0';
    }
    
    /**
     * @brief Procesa la trama MAP: rota el rotor
     * @param carga Lista de carga (no utilizada)
     * @param rotor Rotor a rotar
     */
    void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) override {
        rotor->rotar(rotacion);
        
        std::cout << "ROTANDO ROTOR ";
        if (rotacion >= 0) std::cout << "+";
        std::cout << rotacion << "." << std::endl;
    }
    
    /**
     * @brief Obtiene la representación en string
     * @return Cadena "M,N"
     */
    const char* obtenerRepresentacion() override {
        return buffer;
    }
};

#endif 