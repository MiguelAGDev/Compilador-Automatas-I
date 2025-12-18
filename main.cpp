#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <fstream> // Para escritura (ofstream)

// Tus clases
#include "archivos.h"
#include "lexico.h"
#include "sintactico.h"

using namespace std;

// --- FUNCIÓN PARA GENERAR ARCHIVO (MODO ESCRITURA) ---
void generarArchivo() {
    string nombre;
    char car;

    // 1. Pedir nombre
    cout << "\nNombre del archivo a crear (sin extension): ";
    if(cin.peek() == '\n') cin.ignore(); // Limpiar buffer
    getline(cin, nombre);

    string nombreCompleto = nombre + ".dat";
    ofstream archivoSalida(nombreCompleto.c_str());

    if (archivoSalida.is_open()) {
        cout << "---------------------------------------------------" << endl;
        cout << "Escribe el codigo a continuacion." << endl;
        cout << "Presiona '@' y Enter al final para GUARDAR y SALIR." << endl;
        cout << "---------------------------------------------------" << endl;

        // 2. Ciclo de lectura caracter por caracter hasta encontrar '@'
        do {
            car = cin.get();

            if (car == '@') {
                break; // Salir del ciclo si es el delimitador
            }

            // Escribimos el caracter en el archivo
            archivoSalida.put(car);

        } while (true);

        archivoSalida.close();
        cout << "\n>>> Archivo " << nombreCompleto << " guardado exitosamente. <<<" << endl;
    } else {
        cout << "Error: No se pudo crear el archivo." << endl;
    }
}

int main() {
    Lexico lex;
    Sintactico sint;
    char resp;

    do {
        cout << "\n========================================" << endl;
        cout << "       MENU ANALIZADOR COMPLETO        " << endl;
        cout << "========================================" << endl;

        // ---------------------------------------------------------
        // 1. GENERAR ARCHIVO
        // ---------------------------------------------------------
        cout << "\nDesea Generar un archivo nuevo? (s/n): ";
        cin >> resp;

        if (strchr("Ss", resp)) {
            generarArchivo();
        }

        // ---------------------------------------------------------
        // 2. ABRIR Y ANALIZAR
        // ---------------------------------------------------------
        cout << "\nDesea Abrir un archivo para analizarlo? (s/n): ";
        cin >> resp;

        if (strchr("Ss", resp)) {
            string nombre;
            cout << "\nNombre del Archivo a ABRIR (sin extension): ";
            if(cin.peek() == '\n') cin.ignore();
            getline(cin, nombre);

            string nombreCompleto = nombre + ".dat";

            // Usamos TU CLASE archivos para lectura
            archivos miArchivo(nombreCompleto);

            if (miArchivo.abrir()) {
                cout << ">> EL ARCHIVO SE ENCUENTRA ABIERTO <<" << endl;

                // Leer contenido completo a memoria
                string contenidoTotal = "";
                char c;
                while ((c = miArchivo.leerCaracter()) != EOF) {
                    contenidoTotal += c;
                }
                miArchivo.cerra(); // Tu método se llama 'cerra'

                if (contenidoTotal.empty()) {
                    cout << "El archivo esta vacio." << endl;
                } else {
                    // --- A) ANÁLISIS LÉXICO ---
                    lex.scanner(contenidoTotal.c_str());

                    cout << "\n[1] Resultado del Analisis Lexico:" << endl;
                    int numTokens = lex.getK();
                    for(int i = 0; i < numTokens; i++) {
                        cout << "Token [" << i << "]: " << lex.asTokens[i] << endl;
                    }

                    // Pausa para ver resultados léxicos
                    cout << "\nPresiona Enter para ver las Producciones (Sintactico)...";
                    cin.get();

                    // --- B) ANÁLISIS SINTÁCTICO ---
                    cout << "\n[2] Resultado del Analisis Sintactico:" << endl;
                    sint.ejecutar(lex.asTokens, numTokens);
                }

            } else {
                // Si falla al abrir (el mensaje lo da tu clase archivos)
                cout << "Presiona Enter para continuar..." << endl;
                cin.get();
            }
        }

        // ---------------------------------------------------------
        // 3. CONTINUAR
        // ---------------------------------------------------------
        cout << "\nPresiona (sS) para continuar con otro proceso? : ";
        cin >> resp;

    } while (strchr("Ss", resp));

    cout << "\nSaliendo del programa..." << endl;
    return 0;
}
