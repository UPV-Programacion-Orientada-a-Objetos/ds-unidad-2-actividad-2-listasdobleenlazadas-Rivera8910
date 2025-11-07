# CMakeLists.txt para el proyecto Decodificador PRT-7
# Versión mínima de CMake requerida
cmake_minimum_required(VERSION 3.10)

project(DecodificadorPRT7 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(MSVC)
    
    add_compile_options(/W4)
else()
    
    add_compile_options(-Wall -Wextra -pedantic)
endif()

if(WIN32)
    add_definitions(-D_WIN32)
endif()

set(SOURCES
    main.cpp
    RotorDeMapeo.cpp
    ListaDeCarga.cpp
)

# Archivos header
set(HEADERS
    TramaBase.h
    Tramas.h
    RotorDeMapeo.h
    ListaDeCarga.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)

# Información de compilación
message(STATUS "========================================")
message(STATUS "Proyecto: ${PROJECT_NAME}")
message(STATUS "Versión: ${PROJECT_VERSION}")
message(STATUS "Compilador: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "Sistema: ${CMAKE_SYSTEM_NAME}")
message(STATUS "========================================")

# Target personalizado para limpiar archivos de construcción
add_custom_target(clean-all
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/CMakeFiles
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/CMakeCache.txt
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/cmake_install.cmake
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/Makefile
    COMMENT "Limpiando todos los archivos de construcción"
)