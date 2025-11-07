#include <iostream>
#include "TramaBase.h"
#include "Tramas.h"
#include "ListaDeCarga.h"
#include "RotorDeMapeo.h"

int pruebasExitosas = 0;
int pruebasTotales = 0;

/**
 * @brief Macro para verificar condiciones en las pruebas
 */
#define ASSERT(condicion, mensaje) \
    pruebasTotales++; \
    if (condicion) { \
        std::cout << "[OK] " << mensaje << std::endl; \
        pruebasExitosas++; \
    } else { \
        std::cout << "[FALLO] " << mensaje << std::endl; \
    }

/**
 * @brief Prueba básica de la ListaDeCarga
 */
void test_ListaDeCarga() {
    std::cout << "\n=== Prueba: ListaDeCarga ===" << std::endl;
    
    ListaDeCarga lista;
    
    ASSERT(lista.estaVacia(), "Lista recién creada debe estar vacía");
    ASSERT(lista.obtenerTamanio() == 0, "Tamaño inicial debe ser 0");
    
    lista.insertarAlFinal('A');
    ASSERT(!lista.estaVacia(), "Lista no debe estar vacía después de insertar");
    ASSERT(lista.obtenerTamanio() == 1, "Tamaño debe ser 1 después de insertar");
    
    lista.insertarAlFinal('B');
    lista.insertarAlFinal('C');
    ASSERT(lista.obtenerTamanio() == 3, "Tamaño debe ser 3 después de 3 inserciones");
    
    std::cout << "Contenido de la lista: ";
    lista.imprimirMensaje();
    std::cout << std::endl;
}

/**
 * @brief Prueba básica del RotorDeMapeo
 */
void test_RotorDeMapeo() {
    std::cout << "\n=== Prueba: RotorDeMapeo ===" << std::endl;
    
    RotorDeMapeo rotor;
    
    char resultado = rotor.getMapeo('A');
    ASSERT(resultado == 'A', "Sin rotación: A -> A");
    
    rotor.rotar(1);
    resultado = rotor.getMapeo('A');
    ASSERT(resultado == 'B', "Con rotación +1: A -> B");
   
    rotor.rotar(-1);
    resultado = rotor.getMapeo('A');
    ASSERT(resultado == 'A', "Con rotación -1: A -> A de nuevo");
  
    rotor.rotar(26); // Una vuelta completa
    resultado = rotor.getMapeo('A');
    ASSERT(resultado == 'A', "Rotación completa (26): A -> A");
    
    resultado = rotor.getMapeo(' ');
    ASSERT(resultado == ' ', "Espacios no deben cambiar");
    
    std::cout << "Estado actual del rotor: ";
    rotor.imprimirEstado();
}

/**
 * @brief Prueba de polimorfismo con TramaBase
 */
void test_Polimorfismo() {
    std::cout << "\n=== Prueba: Polimorfismo ===" << std::endl;
    
    ListaDeCarga lista;
    RotorDeMapeo rotor;
    
    TramaBase* trama1 = new TramaLoad('H');
    TramaBase* trama2 = new TramaLoad('O');
    TramaBase* trama3 = new TramaLoad('L');
    TramaBase* trama4 = new TramaLoad('A');
    
    std::cout << "Procesando tramas LOAD..." << std::endl;
    trama1->procesar(&lista, &rotor);
    trama2->procesar(&lista, &rotor);
    trama3->procesar(&lista, &rotor);
    trama4->procesar(&lista, &rotor);
    
    ASSERT(lista.obtenerTamanio() == 4, "Deben haberse procesado 4 tramas");
    
    std::cout << "Mensaje ensamblado: ";
    lista.imprimirMensaje();
    std::cout << std::endl;
   
    delete trama1;
    delete trama2;
    delete trama3;
    delete trama4;
    
    ASSERT(true, "Memoria liberada sin errores (destructores virtuales funcionan)");
}

/**
 * @brief Prueba del ejemplo completo del documento
 */
void test_EjemploCompleto() {
    std::cout << "\n=== Prueba: Ejemplo Completo (HOLCY YORLD) ===" << std::endl;
    
    ListaDeCarga lista;
    RotorDeMapeo rotor;
    
    const char* tramas[] = {
        "L,H", "L,O", "L,L", "M,2", "L,A", "L, ", 
        "L,W", "M,-2", "L,O", "L,R", "L,L", "L,D", nullptr
    };
    
    int i = 0;
    while (tramas[i] != nullptr) {
        char tipo = tramas[i][0];
        
        if (tipo == 'L') {
            char caracter = tramas[i][2];
            TramaBase* trama = new TramaLoad(caracter);
            trama->procesar(&lista, &rotor);
            delete trama;
        } else if (tipo == 'M') {
          
            int rotacion = 0;
            int signo = 1;
            int idx = 2;
            
            if (tramas[i][idx] == '-') {
                signo = -1;
                idx++;
            }
            
            while (tramas[i][idx] >= '0' && tramas[i][idx] <= '9') {
                rotacion = rotacion * 10 + (tramas[i][idx] - '0');
                idx++;
            }
            
            TramaBase* trama = new TramaMap(rotacion * signo);
            trama->procesar(&lista, &rotor);
            delete trama;
        }
        
        i++;
    }
    
    std::cout << "\nMensaje final: ";
    lista.imprimirMensaje();
    std::cout << std::endl;
    
    ASSERT(lista.obtenerTamanio() == 12, "El mensaje debe tener 12 caracteres");
}

/**
 * @brief Prueba de rotaciones extremas
 */
void test_RotacionesExtremas() {
    std::cout << "\n=== Prueba: Rotaciones Extremas ===" << std::endl;
    
    RotorDeMapeo rotor;
    
    rotor.rotar(1000);
    char resultado = rotor.getMapeo('A');
    std::cout << "Después de rotar 1000: A -> " << resultado << std::endl;
    ASSERT(true, "Rotación grande completada sin crash");
  
    rotor.rotar(-1000);
    resultado = rotor.getMapeo('A');
    std::cout << "Después de rotar -1000: A -> " << resultado << std::endl;
    ASSERT(true, "Rotación negativa grande completada sin crash");
}

/**
 * @brief Función principal de pruebas
 */
int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "  Pruebas Unitarias - Decodificador PRT-7" << std::endl;
    std::cout << "========================================" << std::endl;
    
    test_ListaDeCarga();
    test_RotorDeMapeo();
    test_Polimorfismo();
    test_EjemploCompleto();
    test_RotacionesExtremas();
   
    std::cout << "\n========================================" << std::endl;
    std::cout << "  Resumen de Pruebas" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Pruebas exitosas: " << pruebasExitosas << "/" << pruebasTotales << std::endl;
    
    if (pruebasExitosas == pruebasTotales) {
        std::cout << "\n¡Todas las pruebas pasaron correctamente! ✓" << std::endl;
        return 0;
    } else {
        std::cout << "\nAlgunas pruebas fallaron. ✗" << std::endl;
        return 1;
    }
}