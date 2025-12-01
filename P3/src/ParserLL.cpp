#include "headers/ParserLL.hpp"

ParserLL::ParserLL(Lexer *lexer)
{
    this->lexer = lexer;
    loadSyms();
    loadProds();
    loadTable();
}

ParserLL::~ParserLL()
{
}

void ParserLL::loadSyms()
{
    // Cargar Terminales (Tokens) usando su valor enum como ID (0-99)
    grammar.addSymbol(t_eof, Symbol(t_eof));
    grammar.addSymbol(t_int, Symbol(t_int));
    grammar.addSymbol(t_float, Symbol(t_float));
    grammar.addSymbol(t_id, Symbol(t_id));
    grammar.addSymbol(t_num, Symbol(t_num));
    grammar.addSymbol(t_semicolon, Symbol(t_semicolon));
    grammar.addSymbol(t_comma, Symbol(t_comma));
    grammar.addSymbol(t_assign, Symbol(t_assign));
    grammar.addSymbol(t_if, Symbol(t_if));
    grammar.addSymbol(t_else, Symbol(t_else));
    grammar.addSymbol(t_while, Symbol(t_while));
    grammar.addSymbol(t_plus, Symbol(t_plus));
    grammar.addSymbol(t_minus, Symbol(t_minus));
    grammar.addSymbol(t_mul, Symbol(t_mul));
    grammar.addSymbol(t_div, Symbol(t_div));
    grammar.addSymbol(t_lparen, Symbol(t_lparen));
    grammar.addSymbol(t_rparen, Symbol(t_rparen));

    // Cargar No-Terminales con un offset de 100 para evitar colisiones
    // Ejemplo: nt_programa (1) se guarda en la posición 101
    int offset = 100;
    grammar.addSymbol(offset + nt_programa, Symbol(nt_programa));
    grammar.addSymbol(offset + nt_decls, Symbol(nt_decls));
    grammar.addSymbol(offset + nt_decls_prime, Symbol(nt_decls_prime));
    grammar.addSymbol(offset + nt_decl, Symbol(nt_decl));
    grammar.addSymbol(offset + nt_tipo, Symbol(nt_tipo));
    grammar.addSymbol(offset + nt_lista_var, Symbol(nt_lista_var));
    grammar.addSymbol(offset + nt_lista_var_prime, Symbol(nt_lista_var_prime));
    grammar.addSymbol(offset + nt_sentencias, Symbol(nt_sentencias));
    grammar.addSymbol(offset + nt_sentencias_prime, Symbol(nt_sentencias_prime));
    grammar.addSymbol(offset + nt_sentencia, Symbol(nt_sentencia));
    grammar.addSymbol(offset + nt_expr, Symbol(nt_expr));
    grammar.addSymbol(offset + nt_expr_prime, Symbol(nt_expr_prime));
    grammar.addSymbol(offset + nt_term, Symbol(nt_term));
    grammar.addSymbol(offset + nt_term_prime, Symbol(nt_term_prime));
    grammar.addSymbol(offset + nt_factor, Symbol(nt_factor));
}

