#include "headers/Parser.hpp"
#include <iostream>
#include <cstdlib>

namespace C_1
{
  Parser::Parser(Lexer *lexer)
  {
    this->lexer = lexer;
  }
    
  Parser::~Parser()
  {
  }

  /************************************************************************/
  /**                                                                    **/
  /**                       Funciones por cada NT                        **/
  /**                                                                    **/
  /************************************************************************/

  Token Parser::eat(){
    return (Token) lexer->yylex();
  }

  void Parser::error(string msg){
    cout << "ERROR DE SINTAXIS: " << msg << " en la línea " << lexer->getLine() << endl;
    exit(EXIT_FAILURE);
  }

  void Parser::check(int expectedToken) {
      if (token == expectedToken) {
          token = eat();
      } else {
          error("Se esperaba un token distinto.");
      }
  }

  void Parser::parse(){
    token = eat(); // Cargar primer token
    programa();
    
    if(token == t_eof)
      cout << "La cadena es aceptada" << endl;
    else 
      cout << "La cadena no pertenece al lenguaje generado por la gramática" << endl;
  }

  // 1. programa -> declaraciones sentencias
  void Parser::programa(){
    declaraciones();
    sentencias();
  }

  // 2. declaraciones -> declaracion declaraciones | epsilon
  void Parser::declaraciones(){
    // First(declaracion) = {INT, FLOAT}
    if (token == INT || token == FLOAT) {
        declaracion();
        declaraciones();
    }
    // Si no es int/float, asumimos epsilon y retornamos
  }

  // 3. declaracion -> tipo lista_var ;
  void Parser::declaracion(){
    tipo();
    lista_var();
    check(PYC); // Punto y coma `;`
  }

  // 4. tipo -> int | float
  void Parser::tipo(){
    if (token == INT || token == FLOAT) {
        token = eat();
    } else {
        error("Se esperaba un tipo de dato (int o float)");
    }
  }

  // 5. lista_var -> identificador lista_var_prima
  void Parser::lista_var(){
    if (token == IDENTIFICADOR) {
        token = eat();
        lista_var_prima();
    } else {
        error("Se esperaba un identificador");
    }
  }

  // 6. lista_var_prima -> , identificador lista_var_prima | epsilon
  void Parser::lista_var_prima(){
    if (token == COMA) {
        token = eat();
        if (token == IDENTIFICADOR) {
            token = eat();
            lista_var_prima();
        } else {
            error("Se esperaba identificador después de la coma");
        }
    }
  }

  // 7. sentencias -> sentencia sentencias | epsilon
  void Parser::sentencias(){
      // First(sentencia) = {IDENTIFICADOR, IF, WHILE}
      if (token == IDENTIFICADOR || token == IF || token == WHILE) {
          sentencia();
          sentencias();
      }
  }

  // 8. sentencia
  void Parser::sentencia(){
      if (token == IDENTIFICADOR) {
          // identificador = expresion ;
          token = eat(); 
          check(ASIGNA);
          expresion();
          check(PYC);
      } else if (token == IF) {
          // if (expresion) sentencias else sentencias
          token = eat();
          check(LPAREN);
          expresion();
          check(RPAREN);
          sentencias();
          check(ELSE);
          sentencias();
      } else if (token == WHILE) {
          // while (expresion) sentencias
          token = eat();
          check(LPAREN);
          expresion();
          check(RPAREN);
          sentencias();
      } else {
          error("Sentencia no válida");
      }
  }

  // 9. expresion -> termino expresion_prima
  void Parser::expresion(){
      termino();
      expresion_prima();
  }

  // 10. expresion_prima -> + termino E' | - termino E' | epsilon
  void Parser::expresion_prima(){
      if (token == SUMA || token == RESTA) {
          token = eat();
          termino();
          expresion_prima();
      }
  }

  // 11. termino -> factor termino_prima
  void Parser::termino(){
      factor();
      termino_prima();
  }

  // 12. termino_prima -> * factor T' | / factor T' | epsilon
  void Parser::termino_prima(){
      if (token == MUL || token == DIV) {
          token = eat();
          factor();
          termino_prima();
      }
  }

  // 13. factor -> ( expresion ) | identificador | numero
  void Parser::factor(){
      if (token == LPAREN) {
          token = eat();
          expresion();
          check(RPAREN);
      } else if (token == IDENTIFICADOR || token == NUMERO) {
          token = eat();
      } else {
          error("Factor inesperado (se esperaba id, numero o parentesis)");
      }
  }
}