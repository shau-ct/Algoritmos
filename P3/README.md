<p  align="center">
  <img  width="200"  src="https://www.fciencias.unam.mx/sites/default/files/logoFC_2.png"  alt="">  <br>Compiladores  2026-1 <br>
  Práctica 3: Implementación de un Analizador Sintáctico de Descenso Predictivo <br> Alumno: Morales Aguilar Marcos
</p>

## Implementación de un Analizador Sintáctico de Descenso Predictivo

### Estructura del directorio
```c++
p4
├── README.md
└── src //carpeta de código
    ├── prueba //archivo para I/O test
    ├── lib //carpeta para bibliotecas
    │   └── FlexLexer.h //archivo de cabecera (ignorar)
    ├── Makefile //archivo de reglas de compilación
    ├── main.cpp //contiene la función principal del programa
    ├── Production.cpp //archivo para la clase producción
    ├── lexer.ll //archivo de Flex para generación de `scanner`
    ├── Symbol.cpp //archivo para la clase de símbolo
    ├── Grammar.cpp //archivo para la clase de gramática
    ├── ParserLL.cpp //archivo para parser LL(1)
    └── headers //carpeta de archivos de código
        ├── Lexer.hpp //archivo de cabecera para el scanner
        ├── Symbol.h //archivo de cabecera de símbolo
        ├── Production.h //archivo de cabecera de producción
        ├── Symbols.hpp //archivo de cabecera definición de los conjuntos N y Σ
        ├── Grammar.h //archivo de cabecera de gramática
        └── ParserLL.hpp //archivo de cabecera del parser LL(1)

```

### Uso

#### Compilacion

```bash
$ cd src/
$ make
```

#### Ejecucion

```bash
$ ./compiler prueba
```

