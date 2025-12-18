#include <string>
#include "lexico.h"
#include "sintactico.h"
#include <iostream>

using namespace std;

int main() {
    Lexico lex;
    Sintactico sint;

    string entradaTotal;
    string linea;

    cout << "=== DEBUG: ANALIZADOR COMPLETO ===" << endl;

    while (true) {
        cout << "\n___________________________________________________" << endl;
        cout << "Introduce codigo en multiples lineas." << endl;
        cout << "Escribe '$' y Enter para ANALIZAR." << endl;
        cout << "Escribe '@' y Enter para SALIR." << endl;
        cout << "___________________________________________________" << endl;

        entradaTotal = ""; // Limpiamos la entrada anterior

        // --- BUCLE DE LECTURA MULTILÍNEA ---
        while (true) {
            getline(cin, linea);

            // 1. Checar si quiere salir del programa
            if (linea == "@") {
                cout << "Finalizando programa..." << endl;
                return 0;
            }

            // 2. Checar si quiere terminar el bloque y analizar
            if (linea == "$") {
                break; // Rompe el bucle de lectura y va a analizar
            }

            // 3. Si no es ni @ ni $, guardamos la línea
            // Agregamos un espacio para que no se peguen las palabras al dar enter
            entradaTotal += linea + " ";
        }

        if (!entradaTotal.empty()) {
            cout << "\n>>> Procesando bloque de codigo..." << endl;

            // --- EJECUCIÓN DEL LÉXICO ---
            lex.scanner(entradaTotal.c_str());

            cout << "\n[1] Resultado del Analisis Lexico:" << endl;
            int numTokens = lex.getK();

            for(int i = 0; i < numTokens; i++) {
                cout << "Token [" << i << "]: " << lex.asTokens[i] << endl;
            }

            // --- EJECUCIÓN DEL SINTÁCTICO ---
            cout << "\n[2] Resultado del Analisis Sintactico:" << endl;
            sint.ejecutar(lex.asTokens, numTokens);
        } else {
            cout << "Bloque vacio." << endl;
        }
    }

    return 0;
}
