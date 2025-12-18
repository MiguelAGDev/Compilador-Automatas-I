#ifndef LEXICO_H
#define LEXICO_H

#include <iostream>
#include <string>
#include <cstring>

using namespace std;

#define MAXTOKEN 500

/**
 * @brief Clase Lexico
 * Implementa un analizador léxico basado en un autómata finito,
 * encargado de recorrer una cadena de entrada y generar los
 * tokens reconocidos durante el análisis.
 */
class Lexico {
private:
    /**
     * @brief buffer
     * Almacena la cadena de entrada que será analizada carácter por carácter.
     */
    char buffer[255];

    /**
     * @brief i
     * Índice del carácter actual que se está procesando en el buffer.
     */
    int i;

    /**
     * @brief startToken
     * Marca la posición inicial del lexema que se está construyendo.
     */
    int startToken;

    /**
     * @brief inicialState
     * Estado inicial del autómata para el reconocimiento de tokens.
     */
    int inicialState;

    /**
     * @brief estadoActual
     * Estado actual del autómata durante el proceso de análisis léxico.
     */
    int estadoActual;

    /**
     * @brief k
     * Contador e índice utilizado para almacenar los tokens generados.
     */
    int k;

public:
    /**
     * @brief asTokens
     * Arreglo que almacena los lexemas reconocidos, utilizado
     * posteriormente para la Tabla M.
     */
    char asTokens[MAXTOKEN][100];

    /**
     * @brief Constructor de la clase Lexico
     * Inicializa las variables internas necesarias para el
     * funcionamiento del analizador léxico.
     */
    Lexico();

    /**
     * @brief initialize
     * Inicializa o reinicia el autómata léxico y sus variables
     * de control antes de comenzar un nuevo análisis.
     */
    void initialize();

    /**
     * @brief onFailure
     * Maneja una transición inválida dentro del autómata,
     * reiniciando el análisis del token actual.
     */
    void onFailure();

    /**
     * @brief acceptanceState
     * Verifica si el estado actual del autómata es un estado de aceptación.
     * @return true si el token actual ha sido reconocido correctamente.
     */
    bool acceptanceState();

    /**
     * @brief isDelimiter
     * Determina si un carácter corresponde a un delimitador léxico.
     * @param c Carácter a evaluar.
     * @return true si el carácter es un delimitador.
     */
    bool isDelimiter(char c);

    /**
     * @brief isLetter
     * Verifica si un carácter es una letra del alfabeto.
     * @param c Carácter a evaluar.
     * @return true si el carácter es una letra.
     */
    bool isLetter(char c);

    /**
     * @brief isDigit
     * Verifica si un carácter es un dígito numérico.
     * @param c Carácter a evaluar.
     * @return true si el carácter es un dígito.
     */
    bool isDigit(char c);

    /**
     * @brief scanner
     * Ejecuta el análisis léxico sobre la cadena de entrada,
     * recorriéndola carácter por carácter y generando los tokens
     * reconocidos por el autómata.
     * @param cadena Cadena de entrada a analizar.
     */
    void scanner(const char cadena[255]);

    /**
     * @brief getK
     * Obtiene la cantidad total de tokens generados durante el análisis.
     * @return Número de tokens reconocidos.
     */
    int getK() { return k; }
};

#endif // LEXICO_H
