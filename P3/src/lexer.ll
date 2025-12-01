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

%%

[ \t\r]+ {}
"\n" 	 {line++;}

"int"    { return t_int; }
"float"  { return t_float; }
"if"     { return t_if; }
"else"   { return t_else; }
"while"  { return t_while; }

"+"      { return t_plus; }
"-"      { return t_minus; }
"*"      { return t_mul; }
"/"      { return t_div; }
"="      { return t_assign; }
"("      { return t_lparen; }
")"      { return t_rparen; }
";"      { return t_semicolon; }
","      { return t_comma; }

[a-zA-Z_][a-zA-Z0-9_]* { return t_id; }
[0-9]+(\.[0-9]+)?      { return t_num; }

.        { cout << "ERROR LEXICO " << yytext << endl;}

%%

int yyFlexLexer::yywrap(){
    return 1;
}

int Lexer::getLine()
{
    return line;
}