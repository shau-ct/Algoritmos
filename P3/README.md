<p  align="center">
  <img  width="200"  src="https://www.fciencias.unam.mx/sites/default/files/logoFC_2.png"  alt="">  <br>Compiladores  2026-1 <br>
  Práctica 3: Implementación de un Analizador Sintáctico de Descenso Predictivo <br> Alumno: Morales Aguilar Marcos
</p>

## Implementación de un Analizador Sintáctico de Descenso Predictivo

### Ejercicios
Para la gramática G = ( N, Σ, P, S), descrita por las siguientes producciones: 
> P = {
>> programa → declaraciones sentencias <br>
>> declaraciones → declaraciones declaracion | declaracion <br>
>> declaracion → tipo lista-var **;** <br>
>> tipo → **int** | **float** <br>
>> lista_var → lista_var **,** _**identificador**_ | _**identificador**_ <br>
>> sentencias → sentencias sentencia | sentencia <br>
>> sentencia → _**identificador**_ **=** expresion **;** | **if** **(** expresion **)** sentencias **else** sentencias | **while** **(** expresión **)** sentencias <br>
>> expresion → expresion **+** expresion | expresion **-** expresion | expresion __\*__ expresion | expresion **/** expresión | _**identificador**_ | **_numero_** <br>
>> expresion → **(** expresion **)** <br>
}


1. Determinar en un archivo Readme, en formato Markdown (.md) o LaTeX (.tex) - con su respectivo PDF, para este último - , los conjuntos _N_, _Σ_ y el símbolo inicial _S_.  (0.5 pts.) <br>
    a. Mostrar en el archivo el proceso de eliminación de ambigüedad o justificar, en caso de no ser necesario. (0.25 pts.) 
    
    La producción de `expresion` original era ambigua y no respetaba precedencia de operadores. Se estratificó la gramática en tres niveles:

    1.  **Expresión ($E$):** Maneja sumas y restas (menor precedencia).
    2.  **Término ($T$):** Maneja multiplicaciones y divisiones (mayor precedencia).
    3.  **Factor ($F$):** Maneja paréntesis, identificadores y números (unidad básica). <br>
    
    b. Mostrar en el archivo el proceso de eliminación de la recursividad izquierda o justificar, en caso de no ser necesario. (0.25 pts.) <br>
    c. Mostrar en el archivo el proceso de factorización izquierda o justificar, en caso de no ser necesario. (0.25 pts.) 
    
    b. y c. Se eliminó la recursividad izquierda directa en `declaraciones`, `lista_var`, `sentencias` y en las nuevas reglas de expresiones (`expr` y `term`), introduciendo nuevos no terminales "primos" ($'$). <br>

    d. Mostrar en el archivo los nuevos conjuntos _N'_ y _P'_, que definen _G'_. (0.25 pts.) 
    
    Conjunto N': `{ Programa, Decls, Decls_prima, Decl, Tipo, ListaVar, ListaVar_prima, Sentencias, Sentencias_prima, Sentencia, Expr, Expr_prima, Term, Term_prima, Factor }`

> P' = {
>> **Programa** -> Decls Sentencias <br>
>> **Decls** -> Decl Decls_prima <br>
>> **Decls_prima** -> Decl Decls_prima | epsilon <br>
>> **Decl** -> Tipo ListaVar **;** <br>
>> **Tipo** -> **int** | **float** <br>
>> **ListaVar** -> **id** ListaVar_prima <br>
>> **ListaVar_prima** -> **,** **id** ListaVar_prima | epsilon <br>
>> **Sentencias** -> Sentencia Sentencias_prima <br>
>> **Sentencias_prima** -> Sentencia Sentencias_prima | epsilon <br>
>> **Sentencia** -> **id** **=** Expr **;** <br>
>> | **if** **(** Expr **)** Sentencias **else** Sentencias <br>
>> | **while** **(** Expr **)** Sentencias <br>
>> **Expr** -> Term Expr_prima <br>
>> **Expr_prima** -> **+** Term Expr_prima | **-** Term Expr_prima | epsilon <br>
>> **Term** -> Factor Term_prima <br>
>> **Term_prima** -> ***** Factor Term_prima | **/** Factor Term_prima | epsilon <br>
>> **Factor** -> **(** Expr **)** | **id** | **num** <br>
> }

2. Mostrar en el archivo la construcción de los conjuntos FIRST de la gramática _G'_. (1 pt.)

Cálculo de los primeros símbolos que pueden derivarse de cada No-Terminal.

