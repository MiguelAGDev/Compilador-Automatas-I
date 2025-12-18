#ifndef ARCHIVOS_H
#define ARCHIVOS_H
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/**
 * @brief Clase archivos
 * Proporciona una abstracción para el manejo de archivos de texto,
 * permitiendo abrir, leer carácter por carácter y cerrar archivos
 * de forma controlada.
 */
class archivos
{
    /**
     * @brief archivoEntrada
     * Flujo de entrada utilizado para leer el contenido del archivo.
     */
    ifstream archivoEntrada;

    /**
     * @brief nombreArchivo
     * Almacena el nombre o la ruta completa del archivo a procesar.
     */
    string nombreArchivo;
public:
    /**
     * @brief Constructor de la clase archivos
     * Inicializa el objeto asignando el nombre o ruta del archivo
     * que se utilizará para la lectura.
     * @param nombre Nombre o ruta del archivo de entrada.
     */
    archivos(string nombre) : nombreArchivo(nombre) {}


    /**
     * @brief abrir
     * Intenta abrir el archivo asociado al objeto en modo lectura.
     * @return true si el archivo se abrió correctamente, false en caso contrario.
     */
    bool abrir(){
        archivoEntrada.open(nombreArchivo.c_str());
        if(!archivoEntrada.is_open()){
            cerr<<"Error: No se pudo abrir el arcivo \" "
                 << nombreArchivo <<"\""<<endl;
            return false;
        }

        return true;
    }

    /**
     * @brief cerra
     * Cierra el archivo de entrada si actualmente se encuentra abierto.
     */
    void cerra(){
        if(archivoEntrada.is_open())
            archivoEntrada.close();
    }


    /**
     * @brief leerCaracter
     * Obtiene el siguiente carácter disponible del archivo,
     * incluyendo espacios y saltos de línea.
     * @return El carácter leído o EOF si se alcanzó el final del archivo.
     */
    char leerCaracter() {
        char c;
        // Lectura directa del siguiente carácter del flujo
        if (archivoEntrada.get(c)) {
            return c;
        }
        return EOF;
    }

    /**
     * @brief finDeArchivo
     * Indica si el flujo de entrada ha alcanzado el final del archivo.
     * @return true si no quedan más datos por leer.
     */
    bool finDeArchivo() {
        return archivoEntrada.eof();
    }
};

#endif // ARCHIVOS_H
