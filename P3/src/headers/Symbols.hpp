#ifndef __SYMBOLS_HPP__
#define __SYMBOLS_HPP__

/** 
 * 1. Definir en un comentario la gramática G'(N', T, P', S)
 *
 */


/**
 * 2. Determinar la enumeración para el conjunto T
 */
enum Token { 
    t_eof = 0, 
    t_int, t_float,     // 1, 2
    t_id, t_num,        // 3, 4
    t_semicolon, t_comma, t_assign, // 5, 6, 7
    t_if, t_else, t_while,          // 8, 9, 10
    t_plus, t_minus, t_mul, t_div,  // 11, 12, 13, 14
    t_lparen, t_rparen              // 15, 16
};

/**
 * 3. Determinar la enumeración para el conjunto N
 */
enum NoTerm { 
    strEmpty = 0, // epsilon
    nt_programa, 
    nt_decls, nt_decls_prime, 
    nt_decl, 
    nt_tipo, 
    nt_lista_var, nt_lista_var_prime, 
    nt_sentencias, nt_sentencias_prime, 
    nt_sentencia, 
    nt_expr, nt_expr_prime, 
    nt_term, nt_term_prime, 
    nt_factor 
};

#endif // !__SYMBOLS_HPP__
