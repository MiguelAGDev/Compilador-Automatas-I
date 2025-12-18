#ifndef SINTACTICO_H
#define SINTACTICO_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <stack>
#include "pila.h"

using namespace std;

/**
 * @brief Enumeración de símbolos terminales
 * Representa los terminales de la gramática,
 * utilizados como columnas en la tabla M del
 * analizador sintáctico predictivo.
 */
enum Terminales {
    T_ID, T_ASTERISCO, T_COMA, T_PUNTO_COMA, T_PAR_I, T_PAR_D,
    T_CORCH_I, T_CORCH_D, T_LLAVE_I, T_LLAVE_D, T_IF, T_ELSE,
    T_WHILE, T_FOR, T_INT, T_FLOAT, T_CHAR, T_BOOL, T_STRING,
    T_NUM, T_CTE_LIT, T_IGUAL, T_OR, T_AND, T_MENOR, T_MAYOR,
    T_IGUAL_IGUAL, T_DIFERENTE, T_PESOS, T_EPSILON,
    T_MAS, T_MENOS,
    T_ERROR
};

/**
 * @brief Enumeración de símbolos no terminales
 * Representa los no terminales de la gramática,
 * utilizados como filas en la tabla M.
 */
enum NoTerminales {
    NT_S = 100, NT_B, NT_C, NT_D, NT_T, NT_L, NT_L_PRIMA, NT_I,
    NT_I_PRIMA, NT_A, NT_A_PRIMA, NT_K, NT_J, NT_J_PRIMA,
    NT_W, NT_FR, NT_FI, NT_FC, NT_FA, NT_FA_PRIMA, NT_O, NT_O_PRIMA,
    NT_LOP, NT_R, NT_V, NT_OP,
};

/**
 * @brief Estructura Produccion
 * Modela una producción gramatical, almacenando
 * su identificador, el símbolo del lado izquierdo
 * y la secuencia de símbolos del lado derecho.
 */
struct Produccion {
    int id;
    int ladoIzquierdo;
    vector<int> ladoDerecho;

    /**
     * @brief Constructor de Produccion
     * Permite crear una producción indicando su id,
     * el no terminal del lado izquierdo y el conjunto
     * de símbolos del lado derecho.
     */
    Produccion(int _id=0, int _izq=0, vector<int> _der={})
        : id(_id), ladoIzquierdo(_izq), ladoDerecho(_der) {}
};

/**
 * @brief Clase Sintactico
 * Implementa un analizador sintáctico predictivo
 * basado en una pila, una tabla M y una gramática
 * previamente definida.
 */
class Sintactico {
private:
    /**
     * @brief miPila
     * Pila utilizada para el control del análisis sintáctico.
     */
    pila miPila;

    /**
     * @brief tablaM
     * Tabla predictiva M utilizada para decidir
     * qué producción aplicar durante el análisis.
     */
    int tablaM[30][40];

    /**
     * @brief gramatica
     * Conjunto de producciones de la gramática,
     * indexadas por su identificador.
     */
    map<int, Produccion> gramatica;

    /**
     * @brief tokenToEnum
     * Diccionario que convierte un token léxico
     * a su correspondiente símbolo terminal.
     */
    map<string, int> tokenToEnum;

    /**
     * @brief idToString
     * Diccionario inverso que asocia un identificador
     * de símbolo con su representación en texto.
     */
    map<int, string> idToString;

    /**
     * @brief inicializarDiccionarios
     * Inicializa los diccionarios de conversión
     * entre tokens y símbolos de la gramática.
     */
    void inicializarDiccionarios();

    /**
     * @brief configurarGramatica
     * Define las producciones de la gramática y
     * configura la tabla predictiva M.
     */
    void configurarGramatica();

public:
    /**
     * @brief Constructor de la clase Sintactico
     * Inicializa las estructuras necesarias para
     * ejecutar el análisis sintáctico.
     */
    Sintactico();

    /**
     * @brief ejecutar
     * Ejecuta el análisis sintáctico sobre la secuencia
     * de tokens generados por el analizador léxico.
     * @param asTokens Arreglo de tokens léxicos.
     * @param k Número total de tokens generados.
     */
    void ejecutar(char asTokens[500][100], int k);
};

#endif
