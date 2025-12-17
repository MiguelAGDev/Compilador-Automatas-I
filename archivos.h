#ifndef ARCHIVOS_H
#define ARCHIVOS_H
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/**
 * @brief The archivos class
 * Gestiona la lectura de archivos. Encapsula, lectura de
 * caracter por caracter, cierra del archivo.
 */
class archivos
{
    /**
     * @brief archivoEntrada
     * Flujo de lectura del archivo
     */
    ifstream archivoEntrada;

    /**
     * @brief nombreArchivo
     * ruta del archivo
     */
    string nombreArchivo;
public:
    /**
     * @brief Constructor de la clase archivos.
     * Inicializa un objeto de la clase archivos asignando
     * el nombre o ruta del archivo que será utilizado.
     * @param nombre Cadena que representa el nombre o la ruta del archivo.
     */
    archivos(string nombre) : nombreArchivo(nombre) {}


    /**
     * @brief abrir Abre el archivo en modo lectura
     * @return bool retorna si la accion de arbrir el archivo se produjo
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
     * @brief cerra Cierra el archivo si esta abierto
     */
    void cerra(){
        if(archivoEntrada.is_open())
            archivoEntrada.close();
    }


    /**
     * @brief leerCaracter lee el siguiente caracter del archivo
     * @return char El caracter leido o EOF si llego al final.
     */
    char leerCaracter() {
        char c;
        // get() lee incluyendo espacios y saltos de linea
        if (archivoEntrada.get(c)) {
            return c;
        }
        return EOF;
    }

    /**
     * @brief Verifica fin de archivo
     * @return true si ya no hay mas datos.
     */
    bool finDeArchivo() {
        return archivoEntrada.eof();
    }
};

#endif // ARCHIVOS_H
