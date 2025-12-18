#ifndef PILA_H
#define PILA_H
#include <iostream>
#include <vector>
#include <string>
using namespace std;


/**
 * @class Pila
 * @brief Estructura de datos LIFO (Last In, First Out).
 * Clase utilizada para el analisis sintactico. Sistuye a las
 * clases pilas existentes permitiendonos y moldear el codigo
 * a nuestras necesidads
 */
class pila
{

    /**
     * @var vector<string> elementos
     * @brief Variable que contiene los tokens y simbolos terminales y
     * no terminales. Usa un vector para evitar la declaracion de un tope
     */
    vector<string> elementos;

public:
    /**
     * @brief constructor
     */
    pila(){};

    /**
     * @brief isEmpty Verifica si la pila esta vacia
     * @return Si la pila contiene almenos un elemntro retorna false.
     */
    bool isEmpty(){
        return elementos.empty();
    }

    /**
     * @brief push inserta elementos a la pila
     * @param elem string a insertar (Vn o Vt)
     */
    void push(string elem){
        elementos.push_back(elem);
    }

    /**
     * @brief pop elimina el elemento del top
     */
    void pop() {
        if (!elementos.empty()) {
            elementos.pop_back();
        }
    }
    /**
     * @brief top Obtiene el elemnto actual sin eliminarlo
     * @return regresa el elemetro superior. Si no existe, regresa
     * una cadena vacia
     */
    string top() {
        if (elementos.size() >= 0) return string(elemetos.to);
        return "";
    }

    /**
     * @brief mostrar Imprime el contenido actual de la pila
     * @return retorna una cadeena con todo los elementos de la ial
     */
    string mostrar(){
        string pila = "";
        for (int i = elementos.size() - 1; i >= 0; --i) {
            string actual = elementos[i];

            if(actual == " ")
                pila += "ε";
            else
                pila += actual + " ";
        }

        return pila;
    }

};

#endif // PILA_H
