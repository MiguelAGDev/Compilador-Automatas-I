#include "sintactico.h"
#include <iomanip>
#include <vector>

Sintactico::Sintactico() {
    inicializarDiccionarios();
    configurarGramatica();
}

void Sintactico::inicializarDiccionarios() {
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
    tokenToEnum["=="] = T_IGUAL_IGUAL; tokenToEnum["!="] = T_DIFERENTE;
    tokenToEnum["+"] = T_MAS;   tokenToEnum["-"] = T_MENOS;
    tokenToEnum["$"] = T_PESOS;

    // Llenamos el mapa inverso para imprimir nombres de TERMINALES
    for (auto const& [key, val] : tokenToEnum) idToString[val] = key;

    // Llenamos nombres de NO TERMINALES
    idToString[NT_S] = "S"; idToString[NT_B] = "B"; idToString[NT_C] = "C";
    idToString[NT_D] = "D"; idToString[NT_T] = "T"; idToString[NT_L] = "L";
    idToString[NT_L_PRIMA] = "L'"; idToString[NT_I] = "I"; idToString[NT_I_PRIMA] = "I'";
    idToString[NT_A] = "A"; idToString[NT_A_PRIMA] = "A'"; idToString[NT_K] = "K";
    idToString[NT_J] = "J"; idToString[NT_J_PRIMA] = "J'"; idToString[NT_W] = "W";
    idToString[NT_FR] = "FR"; idToString[NT_FI] = "FI"; idToString[NT_FC] = "FC";
    idToString[NT_FA] = "FA"; idToString[NT_FA_PRIMA] = "FA'";
    idToString[NT_O] = "O"; idToString[NT_O_PRIMA] = "O'";
    idToString[NT_LOP] = "LOP"; idToString[NT_R] = "R"; idToString[NT_V] = "V";
    idToString[NT_OP] = "Op";
}