void ParserLL::loadProds()
{
    int off = 100; // Mismo offset usado arriba para referenciar No-Terminales
    
    // 1. Programa -> Decls Sentencias
    grammar.addProd(1, Production(off + nt_programa, {off + nt_decls, off + nt_sentencias}));

    // 2. Decls -> Decl Decls'
    grammar.addProd(2, Production(off + nt_decls, {off + nt_decl, off + nt_decls_prime}));

    // 3. Decls' -> Decl Decls'
    grammar.addProd(3, Production(off + nt_decls_prime, {off + nt_decl, off + nt_decls_prime}));
    // 4. Decls' -> epsilon (No agregamos nada al vector body)
    grammar.addProd(4, Production(off + nt_decls_prime, {})); 

    // 5. Decl -> Tipo ListaVar ;
    grammar.addProd(5, Production(off + nt_decl, {off + nt_tipo, off + nt_lista_var, t_semicolon}));

    // 6. Tipo -> int
    grammar.addProd(6, Production(off + nt_tipo, {t_int}));
    // 7. Tipo -> float
    grammar.addProd(7, Production(off + nt_tipo, {t_float}));

    // 8. ListaVar -> id ListaVar'
    grammar.addProd(8, Production(off + nt_lista_var, {t_id, off + nt_lista_var_prime}));

    // 9. ListaVar' -> , id ListaVar'
    grammar.addProd(9, Production(off + nt_lista_var_prime, {t_comma, t_id, off + nt_lista_var_prime}));
    // 10. ListaVar' -> epsilon
    grammar.addProd(10, Production(off + nt_lista_var_prime, {}));

    // 11. Sentencias -> Sentencia Sentencias'
    grammar.addProd(11, Production(off + nt_sentencias, {off + nt_sentencia, off + nt_sentencias_prime}));

    // 12. Sentencias' -> Sentencia Sentencias'
    grammar.addProd(12, Production(off + nt_sentencias_prime, {off + nt_sentencia, off + nt_sentencias_prime}));
    // 13. Sentencias' -> epsilon
    grammar.addProd(13, Production(off + nt_sentencias_prime, {}));

    // 14. Sentencia -> id = Expr ;
    grammar.addProd(14, Production(off + nt_sentencia, {t_id, t_assign, off + nt_expr, t_semicolon}));
    // 15. Sentencia -> if ( Expr ) Sentencias else Sentencias
    grammar.addProd(15, Production(off + nt_sentencia, {t_if, t_lparen, off + nt_expr, t_rparen, off + nt_sentencias, t_else, off + nt_sentencias}));
    // 16. Sentencia -> while ( Expr ) Sentencias
    grammar.addProd(16, Production(off + nt_sentencia, {t_while, t_lparen, off + nt_expr, t_rparen, off + nt_sentencias}));

    // 17. Expr -> Term Expr'
    grammar.addProd(17, Production(off + nt_expr, {off + nt_term, off + nt_expr_prime}));

    // 18. Expr' -> + Term Expr'
    grammar.addProd(18, Production(off + nt_expr_prime, {t_plus, off + nt_term, off + nt_expr_prime}));
    // 19. Expr' -> - Term Expr'
    grammar.addProd(19, Production(off + nt_expr_prime, {t_minus, off + nt_term, off + nt_expr_prime}));
    // 20. Expr' -> epsilon
    grammar.addProd(20, Production(off + nt_expr_prime, {}));

    // 21. Term -> Factor Term'
    grammar.addProd(21, Production(off + nt_term, {off + nt_factor, off + nt_term_prime}));

    // 22. Term' -> * Factor Term'
    grammar.addProd(22, Production(off + nt_term_prime, {t_mul, off + nt_factor, off + nt_term_prime}));
    // 23. Term' -> / Factor Term'
    grammar.addProd(23, Production(off + nt_term_prime, {t_div, off + nt_factor, off + nt_term_prime}));
    // 24. Term' -> epsilon
    grammar.addProd(24, Production(off + nt_term_prime, {}));

    // 25. Factor -> ( Expr )
    grammar.addProd(25, Production(off + nt_factor, {t_lparen, off + nt_expr, t_rparen}));
    // 26. Factor -> id
    grammar.addProd(26, Production(off + nt_factor, {t_id}));
    // 27. Factor -> num
    grammar.addProd(27, Production(off + nt_factor, {t_num}));
}

