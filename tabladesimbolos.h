#ifndef TABLADESIMBOLOS_H
#define TABLADESIMBOLOS_H

#include <iostream>
#include <string>
#include <vector>
#include <iomanip> // Para setw
using namespace std;


/// Define el aliias para tipe de valor
typedef int SymValue;


/**
 * @struct Symbol
 * @brief Nodo que representa una variable en la tabla
 */
struct Symbol{

    string nombre; // Cambiando a string para compatibilidad con la pila
    SymValue valor; // Valor o Tipo (int, float, etc)
    Symbol *next; // Puntero para encadeamiento

    // Constructor del nodo para facilitar la insercion
    Symbol(string n, SymValue v, Symbol *x) : nombre(n), valor(v), next(x) {};
};


/**
 * @class Tabla de Simbolos
 * @brief Gestionar las variable de programa mediante una Tabla Hash
 * Permite agregar, buscar y eliminar simbolos, manejando
 */
class tablaDeSimbolos
{

    /**
     * @var Symbol **tabla
     * @brief Arreglo de punteros a simbolos
     */
    Symbol **tabla;

    /**
     * @var int size
     * @brief Tamaño de la tabla hash
     */
    int size;


    /**
     * @brief hash
     * Generea el indice basado en las uma de carcateres del nombre
     * @param clave Nombre de la variable
     * @return int Indice donde se almacena
     */
    int hash(string clave){
        int slot = 0;

        // Por cada character del string
        for (char c: clave) {
            // Se suma en el slot
            slot += c;
        }

        // Retorna el slod mdulo tamano del hash (numero primo)
        return slot % size;

    }

 public:


     /**
      * @brief Constructor
      * @param int Tamano de la tabla, que se inicialzia
      * con 7 por default
      */
     tablaDeSimbolos(int tam = 7){
         size = tam;
         tabla = new Symbol *[size];

         for (int i = 0; i < size; i++) {
             tabla[i] = nullptr;
         }
     };

     /**
      * @brief Destructor
      * Libera toda la memoria reservada al destruir el objeto
      */

     ~tablaDeSimbolos(){

         for (int i = 0; i < size; ++i) {
             Symbol *actual = tabla[i];

             while (actual != nullptr) {
                 Symbol *aBorrar = actual;
                 actual = actual->next;
                 delete aBorrar;
             }
         }

         delete []tabla;
     }

     /**
      * @brief addSym
      * Agrega un simbolo a la tabla
      * @param variable Nombre del identificador
      * @param valor Valor asociado (o tipo)
      * @return Puntero al simbolo creado
      */
     Symbol *addSym(string variable, SymValue valor){

         int indice = hash(variable);

         // Creamos el nuevo y lo ponemos al principo (LIFO en colision)
         Symbol *nuevo = new Symbol(variable, valor, tabla[indice]);

         // Se actualiza la posicion 'indice'
         tabla[indice] = nuevo;

         // Devuelve el puntero al simbolo recien creado
         return nuevo;
     }

     /**
      * @brief findSym
      * Elimina un simbolo de la tabla
      * @param string variable  Nombre a buscar
      * @return true si se lo econtro,  nullptr si no.
      */
     Symbol *findSym(string variable){

         int indice = hash(variable);

         Symbol *simbolo = tabla[indice];

         while( simbolo != nullptr){
             if(simbolo->nombre == variable)
                 return simbolo;

             simbolo = simbolo->next;
         }

         return nullptr;
     }


     /**
      * @brief deleteSym
      * Elimina el simbolo del hash.
      * @param variable String del dato abuscar
      * @return True si lo elimino, false sino.
      */
     bool deleteSym(string variable){

         int indice = hash(variable);
         Symbol *actual = tabla[indice];
         Symbol *anterior = nullptr;

         while(actual != nullptr){

             if(actual->nombre == variable){
                 // Si es el primero de la lista
                 if(anterior == nullptr){
                     tabla[indice] = actual->next;
                 } else {
                     anterior->next = actual->next;
                 }

                 delete actual;
                 return true;

             }// fin if


         }// fin while

         return false;

     }

     /**
     * @brief getTablaSimbolos
     * Extrae los datos de la tabla hash y los organiza en una matriz de strings.
     * Este método es el puente entre la lógica del compilador y la interfaz gráfica (GUI),
     * permitiendo que un componente como QTableWidget o JTable muestre los datos.
     * * @return vector<vector<string>> Matriz donde cada fila contiene:
     * [0] Dirección de memoria del símbolo.
     * [1] Nombre del identificador.
     * [2] Valor actual en formato hexadecimal.
     * [3] Dirección de memoria del siguiente nodo (colisión).
     */
     vector<vector<string>> getTablaSimbolos() {
         vector<vector<string>> tablaLogica;

         for (int i = 0; i < size; ++i) {
             Symbol *simbolo = tabla[i];

             while (simbolo != nullptr) {
                 vector<string> fila;
                 stringstream ss;

                 // Columna 0: dirección del símbolo
                 ss << hex << simbolo;
                 fila.push_back(ss.str());
                 ss.str(""); ss.clear();

                 // Columna 1: nombre
                 fila.push_back(simbolo->nombre);

                 // Columna 2: valor en hexadecimal
                 ss << hex << simbolo->valor;
                 fila.push_back(ss.str());
                 ss.str(""); ss.clear();

                 // Columna 3: dirección del next
                 ss << hex << simbolo->next;
                 fila.push_back(ss.str());

                 tablaLogica.push_back(fila);

                 simbolo = simbolo->next;
             }
         }

         return tablaLogica;
     }




};

#endif // TABLADESIMBOLOS_H