void Sintactico::configurarGramatica() {
    for(int i=0; i<30; i++) for(int j=0; j<40; j++) tablaM[i][j] = 999;

    // --- DEFINICIÓN DE PRODUCCIONES ---

    // S -> D | J | W | FR
    gramatica[1] = Produccion(1, NT_S, {NT_D});
    gramatica[2] = Produccion(2, NT_S, {NT_J});
    gramatica[3] = Produccion(3, NT_S, {NT_W});
    gramatica[4] = Produccion(4, NT_S, {NT_FR});

    // B -> { C }
    gramatica[5] = Produccion(5, NT_B, {T_LLAVE_D, NT_C, T_LLAVE_I});

    // C -> S C | e
    gramatica[6] = Produccion(6, NT_C, {NT_C, NT_S});
    gramatica[7] = Produccion(7, NT_C, {T_EPSILON});

    // D -> T L ;
    gramatica[8] = Produccion(8, NT_D, {T_PUNTO_COMA, NT_L, NT_T});

    // T -> int | float | char | bool | string
    gramatica[9]  = Produccion(9,  NT_T, {T_INT});
    gramatica[10] = Produccion(10, NT_T, {T_FLOAT});
    gramatica[11] = Produccion(11, NT_T, {T_CHAR});
    gramatica[12] = Produccion(12, NT_T, {T_BOOL});
    gramatica[13] = Produccion(13, NT_T, {T_STRING});

    // L -> I L'
    gramatica[14] = Produccion(14, NT_L, {NT_L_PRIMA, NT_I});
    // L' -> , I L' | e
    gramatica[15] = Produccion(15, NT_L_PRIMA, {NT_L_PRIMA, NT_I, T_COMA});
    gramatica[16] = Produccion(16, NT_L_PRIMA, {T_EPSILON});

    // I -> id I' | * id I'
    gramatica[17] = Produccion(17, NT_I, {NT_I_PRIMA, T_ID});
    gramatica[18] = Produccion(18, NT_I, {NT_I_PRIMA, T_ID, T_ASTERISCO});

    // I' -> A I' | e
    gramatica[19] = Produccion(19, NT_I_PRIMA, {NT_I_PRIMA, NT_A});
    gramatica[20] = Produccion(20, NT_I_PRIMA, {T_EPSILON});

    // A -> [ K ]
    gramatica[21] = Produccion(21, NT_A, {T_CORCH_D, NT_K, T_CORCH_I});

    // A' -> [ K ] A' | e
    gramatica[22] = Produccion(22, NT_A_PRIMA, {NT_A_PRIMA, T_CORCH_D, NT_K, T_CORCH_I});
    gramatica[23] = Produccion(23, NT_A_PRIMA, {T_EPSILON});

    // K -> id | num
    gramatica[24] = Produccion(24, NT_K, {T_ID});
    gramatica[25] = Produccion(25, NT_K, {T_NUM});

    // J -> if ( O ) B J'
    gramatica[26] = Produccion(26, NT_J, {NT_J_PRIMA, NT_B, T_PAR_D, NT_O, T_PAR_I, T_IF});
    // J' -> else B | e
    gramatica[27] = Produccion(27, NT_J_PRIMA, {NT_B, T_ELSE});
    gramatica[28] = Produccion(28, NT_J_PRIMA, {T_EPSILON});

    // W -> while ( O ) B
    gramatica[29] = Produccion(29, NT_W, {NT_B, T_PAR_D, NT_O, T_PAR_I, T_WHILE});

    // FR -> for ( FI ; FC ; FA ) B
    gramatica[30] = Produccion(30, NT_FR, {NT_B, T_PAR_D, NT_FA, T_PUNTO_COMA, NT_FC, T_PUNTO_COMA, NT_FI, T_PAR_I, T_FOR});

    // FI -> L T | id = V | e
    gramatica[31] = Produccion(31, NT_FI, {NT_L, NT_T});
    gramatica[32] = Produccion(32, NT_FI, {NT_V, T_IGUAL, T_ID});
    gramatica[33] = Produccion(33, NT_FI, {T_EPSILON});

    // FC -> O | e
    gramatica[34] = Produccion(34, NT_FC, {NT_O});
    gramatica[35] = Produccion(35, NT_FC, {T_EPSILON});

    // FA -> id FA' | ++ id | -- id | e
    gramatica[36] = Produccion(36, NT_FA, {NT_FA_PRIMA, T_ID});
    gramatica[37] = Produccion(37, NT_FA, {T_EPSILON});
    gramatica[52] = Produccion(52, NT_FA, {T_ID, T_MAS, T_MAS});
    gramatica[56] = Produccion(56, NT_FA, {T_ID, T_MENOS, T_MENOS});

    // FA' -> ++ | -- | = V | e
    gramatica[53] = Produccion(53, NT_FA_PRIMA, {T_MAS, T_MAS});
    gramatica[54] = Produccion(54, NT_FA_PRIMA, {T_MENOS, T_MENOS});
    gramatica[51] = Produccion(51, NT_FA_PRIMA, {NT_V, T_IGUAL});
    gramatica[55] = Produccion(55, NT_FA_PRIMA, {T_EPSILON});

    // O -> R O'
    gramatica[38] = Produccion(38, NT_O, {NT_O_PRIMA, NT_R});
    // O' -> LOP R O' | e
    gramatica[39] = Produccion(39, NT_O_PRIMA, {NT_O_PRIMA, NT_R, NT_LOP});
    gramatica[40] = Produccion(40, NT_O_PRIMA, {T_EPSILON});

    // LOP -> && | ||
    gramatica[41] = Produccion(41, NT_LOP, {T_AND});
    gramatica[42] = Produccion(42, NT_LOP, {T_OR});

    // R -> V Op V
    gramatica[43] = Produccion(43, NT_R, {NT_V, NT_OP, NT_V});

    // V -> id | num | Cte.Lit
    gramatica[44] = Produccion(44, NT_V, {T_ID});
    gramatica[45] = Produccion(45, NT_V, {T_NUM});
    gramatica[46] = Produccion(46, NT_V, {T_CTE_LIT});

    // Op -> < | > | == | !=
    gramatica[47] = Produccion(47, NT_OP, {T_MENOR});
    gramatica[48] = Produccion(48, NT_OP, {T_MAYOR});
    gramatica[49] = Produccion(49, NT_OP, {T_IGUAL_IGUAL});
    gramatica[50] = Produccion(50, NT_OP, {T_DIFERENTE});


    // ============================================================
    // LLENADO DE LA TABLA M
    // ============================================================

    // NT_S
    tablaM[NT_S-100][T_IF] = 2;
    tablaM[NT_S-100][T_WHILE] = 3; tablaM[NT_S-100][T_FOR] = 4;
    tablaM[NT_S-100][T_INT] = 1; tablaM[NT_S-100][T_FLOAT] = 1; tablaM[NT_S-100][T_CHAR] = 1;
    tablaM[NT_S-100][T_BOOL] = 1; tablaM[NT_S-100][T_STRING] = 1;

    // NT_B
    tablaM[NT_B-100][T_LLAVE_I] = 5;

    // NT_C
    tablaM[NT_C-100][T_ID] = 6; tablaM[NT_C-100][T_IF] = 6; tablaM[NT_C-100][T_WHILE] = 6;
    tablaM[NT_C-100][T_FOR] = 6; tablaM[NT_C-100][T_INT] = 6; tablaM[NT_C-100][T_FLOAT] = 6;
    tablaM[NT_C-100][T_CHAR] = 6; tablaM[NT_C-100][T_BOOL] = 6; tablaM[NT_C-100][T_STRING] = 6;
    tablaM[NT_C-100][T_LLAVE_D] = 7; tablaM[NT_C-100][T_PESOS] = 7;

    // NT_D
    tablaM[NT_D-100][T_INT] = 8; tablaM[NT_D-100][T_FLOAT] = 8; tablaM[NT_D-100][T_CHAR] = 8;
    tablaM[NT_D-100][T_BOOL] = 8; tablaM[NT_D-100][T_STRING] = 8;

    // NT_T
    tablaM[NT_T-100][T_INT] = 9; tablaM[NT_T-100][T_FLOAT] = 10; tablaM[NT_T-100][T_CHAR] = 11;
    tablaM[NT_T-100][T_BOOL] = 12; tablaM[NT_T-100][T_STRING] = 13;

    // NT_L y NT_L_PRIMA
    tablaM[NT_L-100][T_ID] = 14; tablaM[NT_L-100][T_ASTERISCO] = 14;
    tablaM[NT_L_PRIMA-100][T_COMA] = 15; tablaM[NT_L_PRIMA-100][T_PUNTO_COMA] = 16;

    // NT_I y NT_I_PRIMA
    tablaM[NT_I-100][T_ID] = 17; tablaM[NT_I-100][T_ASTERISCO] = 18;
    tablaM[NT_I_PRIMA-100][T_PUNTO_COMA] = 20;
    tablaM[NT_I_PRIMA-100][T_CORCH_I] = 19; tablaM[NT_I_PRIMA-100][T_COMA] = 20;
    tablaM[NT_I_PRIMA - 100][T_IGUAL] = 51;

    // NT_A y NT_A_PRIMA
    tablaM[NT_A-100][T_CORCH_I] = 21;
    tablaM[NT_A_PRIMA-100][T_CORCH_I] = 22;
    tablaM[NT_A_PRIMA-100][T_PUNTO_COMA] = 23; tablaM[NT_A_PRIMA-100][T_COMA] = 23;
    tablaM[NT_A_PRIMA-100][T_PAR_D] = 23;

    // NT_K
    tablaM[NT_K-100][T_ID] = 24; tablaM[NT_K-100][T_NUM] = 25;

    // NT_J y NT_J_PRIMA
    tablaM[NT_J-100][T_IF] = 26;
    tablaM[NT_J_PRIMA-100][T_ELSE] = 27;
    tablaM[NT_J_PRIMA-100][T_ID] = 28; tablaM[NT_J_PRIMA-100][T_INT] = 28;
    tablaM[NT_J_PRIMA-100][T_LLAVE_D] = 28; tablaM[NT_J_PRIMA-100][T_WHILE] = 28;
    tablaM[NT_J_PRIMA-100][T_FOR] = 28; tablaM[NT_J_PRIMA-100][T_PESOS] = 28;

    // NT_W y NT_FR
    tablaM[NT_W-100][T_WHILE] = 29;
    tablaM[NT_FR-100][T_FOR] = 30;

    // NT_FI, NT_FC, NT_FA
    tablaM[NT_FI-100][T_INT] = 31; tablaM[NT_FI-100][T_ID] = 32; tablaM[NT_FI-100][T_PUNTO_COMA] = 33;
    tablaM[NT_FC-100][T_ID] = 34; tablaM[NT_FC-100][T_NUM] = 34; tablaM[NT_FC-100][T_PUNTO_COMA] = 35;
    tablaM[NT_FA-100][T_ID] = 36; tablaM[NT_FA-100][T_MAS] = 52; tablaM[NT_FA-100][T_MENOS] = 56;
    tablaM[NT_FA-100][T_PAR_D] = 37;

    // NT_FA_PRIMA
    tablaM[NT_FA_PRIMA-100][T_MAS] = 53; tablaM[NT_FA_PRIMA-100][T_MENOS] = 54;
    tablaM[NT_FA_PRIMA-100][T_IGUAL] = 51; tablaM[NT_FA_PRIMA-100][T_PAR_D] = 55;

    // NT_O y NT_O_PRIMA
    tablaM[NT_O-100][T_ID] = 38; tablaM[NT_O-100][T_NUM] = 38;
    tablaM[NT_O_PRIMA-100][T_AND] = 39; tablaM[NT_O_PRIMA-100][T_OR] = 39;
    tablaM[NT_O_PRIMA-100][T_PUNTO_COMA] = 40; tablaM[NT_O_PRIMA-100][T_PAR_D] = 40;

    // NT_LOP y NT_OP
    tablaM[NT_LOP-100][T_AND] = 41; tablaM[NT_LOP-100][T_OR] = 42;
    tablaM[NT_OP-100][T_MENOR] = 47; tablaM[NT_OP-100][T_MAYOR] = 48;
    tablaM[NT_OP-100][T_IGUAL_IGUAL] = 49; tablaM[NT_OP-100][T_DIFERENTE] = 50;

    // NT_R y NT_V
    tablaM[NT_R-100][T_ID] = 43; tablaM[NT_R-100][T_NUM] = 43;
    tablaM[NT_V-100][T_ID] = 44; tablaM[NT_V-100][T_NUM] = 45; tablaM[NT_V-100][T_CTE_LIT] = 46;
}

