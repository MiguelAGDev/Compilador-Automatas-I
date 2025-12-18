#include <iostream>
#include <string>
#include "lexico.h"
#include "sintactico.h"

using namespace std;

int main() {
    // 1. Instanciamos con los nombres exactos de tus clases
    Lexico lex;
    Sintactico sint;

    string entrada;

    cout << "=== DEBUG: ANALIZADOR COMPLETO ===" << endl;
    cout << "Introduce el codigo a analizar (ejemplo: int id;):" << endl;

    // Leemos la línea completa
    getline(cin, entrada);

    if (!entrada.empty()) {
        // 2. EJECUCIÓN DEL LÉXICO
        // En tu lexico.cpp, el motor es 'scanner(const char cadena[255])'
        lex.scanner(entrada.c_str());

        cout << "\n[1] Resultado del Analisis Lexico:" << endl;
        int numTokens = lex.getK(); // Usamos tu getter

        for(int i = 0; i < numTokens; i++) {
            cout << "Token [" << i << "]: " << lex.asTokens[i] << endl;
        }

        // 3. EJECUCIÓN DEL SINTÁCTICO
        // Tu método 'analizar' recibe el arreglo de tokens:
        // void analizar(char tokens[][100], int n);
        cout << "\n[2] Resultado del Analisis Sintactico:" << endl;
        sint.ejecutar(lex.asTokens, numTokens);
    } else {
        cout << "Entrada vacia." << endl;
    }

    cout << "\nPresiona Enter para salir..." << endl;
    cin.get();

    return 0;
}