#### Ejercicios
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
    
    **Nuevos No Terminales ($N'$):**
    $\{ Programa, Decls, Decls', Decl, Tipo, ListaVar, ListaVar', Sentencias, Sentencias', Sentencia, Expr, Expr', Term, Term', Factor \}$
    
    **Producciones ($P'$):**
    1.  $Programa \to Decls \ Sentencias$
    2.  $Decls \to Decl \ Decls'$
    3.  $Decls' \to Decl \ Decls' \mid \epsilon$
    4.  $Decl \to Tipo \ ListaVar \ \textbf{;}$
    5.  $Tipo \to \textbf{int} \mid \textbf{float}$
    6.  $ListaVar \to \textbf{id} \ ListaVar'$
    7.  $ListaVar' \to \textbf{,} \ \textbf{id} \ ListaVar' \mid \epsilon$
    8.  $Sentencias \to Sentencia \ Sentencias'$
    9.  $Sentencias' \to Sentencia \ Sentencias' \mid \epsilon$
    10. $Sentencia \to \textbf{id} \ \textbf{=} \ Expr \ \textbf{;}$
    11. $Sentencia \to \textbf{if} \ \textbf{(} \ Expr \ \textbf{)} \ Sentencias \ \textbf{else} \ Sentencias$
    12. $Sentencia \to \textbf{while} \ \textbf{(} \ Expr \ \textbf{)} \ Sentencias$
    13. $Expr \to Term \ Expr'$
    14. $Expr' \to \textbf{+} \ Term \ Expr' \mid \textbf{-} \ Term \ Expr' \mid \epsilon$
    15. $Term \to Factor \ Term'$
    16. $Term' \to \textbf{*} \ Factor \ Term' \mid \textbf{/} \ Factor \ Term' \mid \epsilon$
    17. $Factor \to \textbf{(} \ Expr \ \textbf{)} \mid \textbf{id} \mid \textbf{num}$ <br>

2. Mostrar en el archivo la construcción de los conjuntos FIRST de la gramática _G'_. (1 pt.)

Cálculo de los primeros símbolos que pueden derivarse de cada No Terminal.

| No Terminal ($X$) | FIRST($X$) |
| :--- | :--- |
| **Programa** | $\{ \textbf{int}, \textbf{float} \}$ |
| **Decls** | $\{ \textbf{int}, \textbf{float} \}$ |
| **Decls'** | $\{ \textbf{int}, \textbf{float}, \epsilon \}$ |
| **Decl** | $\{ \textbf{int}, \textbf{float} \}$ |
| **Tipo** | $\{ \textbf{int}, \textbf{float} \}$ |
| **ListaVar** | $\{ \textbf{id} \}$ |
| **ListaVar'** | $\{ \textbf{,}, \epsilon \}$ |
| **Sentencias** | $\{ \textbf{id}, \textbf{if}, \textbf{while} \}$ |
| **Sentencias'** | $\{ \textbf{id}, \textbf{if}, \textbf{while}, \epsilon \}$ |
| **Sentencia** | $\{ \textbf{id}, \textbf{if}, \textbf{while} \}$ |
| **Expr** | $\{ \textbf{(}, \textbf{id}, \textbf{num} \}$ |
| **Expr'** | $\{ \textbf{+}, \textbf{-}, \epsilon \}$ |
| **Term** | $\{ \textbf{(}, \textbf{id}, \textbf{num} \}$ |
| **Term'** | $\{ \textbf{*}, \textbf{/}, \epsilon \}$ |
| **Factor** | $\{ \textbf{(}, \textbf{id}, \textbf{num} \}$ |

---

3. Mostrar en el archivo la construcción de los conjuntos FOLLOW de la gramática _G'_. (1 pt.)

Cálculo de los símbolos que pueden aparecer inmediatamente después de un No Terminal.

| No Terminal ($X$) | FOLLOW($X$) |
| :--- | :--- |
| **Programa** | $\{ \mathbf{\$} \}$ |
| **Decls** | $\{ \textbf{id}, \textbf{if}, \textbf{while} \}$ |
| **Decls'** | $\{ \textbf{id}, \textbf{if}, \textbf{while} \}$ |
| **Decl** | $\{ \textbf{int}, \textbf{float}, \textbf{id}, \textbf{if}, \textbf{while} \}$ |
| **Tipo** | $\{ \textbf{id} \}$ |
| **ListaVar** | $\{ \textbf{;} \}$ |
| **ListaVar'** | $\{ \textbf{;} \}$ |
| **Sentencias** | $\{ \mathbf{\$}, \textbf{else} \}$ |
| **Sentencias'** | $\{ \mathbf{\$}, \textbf{else} \}$ |
| **Sentencia** | $\{ \textbf{id}, \textbf{if}, \textbf{while}, \mathbf{\$}, \textbf{else} \}$ |
| **Expr** | $\{ \textbf{;}, \textbf{)} \}$ |
| **Expr'** | $\{ \textbf{;}, \textbf{)} \}$ |
| **Term** | $\{ \textbf{+}, \textbf{-}, \textbf{;}, \textbf{)} \}$ |
| **Term'** | $\{ \textbf{+}, \textbf{-}, \textbf{;}, \textbf{)} \}$ |
| **Factor** | $\{ \textbf{*}, \textbf{/}, \textbf{+}, \textbf{-}, \textbf{;}, \textbf{)} \}$ |

---

4. Mostrar en el archivo la construcción de la tabla de análisis sintáctico predictivo para _G'_. (1 pt.)

La tabla $M[N, T]$ indica qué producción utilizar dado un No Terminal en la cima de la pila y un Token de entrada.

*(Nota: Las celdas vacías indican error de sintaxis).*

| No Term | int | float | id | num | ; | , | = | if | else | while | + | - | * | / | ( | ) | $ |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| **Prog** | Prod 1 | Prod 1 | | | | | | | | | | | | | | | |
| **Decls** | Prod 2 | Prod 2 | | | | | | | | | | | | | | | |
| **Decls'** | Prod 3 | Prod 3 | $\epsilon$ | | | | | $\epsilon$ | | $\epsilon$ | | | | | | | |
| **Decl** | Prod 5 | Prod 5 | | | | | | | | | | | | | | | |
| **Tipo** | Prod 6 | Prod 7 | | | | | | | | | | | | | | | |
| **LVar** | | | Prod 8 | | | | | | | | | | | | | | |
| **LVar'** | | | | | $\epsilon$ | Prod 9 | | | | | | | | | | | |
| **Stmts** | | | Prod 11 | | | | | Prod 11 | | Prod 11 | | | | | | | |
| **Stmts'** | | | Prod 12 | | | | | Prod 12 | $\epsilon$ | Prod 12 | | | | | | | $\epsilon$ |
| **Stmt** | | | Prod 14 | | | | | Prod 15 | | Prod 16 | | | | | | | |
| **Expr** | | | Prod 17 | Prod 17 | | | | | | | | | | | Prod 17 | | |
| **Expr'** | | | | | $\epsilon$ | | | | | | Prod 18 | Prod 19 | | | | $\epsilon$ | |
| **Term** | | | Prod 21 | Prod 21 | | | | | | | | | | | Prod 21 | | |
| **Term'** | | | | | $\epsilon$ | | | | | | $\epsilon$ | $\epsilon$ | Prod 22 | Prod 23 | | $\epsilon$ | |
| **Factor**| | | Prod 26 | Prod 27 | | | | | | | | | | | Prod 25 | | |

---

5. Sustituir el contenido del Analizador Léxico (lexer.ll) con el implementado en la segunda práctica. (0.5 pts.)

El analizador sintáctico se implementó utilizando el algoritmo de descenso predictivo guiado por tabla en C++.

* Se definieron los enumeradores `Token` y `NoTerm` en `Symbols.hpp`.
* Se cargó la gramática $G'$ y la tabla predictiva $M$ en `ParserLL::loadTable`.
* El método `ParserLL::parse` utiliza una pila explícita para validar la cadena de entrada contra las producciones.

### Pruebas Realizadas
El parser aceptó correctamente el archivo de prueba base y se generaron casos adicionales para validar la robustez (archivos `test_valid_1`, `test_invalid_1`, etc.).

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
