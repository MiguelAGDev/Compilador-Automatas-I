#include "lexico.h"
#include <iostream>
#include <cstring>

using namespace std;

/* Constructor */
Lexico::Lexico() {
    i = startToken = inicialState = estadoActual = k = 0;
    buffer[0] = '\0';
}

void Lexico::initialize() {
    estadoActual = 0;
}

void Lexico::onFailure() {
    switch (estadoActual) {
    case 0:  estadoActual = 3;  i = startToken; break; // Grupo IDs
    case 3:  estadoActual = 6;  i = startToken; break; // Grupo Números
    case 6:  estadoActual = 11; i = startToken; break; // Grupo '=' (Asignación/Relacional)
    case 11: estadoActual = 15; i = startToken; break; // Grupo '!' (Diferente/Not)
    case 15: estadoActual = 19; i = startToken; break; // Grupo '>' (Mayor/Igual)
    case 19: estadoActual = 23; i = startToken; break; // Grupo '<' (Menor/Igual)
    case 23: estadoActual = 40; i = startToken; break; // Grupo '&&' (Lógico)
    case 40: estadoActual = 42; i = startToken; break; // Grupo '||' (Lógico)
    case 42: estadoActual = 27; i = startToken; break; // Grupo '+'
    case 27: estadoActual = 29; i = startToken; break; // Grupo '-'
    case 29: estadoActual = 31; i = startToken; break; // Grupo '*'
    case 31: estadoActual = 33; i = startToken; break; // Grupo '/'
    case 33: estadoActual = 34; i = startToken; break; // Grupo ';'
    case 34: estadoActual = 44; i = startToken; break; // Grupo Otros (Agrupadores/Comas)
    default:
        i = startToken + 1; // Error o desconocido, saltar char
        initialize();
        startToken = i;
        break;
    }
}

bool Lexico::isDelimiter(char c) { return (c == ' ' || c == '\t' || c == '\n' || c == '\r'); }
bool Lexico::isLetter(char c)    { return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')); }
bool Lexico::isDigit(char c)     { return (c >= '0' && c <= '9'); }

void Lexico::scanner(const char cadena[255]) {
    strncpy(buffer, cadena, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

    initialize();
    i = startToken = k = 0;
    size_t len = strlen(buffer);

    while (i <= (int)len) {
        char caracter = (i < (int)len ? buffer[i] : '\0');

        switch (estadoActual) {
        case 0:
            if (caracter == '\0') { strcpy(asTokens[k++], "$"); return; }
            if (isDelimiter(caracter)) { estadoActual = 1; i++; }
            else if (isLetter(caracter) || caracter == '_') { estadoActual = 3; i++; }
            else if (isDigit(caracter)) { estadoActual = 6; i++; }
            else if (caracter == '=') { estadoActual = 11; i++; }
            else if (caracter == '!') { estadoActual = 15; i++; }
            else if (caracter == '>') { estadoActual = 19; i++; }
            else if (caracter == '<') { estadoActual = 23; i++; }
            else if (caracter == '&') { estadoActual = 40; i++; }
            else if (caracter == '|') { estadoActual = 42; i++; }
            else if (caracter == '+') { estadoActual = 27; i++; }
            else if (caracter == '-') { estadoActual = 29; i++; }
            else if (caracter == '*') { estadoActual = 31; i++; }
            else if (caracter == '/') { estadoActual = 33; i++; }
            else if (caracter == ';') { estadoActual = 34; i++; }
            else if (strchr("()[]{},", caracter)) { estadoActual = 44; i++; }
            else onFailure();
            break;

        /* DELIMITADORES */
        case 1:
            if (isDelimiter(caracter)) i++;
            else {
                initialize();
                startToken = i;
            }
            break;

        /* IDENTIFICADORES Y RESERVADAS */
        case 3:
        case 4:
            if (isLetter(caracter) || isDigit(caracter) || caracter == '_') {
                estadoActual = 4; i++;
            } else {
                string lex(buffer + startToken, buffer + i);
                if (lex == "int" || lex == "float" || lex == "char" || lex == "bool" ||
                    lex == "string" || lex == "if" || lex == "else" || lex == "while" || lex == "for")
                    strcpy(asTokens[k++], lex.c_str());
                else
                    strcpy(asTokens[k++], "id");

                initialize(); startToken = i;
            }
            break;

        /* NUMEROS (Enteros y Reales) */
        case 6:
        case 7:
            if (isDigit(caracter)) { estadoActual = 7; i++; }
            else if (caracter == '.') { estadoActual = 9; i++; }
            else {
                strcpy(asTokens[k++], "num");
                initialize(); startToken = i;
            }
            break;

        case 9:
            if (isDigit(caracter)) {
                while (i < (int)len && isDigit(buffer[i])) i++;
                strcpy(asTokens[k++], "Real");
                initialize(); startToken = i;
            } else onFailure();
            break;

        /* GRUPO '=': Asignación, == o => */
        case 11:
            if (caracter == '=') { i++; strcpy(asTokens[k++], "=="); }
            else if (caracter == '>') { i++; strcpy(asTokens[k++], "=>"); }
            else { strcpy(asTokens[k++], "="); }
            initialize(); startToken = i;
            break;

        /* GRUPO '!': != */
        case 15:
            if (caracter == '=') { i++; strcpy(asTokens[k++], "!="); }
            else onFailure();
            initialize(); startToken = i;
            break;

        /* GRUPO '>': > o => (Ya cubierto en 11, pero por si acaso) */
        case 19:
            if (caracter == '=') { i++; strcpy(asTokens[k++], "=>"); }
            else { strcpy(asTokens[k++], ">"); }
            initialize(); startToken = i;
            break;

        /* GRUPO '<': < o =< */
        case 23:
            if (caracter == '=') { i++; strcpy(asTokens[k++], "=<"); }
            else { strcpy(asTokens[k++], "<"); }
            initialize(); startToken = i;
            break;

        /* LOGICOS: && y || */
        case 40:
            if (caracter == '&') { i++; strcpy(asTokens[k++], "&&"); }
            else onFailure();
            initialize(); startToken = i;
            break;

        case 42:
            if (caracter == '|') { i++; strcpy(asTokens[k++], "||"); }
            else onFailure();
            initialize(); startToken = i;
            break;

        /* ARITMETICOS Y SIMBOLOS */
        case 27: strcpy(asTokens[k++], "+"); initialize(); startToken = i; break;
        case 29: strcpy(asTokens[k++], "-"); initialize(); startToken = i; break;
        case 31: strcpy(asTokens[k++], "*"); initialize(); startToken = i; break;
        case 33: strcpy(asTokens[k++], "/"); initialize(); startToken = i; break;
        case 34: strcpy(asTokens[k++], ";"); initialize(); startToken = i; break;

        /* OTROS (Agrupadores y comas) */
        case 44: {
            string s(1, buffer[startToken]);
            strcpy(asTokens[k++], s.c_str());
            initialize(); startToken = i;
            break;
        }

        default: onFailure(); break;
        }
    }
}
