#ifndef SINTACTICO_H
#define SINTACTICO_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <stack>
#include "pila.h"

using namespace std;

// --- TERMINALES (Columnas del Excel) ---
enum Terminales {
    T_ID, T_ASTERISCO, T_COMA, T_PUNTO_COMA, T_PAR_I, T_PAR_D,
    T_CORCH_I, T_CORCH_D, T_LLAVE_I, T_LLAVE_D, T_IF, T_ELSE,
    T_WHILE, T_FOR, T_INT, T_FLOAT, T_CHAR, T_BOOL, T_STRING,
    T_NUM, T_CTE_LIT, T_IGUAL, T_OR, T_AND, T_MENOR, /*T_MAYOR_IGUAL,/*
    /*T_MENOR_IGUAL*/ T_MAYOR, T_IGUAL_IGUAL, T_DIFERENTE,
    T_PESOS,
    T_EPSILON, // <-- Para reglas vacías
    T_ERROR
};

// --- NO TERMINALES (Filas del Excel) ---
enum NoTerminales {
    NT_S = 100, NT_B, NT_C, NT_D, NT_T, NT_L, NT_L_PRIMA, NT_I,
    NT_I_PRIMA, NT_A, NT_A_PRIMA, NT_K, NT_J, NT_J_PRIMA,
    NT_W, NT_FR, NT_FI, NT_FC, NT_FA, NT_O, NT_O_PRIMA,
    NT_LOP, NT_R, NT_V, NT_OP
};

struct Produccion {
    int id;
    int ladoIzquierdo;
    vector<int> ladoDerecho;

    // Constructor para que acepte la sintaxis {id, izq, {der}}
    Produccion(int _id=0, int _izq=0, vector<int> _der={})
        : id(_id), ladoIzquierdo(_izq), ladoDerecho(_der) {}
};

class Sintactico {
private:
    pila miPila;
    int tablaM[30][40];
    map<int, Produccion> gramatica;
    map<string, int> tokenToEnum;
    map<int, string> idToString;

    void inicializarDiccionarios();
    void configurarGramatica();

public:
    Sintactico(); // Constructor normal de consola
    void ejecutar(char asTokens[500][100], int k);
};

#endif