void Sintactico::ejecutar(char asTokens[500][100], int k) {
    int ip = 0;
    while(!miPila.isEmpty()) miPila.pop();

    miPila.push("$");
    miPila.push("C");

    std::cout << "\n>>> ANALISIS SINTACTICO <<<" << std::endl;

    while(true) {
        std::string X_str = miPila.top();
        std::string a_str = asTokens[ip];

        int idX = -1;
        if(X_str == "S") idX = NT_S;
        else if(X_str == "B") idX = NT_B;
        else if(X_str == "C") idX = NT_C;
        else if(X_str == "D") idX = NT_D;
        else if(X_str == "T") idX = NT_T;
        else if(X_str == "L") idX = NT_L;
        else if(X_str == "L'") idX = NT_L_PRIMA;
        else if(X_str == "I") idX = NT_I;
        else if(X_str == "I'") idX = NT_I_PRIMA;
        else if(X_str == "A") idX = NT_A;
        else if(X_str == "A'") idX = NT_A_PRIMA;
        else if(X_str == "K") idX = NT_K;
        else if(X_str == "J") idX = NT_J;
        else if(X_str == "J'") idX = NT_J_PRIMA;
        else if(X_str == "W") idX = NT_W;
        else if(X_str == "FR") idX = NT_FR;
        else if(X_str == "FI") idX = NT_FI;
        else if(X_str == "FC") idX = NT_FC;
        else if(X_str == "FA") idX = NT_FA;
        else if(X_str == "FA'") idX = NT_FA_PRIMA;
        else if(X_str == "O") idX = NT_O;
        else if(X_str == "O'") idX = NT_O_PRIMA;
        else if(X_str == "LOP") idX = NT_LOP;
        else if(X_str == "R") idX = NT_R;
        else if(X_str == "V") idX = NT_V;
        else if(X_str == "Op") idX = NT_OP;
        else if(tokenToEnum.count(X_str)) idX = tokenToEnum[X_str];

        if (idX == -1) {
            if(X_str == "$" && a_str == "$") {
                std::cout << "EXITO: Cadena valida." << std::endl;
                break;
            }
            std::cout << "ERROR CRITICO: Simbolo en pila desconocido: " << X_str << std::endl;
            break;
        }

        int idA = tokenToEnum.count(a_str) ? tokenToEnum[a_str] : T_ERROR;

        if (idX < 100) {
            if (X_str == a_str) {
                miPila.pop();
                ip++;
                if (X_str == "$") {
                    std::cout << "EXITO: Cadena valida." << std::endl;
                    break;
                }
            } else {
                std::cout << "ERROR: Se esperaba " << X_str << " pero hay " << a_str << std::endl;
                break;
            }
        } else {
            int renglon = tablaM[idX - 100][idA];
            if (renglon != 999) {
                miPila.pop();
                Produccion p = gramatica[renglon];

                // >>> AQUI ESTA LA MAGIA QUE IMPRIME LAS PRODUCCIONES <<<
                std::cout << idToString[p.ladoIzquierdo] << " -> ";

                if (p.ladoDerecho.size() == 1 && p.ladoDerecho[0] == T_EPSILON) {
                    std::cout << "epsilon";
                } else {
                    // Imprimimos el vector al revés para que se lea en orden correcto
                    for (int i = p.ladoDerecho.size() - 1; i >= 0; i--) {
                        int sym = p.ladoDerecho[i];
                        std::cout << idToString[sym] << " ";
                    }
                }
                std::cout << std::endl;
                // >>> FIN DE LA MAGIA <<<

                for (int simbolo : p.ladoDerecho) {
                    if (simbolo != T_EPSILON) {
                        string s = (simbolo >= 100) ? idToString[simbolo] : idToString[simbolo];
                        miPila.push(s);
                    }
                }
            } else {
                std::cout << "ERROR SINTACTICO en: " << a_str << std::endl;
                break;
            }
        }
    }
}
