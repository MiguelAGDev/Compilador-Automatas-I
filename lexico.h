#ifndef LEXICO_H
#define LEXICO_H

#include <iostream>
#include <string>
#include <cstring>

using namespace std;

#define MAXTOKEN 500

class Lexico {
private:
    char buffer[255];   // Buffer para la cadena a analizar
    int i;              // Índice del carácter actual
    int startToken;     // Inicio del lexema actual
    int inicialState;   // Estado inicial del grupo
    int estadoActual;   // Estado actual del autómata
    int k;              // Índice para el arreglo asTokens

public:
    // Arreglo donde se guardan los nombres para la Tabla M
    char asTokens[MAXTOKEN][100];

    /* Constructor */
    Lexico();

    /* Métodos de control del autómata */
    void initialize();
    void onFailure();
    bool acceptanceState();

    /* Métodos de validación de caracteres */
    bool isDelimiter(char c);
    bool isLetter(char c);
    bool isDigit(char c);

    /* El motor del léxico */
    void scanner(const char cadena[255]);

    /* Getter para saber cuántos tokens se generaron */
    int getK() { return k; }
};

#endif // LEXICO_H
