#ifndef __SYMBOLS_HPP__
#define __SYMBOLS_HPP__

/** 
 * 1. Definir en un comentario la gramática G(N, T, P, S):
 * - Símbolo Inicial (S): programa
 * 
 * - Terminales (Σ): { int, float, ;, ,, identificador, =,
 * if, else, while, (, ), +, -, *, /, numero }
 * 
 * - No terminales (N): { programa, declaraciones, declaracion,
 * tipo, lista_var, sentencias, sentencia, expresion }
 */

/**
 * 2. Determinar la enumeración para el conjunto T
 */
enum Token { 
    // Control de fin de archivo
    t_eof = 0,
    
    // Palabras reservadas y tipos
    INT = 256, FLOAT, IF, ELSE, WHILE,
    
    // Identificadores y literales
    IDENTIFICADOR, NUMERO,
    
    // Operadores y signos
    SUMA, RESTA, MUL, DIV, ASIGNA, // +, -, *, /, =
    LPAREN, RPAREN, PYC, COMA      // (, ), ;, ,
};

/**
 * 3. Determinar la enumeración para el conjunto N (No terminales)
 */
enum NoTerm { 
    strEmpty, 
    nt_programa, nt_declaraciones, nt_declaracion, 
    nt_tipo, nt_lista_var, nt_lista_var_prima,
    nt_sentencias, nt_sentencia, 
    nt_expresion, nt_expresion_prima, 
    nt_termino, nt_termino_prima, nt_factor 
};

#endif // !__SYMBOLS_HPP__