#include "sintactico.h"
#include <iostream>
#include <iomanip>

using namespace std;

Sintactico::Sintactico(QWidget *parent) : QWidget(parent) {
    inicializarDiccionarios();
    configurarGramatica();
}

Sintactico::~Sintactico() {
}

void Sintactico::inicializarDiccionarios() {
    // Mapeo de strings (Léxico) -> Enums (Terminales)
    tokenToEnum["id"] = T_ID;         tokenToEnum["*"] = T_ASTERISCO;
    tokenToEnum[","] = T_COMA;       tokenToEnum[";"] = T_PUNTO_COMA;
    tokenToEnum["("] = T_PAR_I;       tokenToEnum[")"] = T_PAR_D;
    tokenToEnum["["] = T_CORCH_I;     tokenToEnum["]"] = T_CORCH_D;
    tokenToEnum["{"] = T_LLAVE_I;     tokenToEnum["}"] = T_LLAVE_D;
    tokenToEnum["if"] = T_IF;         tokenToEnum["else"] = T_ELSE;
    tokenToEnum["while"] = T_WHILE;   tokenToEnum["for"] = T_FOR;
    tokenToEnum["int"] = T_INT;       tokenToEnum["float"] = T_FLOAT;
    tokenToEnum["char"] = T_CHAR;     tokenToEnum["bool"] = T_BOOL;
    tokenToEnum["string"] = T_STRING; tokenToEnum["num"] = T_NUM;
    tokenToEnum["Cte.Lit"] = T_CTE_LIT; tokenToEnum["="] = T_IGUAL;
    tokenToEnum["||"] = T_OR;         tokenToEnum["&&"] = T_AND;
    tokenToEnum["<"] = T_MENOR;       tokenToEnum[">"] = T_MAYOR;
    tokenToEnum["=>"] = T_MAYOR_IGUAL; tokenToEnum["=<"] = T_MENOR_IGUAL;
    tokenToEnum["=="] = T_IGUAL_IGUAL; tokenToEnum["!="] = T_DIFERENTE;
    tokenToEnum["Real"] = T_REAL;     tokenToEnum["$"] = T_PESOS;

    // Diccionario inverso para impresión y logs
    for (auto const& [key, val] : tokenToEnum) idToString[val] = key;

    idToString[NT_S] = "S"; idToString[NT_B] = "B"; idToString[NT_C] = "C";
    idToString[NT_D] = "D"; idToString[NT_T] = "T"; idToString[NT_L] = "L";
    idToString[NT_L_PRIMA] = "L'"; idToString[NT_I] = "I"; idToString[NT_I_PRIMA] = "I'";
    idToString[NT_A] = "A"; idToString[NT_A_PRIMA] = "A'"; idToString[NT_K] = "K";
    idToString[NT_J] = "J"; idToString[NT_J_PRIMA] = "J'"; idToString[NT_W] = "W";
    idToString[NT_FR] = "FR"; idToString[NT_FI] = "FI"; idToString[NT_FC] = "FC";
    idToString[NT_FA] = "FA"; idToString[NT_O] = "O"; idToString[NT_O_PRIMA] = "O'";
    idToString[NT_LOP] = "LOP"; idToString[NT_R] = "R"; idToString[NT_V] = "V";
    idToString[NT_OP] = "Op";
}

