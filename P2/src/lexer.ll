%{
#include <iostream>
#include <string>
using namespace std;

#include "headers/Symbols.hpp"
#include "headers/Lexer.hpp"

int line=1;
%}

%option c++
%option outfile="Lexer.cpp"
%option yyclass="Lexer"
%option noyywrap

/* Expresiones regulares auxiliares */
DIGITO  [0-9]
LETRA   [a-zA-Z_]
ID      {LETRA}({LETRA}|{DIGITO})*
NUM     {DIGITO}+(\.{DIGITO}+)?

%%

[ \t\r]+    { /* Ignorar espacios en blanco */ }
"\n" 	    { line++; }

"int"       { return INT; }
"float"     { return FLOAT; }
"if"        { return IF; }
"else"      { return ELSE; }
"while"     { return WHILE; }

"+"         { return SUMA; }
"-"         { return RESTA; }
"*"         { return MUL; }
"/"         { return DIV; }
"="         { return ASIGNA; }
"("         { return LPAREN; }
")"         { return RPAREN; }
";"         { return PYC; }
","         { return COMA; }

{ID}        { return IDENTIFICADOR; }
{NUM}       { return NUMERO; }

.           { cout << "ERROR LEXICO " << yytext << " en linea " << line << endl; }

%%

int Lexer::getLine()
{
    return line;
}