| No-Terminal | FIRST |
| :--- | :--- |
| **Programa** | int, float |
| **Decls** | int, float |
| **Decls_prima** | int, float, epsilon |
| **Decl** | int, float |
| **Tipo** | int, float |
| **ListaVar** | id |
| **ListaVar_prima** | , (coma), epsilon |
| **Sentencias** | id, if, while |
| **Sentencias_prima** | id, if, while, epsilon |
| **Sentencia** | id, if, while |
| **Expr** | (, id, num |
| **Expr_prima** | +, -, epsilon |
| **Term** | (, id, num |
| **Term_prima** | *, /, epsilon |
| **Factor** | (, id, num |

3. Mostrar en el archivo la construcción de los conjuntos FOLLOW de la gramática _G'_. (1 pt.)

Cálculo de los símbolos que pueden aparecer inmediatamente después de un No-Terminal.

| No-Terminal | FOLLOW |
| :--- | :--- |
| **Programa** | $ (Fin de archivo) |
| **Decls** | id, if, while |
| **Decls_prima** | id, if, while |
| **Decl** | int, float, id, if, while |
| **Tipo** | id |
| **ListaVar** | ; |
| **ListaVar_prima** | ; |
| **Sentencias** | $, else |
| **Sentencias_prima** | $, else |
| **Sentencia** | id, if, while, $, else |
| **Expr** | ;, ) |
| **Expr_prima** | ;, ) |
| **Term** | +, -, ;, ) |
| **Term_prima** | +, -, ;, ) |
| **Factor** | *, /, +, -, ;, ) |

4. Mostrar en el archivo la construcción de la tabla de análisis sintáctico predictivo para _G'_. (1 pt.)

La tabla indica qué producción utilizar dado un No-Terminal y un Token de entrada.

*(Nota: Las celdas vacías indican error).*

| No-Terminal | int | float | id | num | ; | , | = | if | else | while | + | - | * | / | ( | ) | $ |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| **Prog** | P 1 | P 1 | | | | | | | | | | | | | | | |
| **Decls** | P 2 | P 2 | | | | | | | | | | | | | | | |
| **Decls'** | P 3 | P 3 | epsilon | | | | | epsilon | | epsilon | | | | | | | |
| **Decl** | P 5 | P 5 | | | | | | | | | | | | | | | |
| **Tipo** | P 6 | P 7 | | | | | | | | | | | | | | | |
| **LVar** | | | P 8 | | | | | | | | | | | | | | |
| **LVar'** | | | | | epsilon | P 9 | | | | | | | | | | | |
| **Stmts** | | | P 11 | | | | | P 11 | | P 11 | | | | | | | |
| **Stmts'** | | | P 12 | | | | | P 12 | epsilon | P 12 | | | | | | | epsilon |
| **Stmt** | | | P 14 | | | | | P 15 | | P 16 | | | | | | | |
| **Expr** | | | P 17 | P 17 | | | | | | | | | | | P 17 | | |
| **Expr'** | | | | | epsilon | | | | | | P 18 | P 19 | | | | epsilon | |
| **Term** | | | P 21 | P 21 | | | | | | | | | | | P 21 | | |
| **Term'** | | | | | epsilon | | | | | | epsilon | epsilon | P 22 | P 23 | | epsilon | |
| **Factor**| | | P 26 | P 27 | | | | | | | | | | | P 25 | | |

5. Sustituir el contenido del Analizador Léxico (lexer.ll) con el implementado en la segunda práctica. (0.5 pts.)
* Se definieron los enumeradores `Token` y `NoTerm` en `Symbols.hpp`.
* Se cargó la gramática $G'$ y la tabla predictiva $M$ en `ParserLL::loadTable`.
* El método `ParserLL::parse` utiliza una pila explícita para validar la cadena de entrada contra las producciones.

6. Definir en un comentario de _Symbols.hpp_ la gramática _G'_. (0.05 pts.)
7. Definir _Σ_ en un _**enum**_ de _Symbols.hpp_. (0.10 pts.)
8. Definir _N'_ en un _**enum**_ de _Symbols.hpp_. (0.10 pts.)
9. Cargar _N' ∪ Σ_ en _ParserLL.cpp_. (0.25 pts.) 
10. Cargar _P'_ en _ParserLL.cpp_. (0.25 pts.)
11. Cargar la tabla de análisis sintáctico predictivo en _ParserLL.cpp_. (0.25 pts.)
12. Implementar el algoritmo de análisis sintáctico de descenso predictivo en _ParserLL.cpp_ de modo que el programa acepte el archivo _prueba_. (4 pts.)
---
#### Extras

13. Documentar el código. (0.25pts)
14. Proponer 4 archivos de prueba nuevos, 2 válidos y 2 inválidos. (0.25pts)