void Sintactico::configurarGramatica() {
    // Inicializar Tabla M con 999 (Error)
    for(int i=0; i<25; i++) for(int j=0; j<32; j++) tablaM[i][j] = 999;

    // --- DEFINICIÓN DE REGLAS (Lado Derecho ya está INVERTIDO para la pila) ---
    // S -> D | J | W | FR
    gramatica[1] = {1, NT_S, {NT_D}};
    gramatica[2] = {2, NT_S, {NT_J}};
    gramatica[3] = {3, NT_S, {NT_W}};
    gramatica[4] = {4, NT_S, {NT_FR}};
    // B -> { C }
    gramatica[5] = {5, NT_B, {T_LLAVE_D, NT_C, T_LLAVE_I}};
    // C -> S C | e
    gramatica[6] = {6, NT_C, {NT_C, NT_S}};
    gramatica[7] = {7, NT_C, {"e"}}; // Epsilon
    // D -> T L ;
    gramatica[8] = {8, NT_D, {T_PUNTO_COMA, NT_L, NT_T}};
    // T -> int | float | char | bool | string
    gramatica[9] = {9, NT_T, {T_INT}};
    gramatica[10] = {10, NT_T, {T_FLOAT}};
    gramatica[11] = {11, NT_T, {T_CHAR}};
    gramatica[12] = {12, NT_T, {T_BOOL}};
    gramatica[13] = {13, NT_T, {T_STRING}};
    // L -> I L' | L' -> , I L' | e
    gramatica[14] = {14, NT_L, {NT_L_PRIMA, NT_I}};
    gramatica[15] = {15, NT_L_PRIMA, {NT_L_PRIMA, NT_I, T_COMA}};
    gramatica[16] = {16, NT_L_PRIMA, "e"};
    // I -> id I' | * id I'
    gramatica[17] = {17, NT_I, {NT_I_PRIMA, T_ID}};
    gramatica[18] = {18, NT_I, {NT_I_PRIMA, T_ID, T_ASTERISCO}};
    // J -> if ( O ) B J'
    gramatica[26] = {26, NT_J, {NT_J_PRIMA, NT_B, T_PAR_D, NT_O, T_PAR_I, T_IF}};
    // Op -> < | > | == | !=
    gramatica[47] = {47, NT_OP, {T_MENOR}};
    gramatica[48] = {48, NT_OP, {T_MAYOR}};
    gramatica[49] = {49, NT_OP, {T_IGUAL_IGUAL}};
    gramatica[50] = {50, NT_OP, {T_DIFERENTE}};

    // --- LLENADO DE TABLA M [NoTerminal - 100][Terminal] ---
    // S
    tablaM[NT_S-100][T_INT] = 1; tablaM[NT_S-100][T_FLOAT] = 1;
    tablaM[NT_S-100][T_IF] = 2;  tablaM[NT_S-100][T_WHILE] = 3;
    tablaM[NT_S-100][T_FOR] = 4;
    // D
    tablaM[NT_D-100][T_INT] = 8; tablaM[NT_D-100][T_FLOAT] = 8;
    // T
    tablaM[NT_T-100][T_INT] = 9; tablaM[NT_T-100][T_FLOAT] = 10;
    // ... completar con el resto de tu Excel ...
}

void Sintactico::ejecutar(char asTokens[500][100], int k) {
    int ip = 0;
    miPila.pop();
    miPila.push("$");
    miPila.push("S");

    cout << "\n>>> ANALISIS SINTACTICO POR CONSOLA <<<" << endl;
    cout << "------------------------------------------------" << endl;

    while(true) {
        string X = miPila.top(); // Asumiendo que agregaste top() a tu clase Pila
        string a = asTokens[ip];

        int idX = -1;
        if(X == "S") idX = NT_S;
        else if(X == "D") idX = NT_D;
        else if(X == "T") idX = NT_T;
        else if(tokenToEnum.count(X)) idX = tokenToEnum[X];

        int idA = tokenToEnum.count(a) ? tokenToEnum[a] : T_ERROR;

        if (idX < 100 || idX == T_PESOS) { // TERMINAL
            if (X == a) {
                cout << "Match: " << a << endl;
                miPila.pop();
                ip++;
                if (X == "$") {
                    cout << "COMPILACION EXITOSA." << endl;
                    break;
                }
            } else {
                cout << "ERROR: Se esperaba " << X << " pero se encontro " << a << endl;
                break;
            }
        } else { // NO TERMINAL
            int numRegla = tablaM[idX - 100][idA];
            if (numRegla != 999) {
                miPila.pop();
                Produccion p = gramatica[numRegla];

                // Meter a la pila (ya invertidos en configurarGramatica)
                for (auto simbolo : p.ladoDerecho) {
                    string sNom = (simbolo >= 100) ? idToString[simbolo] : idToString[simbolo];
                    if (sNom != "e") miPila.push(sNom);
                }
                cout << "Regla " << numRegla << ": " << idToString[idX] << " aplicada." << endl;
            } else {
                cout << "ERROR SINTACTICO en token: " << a << endl;
                break;
            }
        }
    }
}