void ParserLL::loadTable()
{
    // Programa -> Decls Sentencias
    table[nt_programa][t_int] = 1;
    table[nt_programa][t_float] = 1;

    // Decls
    table[nt_decls][t_int] = 2;
    table[nt_decls][t_float] = 2;

    // Decls'
    table[nt_decls_prime][t_int] = 3;
    table[nt_decls_prime][t_float] = 3;
    // Follow(Decls') -> id, if, while
    table[nt_decls_prime][t_id] = 4;    // epsilon
    table[nt_decls_prime][t_if] = 4;    // epsilon
    table[nt_decls_prime][t_while] = 4; // epsilon

    // Decl
    table[nt_decl][t_int] = 5;
    table[nt_decl][t_float] = 5;

    // Tipo
    table[nt_tipo][t_int] = 6;
    table[nt_tipo][t_float] = 7;

    // ListaVar
    table[nt_lista_var][t_id] = 8;

    // ListaVar'
    table[nt_lista_var_prime][t_comma] = 9;
    table[nt_lista_var_prime][t_semicolon] = 10; // epsilon (Follow)

    // Sentencias
    table[nt_sentencias][t_id] = 11;
    table[nt_sentencias][t_if] = 11;
    table[nt_sentencias][t_while] = 11;

    // Sentencias'
    table[nt_sentencias_prime][t_id] = 12;
    table[nt_sentencias_prime][t_if] = 12;
    table[nt_sentencias_prime][t_while] = 12;
    table[nt_sentencias_prime][t_eof] = 13;   // epsilon (Follow)
    table[nt_sentencias_prime][t_else] = 13;  // epsilon (Follow)

    // Sentencia
    table[nt_sentencia][t_id] = 14;
    table[nt_sentencia][t_if] = 15;
    table[nt_sentencia][t_while] = 16;

    // Expr
    table[nt_expr][t_lparen] = 17;
    table[nt_expr][t_id] = 17;
    table[nt_expr][t_num] = 17;

    // Expr'
    table[nt_expr_prime][t_plus] = 18;
    table[nt_expr_prime][t_minus] = 19;
    table[nt_expr_prime][t_semicolon] = 20; // epsilon
    table[nt_expr_prime][t_rparen] = 20;    // epsilon

    // Term
    table[nt_term][t_lparen] = 21;
    table[nt_term][t_id] = 21;
    table[nt_term][t_num] = 21;

    // Term'
    table[nt_term_prime][t_mul] = 22;
    table[nt_term_prime][t_div] = 23;
    table[nt_term_prime][t_plus] = 24;  // epsilon
    table[nt_term_prime][t_minus] = 24; // epsilon
    table[nt_term_prime][t_semicolon] = 24; // epsilon
    table[nt_term_prime][t_rparen] = 24;    // epsilon

    // Factor
    table[nt_factor][t_lparen] = 25;
    table[nt_factor][t_id] = 26;
    table[nt_factor][t_num] = 27;
}

int ParserLL::parse()
{
    stack<Symbol> pila;
    
    // 1. Inicializar la pila con el símbolo inicial (Programa) y EOF ($) al fondo
    pila.push(Symbol(t_eof)); 
    pila.push(Symbol(nt_programa)); 

    // Obtiene el primer token del lexer
    token = eat(); 

    while(!pila.empty()) {
        Symbol X = pila.top();
        pila.pop();

        // CASO 1: X es un Terminal
        if (X.getType() == terminal) {
            if (X.getToken() == token) {
                // Consumimos entrada (a menos que sea EOF)
                if (token != t_eof) {
                    token = eat();
                }
            } else {
                error("Error sintáctico: Se esperaba " + to_string(X.getToken()) + 
                      " pero se encontró " + to_string(token));
            }
        }
        // CASO 2: X es un No-Terminal
        else {
            NoTerm nt = X.getNoTerm();
            
            // Buscar en la tabla M[nt, token]
            // Se valida si la entrada existe en el mapa
            if (table[nt].find(token) != table[nt].end()) {
                int prodIndex = table[nt][token];
                Production p = grammar.getProd(prodIndex);
                
                // Empuja el cuerpo de la producción a la pila EN ORDEN INVERSO
                vector<int> body = p.getBody();
                for (int i = body.size() - 1; i >= 0; i--) {
                    int symId = body[i];
                    Symbol s = grammar.getSym(symId);
                    
                    // No empujar epsilon (strEmpty) a la pila
                    if (s.getType() == nonterminal && s.getNoTerm() == strEmpty) {
                        continue; 
                    }
                    pila.push(s);
                }
            } else {
                error("Error sintáctico: No hay producción para [" + to_string(nt) + 
                      "] con el token " + to_string(token));
            }
        }
    }
    aceptar("Análisis sintáctico exitoso.");
    return 0;
}

void ParserLL::error(string msg)
{
    cout<<msg<<endl;
    exit(EXIT_FAILURE);
}

Token ParserLL::eat()
{
    return (Token) lexer->yylex();    
}

void ParserLL::aceptar(string msg)
{
    cout<<msg<<endl;
}
