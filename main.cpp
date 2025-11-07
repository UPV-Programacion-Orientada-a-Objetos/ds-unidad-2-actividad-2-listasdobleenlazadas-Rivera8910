#include <iostream>
#include <fstream>
#include "TramaBase.h"
#include "Tramas.h"
#include "ListaDeCarga.h"
#include "RotorDeMapeo.h"


#ifdef _WIN32
    #include <windows.h>
#else
    // Para Linux/Mac
    #include <fcntl.h>
    #include <unistd.h>
    #include <termios.h>
#endif

/**
 * @brief Parsea una línea del protocolo y crea la trama correspondiente
 * @param linea Cadena con el formato "L,X" o "M,N"
 * @return Puntero a la trama creada o nullptr si hay error
 */
TramaBase* parsearTrama(const char* linea) {
    if (linea == nullptr || linea[0] == '\0') {
        return nullptr;
    }
    
    if (linea[1] != ',') {
        return nullptr;
    }
    
    char tipo = linea[0];
    
    if (tipo == 'L' || tipo == 'l') {
     
        char caracter = linea[2];
        return new TramaLoad(caracter);
    }
    else if (tipo == 'M' || tipo == 'm') {
       
        int numero = 0;
        int signo = 1;
        int i = 2;
        
        if (linea[i] == '-') {
            signo = -1;
            i++;
        } else if (linea[i] == '+') {
            i++;
        }
        
        while (linea[i] >= '0' && linea[i] <= '9') {
            numero = numero * 10 + (linea[i] - '0');
            i++;
        }
        
        return new TramaMap(numero * signo);
    }
    
    return nullptr;
}

/**
 * @brief Lee una línea del puerto serial (implementación multiplataforma)
 * @param handle Handle del puerto serial
 * @param buffer Buffer donde se almacenará la línea
 * @param maxLen Tamaño máximo del buffer
 * @return true si se leyó correctamente, false en caso contrario
 */
#ifdef _WIN32
bool leerLineaSerial(HANDLE handle, char* buffer, int maxLen) {
    int idx = 0;
    DWORD bytesLeidos;
    
    while (idx < maxLen - 1) {
        if (!ReadFile(handle, &buffer[idx], 1, &bytesLeidos, NULL) || bytesLeidos == 0) {
            return false;
        }
        
        if (buffer[idx] == '\n') {
            buffer[idx] = '\0';
         
            if (idx > 0 && buffer[idx-1] == '\r') {
                buffer[idx-1] = '\0';
            }
            return true;
        }
        idx++;
    }
    buffer[idx] = '\0';
    return true;
}
#else
bool leerLineaSerial(int fd, char* buffer, int maxLen) {
    int idx = 0;
    
    while (idx < maxLen - 1) {
      if (read(fd, &buffer[idx], 1) <= 0) {
            return false;
        }
        
        if (buffer[idx] == '\n') {
            buffer[idx] = '\0';
            if (idx > 0 && buffer[idx-1] == '\r') {
                buffer[idx-1] = '\0';
            }
            return true;
        }
        idx++;
    }
    buffer[idx] = '\0';
    return true;
}
#endif

/**
 * @brief Función principal del decodificador
 */
int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "  Decodificador PRT-7" << std::endl;
    std::cout << "  Sistema de Ciberseguridad Industrial" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << std::endl;
    
 
    ListaDeCarga miListaDeCarga;
    RotorDeMapeo miRotorDeMapeo;
    
    std::cout << "Iniciando sistema..." << std::endl;
    std::cout << "Lista de carga inicializada." << std::endl;
    std::cout << "Rotor de mapeo inicializado." << std::endl;
    std::cout << std::endl;
 
    const char* puertoSerial = nullptr;
    
#ifdef _WIN32
    puertoSerial = "COM3"; 
    std::cout << "Conectando a puerto " << puertoSerial << "..." << std::endl;
    
    HANDLE hSerial = CreateFileA(
        puertoSerial,
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        0,
        NULL
    );
    
    if (hSerial == INVALID_HANDLE_VALUE) {
        std::cerr << "ERROR: No se pudo abrir el puerto serial." << std::endl;
        std::cerr << "Asegurate de que el Arduino este conectado a " << puertoSerial << std::endl;
        return 1;
    }
    
    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "ERROR: No se pudo obtener el estado del puerto." << std::endl;
        CloseHandle(hSerial);
        return 1;
    }
    
    dcbSerialParams.BaudRate = CBR_9600;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    
    if (!SetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "ERROR: No se pudo configurar el puerto." << std::endl;
        CloseHandle(hSerial);
        return 1;
    }
    
    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    SetCommTimeouts(hSerial, &timeouts);
    
#else
    puertoSerial = "/dev/ttyUSB0"; 
    std::cout << "Conectando a puerto " << puertoSerial << "..." << std::endl;
    
    int fd = open(puertoSerial, O_RDWR | O_NOCTTY | O_NDELAY);
    
    if (fd == -1) {
        std::cerr << "ERROR: No se pudo abrir el puerto serial." << std::endl;
        std::cerr << "Asegurate de que el Arduino este conectado a " << puertoSerial << std::endl;
        return 1;
    }
    
    struct termios tty;
    tcgetattr(fd, &tty);
    
    cfsetospeed(&tty, B9600);
    cfsetispeed(&tty, B9600);
    
    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;
    tty.c_cflag &= ~CRTSCTS;
    tty.c_cflag |= CREAD | CLOCAL;
    
    tty.c_lflag &= ~ICANON;
    tty.c_lflag &= ~ECHO;
    tty.c_lflag &= ~ISIG;
    
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);
    
    tty.c_cc[VMIN] = 1;
    tty.c_cc[VTIME] = 5;
    
    tcsetattr(fd, TCSANOW, &tty);
#endif
    
    std::cout << "Conexion establecida. Esperando tramas..." << std::endl;
    std::cout << std::endl;
   
    char buffer[256];
    
    while (true) {
        
#ifdef _WIN32
        if (!leerLineaSerial(hSerial, buffer, sizeof(buffer))) {
#else
        if (!leerLineaSerial(fd, buffer, sizeof(buffer))) {
#endif
           
            continue;
        }
       
        if (buffer[0] == '\0') {
            continue;
        }
        
        TramaBase* trama = parsearTrama(buffer);
        
        if (trama == nullptr) {
            std::cerr << "ADVERTENCIA: Trama mal formada: [" << buffer << "]" << std::endl;
            continue;
        }
       
        std::cout << "Trama recibida: [" << trama->obtenerRepresentacion() 
                  << "] -> Procesando... -> ";
        
        trama->procesar(&miListaDeCarga, &miRotorDeMapeo);
       
        delete trama;
        
        std::cout << std::endl;
    }
    
#ifdef _WIN32
    CloseHandle(hSerial);
#else
    close(fd);
#endif
   
    std::cout << std::endl;
    std::cout << "---" << std::endl;
    std::cout << "Flujo de datos terminado." << std::endl;
    std::cout << "MENSAJE OCULTO ENSAMBLADO:" << std::endl;
    miListaDeCarga.imprimirMensaje();
    std::cout << std::endl;
    std::cout << "---" << std::endl;
    std::cout << "Liberando memoria... Sistema apagado." << std::endl;
    
    return 0;
}