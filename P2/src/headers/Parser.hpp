#ifndef PARSER_H
#define PARSER_H
#include <string>
#include "Lexer.hpp"
#include "Symbols.hpp"
using namespace std;

namespace C_1
{
  class Parser
  {
  private:
    Lexer *lexer;
    int token;
    
    // Comprobación
    void check(int expectedToken); // Verifica y consume el token esperado
    
  public:
    Parser(Lexer *lexer);
    ~Parser();
    
    // Funciones de la gramática (No terminales)
    void programa();
    void declaraciones();
    void declaracion();
    void tipo();
    void lista_var();
    void lista_var_prima();
    void sentencias();
    void sentencia();
    void expresion();
    void expresion_prima();
    void termino();
    void termino_prima();
    void factor();

    Token eat();       // Obtener siguiente token
    void error(string msg);
    void parse();      // Punto de entrada
  };    
}
#endif