<p  align="center">
  <img  width="200"  src="https://www.fciencias.unam.mx/sites/default/files/logoFC_2.png"  alt="">  <br>Compiladores  2026-1 <br>
  Práctica 2: Implementación de un Analizador Sintáctico de Descenso Recursivo <br> Alumno: Morales Aguilar Marcos
</p>

## Implementación de un Analizador Sintáctico de Descenso Recursivo

### Estructura del directorio
```c++
p3
├── README.md
└── src //carpeta de código
    ├── headers
    │   ├── Lexer.hpp   //header de la clase Lexer
    │   ├── Parser.hpp  //header de la clase Parser
    │   └── Symbols.hpp //definición de símbolos
    ├── lexer.ll        //definición del an. léxico
    ├── main.cpp        //contiene la función principal del programa
    ├── Makefile        //boceto de Makefile (no funciona aún)
    ├── Parser.cpp      //código fuente de la clase Parser
    └── prueba          ////archivo de entrada para el analizador (léxico y sintáctico)
```

### Uso

#### Compilación

```bash
$ cd src/
$ flex++ lexer.ll
$ g++ Lexer.cpp Parser.cpp main.cpp -o analyzer
```

#### Ejecución

```bash
$ ./analyzer prueba
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
>> expresion → expresion **+** expresion | expresion **-** expresion | expresion __\*__ expresion | expresion **\/** expresión | _**identificador**_ | **_numero_** <br>
>> expresion → **(** expresion **)** <br>
}


1. Determinar en un archivo Readme, en formato Markdown (.md) o LaTeX (.tex) -- con su respectivo PDF, para este último -- , los conjuntos _N_, _Σ_ y el símbolo inicial _S_.  (0.5 pts.)

* **Símbolo Inicial ($S$):** `programa`
* **Terminales ($\Sigma$):** `{ int, float, ;, ,, identificador, =, if, else, while, (, ), +, -, *, /, numero }`
* **No Terminales ($N$):** `{ programa, declaraciones, declaracion, tipo, lista_var, sentencias, sentencia, expresion }`

2. Mostrar en el archivo el proceso de eliminación de ambigüedad o justificar, en caso de no ser necesario. (1 pts.).

La producción original de `expresion` es ambigua ya que no define precedencia de operadores ni asociatividad.
> `expresion → expresion + expresion | ... | numero`

3. Mostrar en el archivo el proceso de eliminación de la recursividad izquierda o justificar, en caso de no ser necesario. (1 pts.)

Las producciones `declaraciones`, `lista_var`, `sentencias` y `expresion` presentaban recursividad izquierda (ej. `A -> A alpha`). Se eliminó transformándola en recursividad derecha mediante la regla estándar: $A \to \beta A'$ y $A' \to \alpha A' | \epsilon$.

Ejemplo con `expresion`:
* Original: `E -> E + T | T`
* Transformada: `E -> T E'`, `E' -> + T E' | epsilon`

4. Mostrar en el archivo el proceso de factorización izquierda o justificar, en caso de no ser necesario. (1 pts.)

Dado que los conjuntos *First* de las producciones alternativas para cada No-Terminal son disjuntos (por ejemplo, `sentencia` puede empezar con `id`, `if` o `while`), no fue necesaria una factorización izquierda adicional.

5. Mostrar en el archivo los nuevos conjuntos _N_ y _P_. (0.5 pts.)

**Conjunto $N$:** `{ programa, declaraciones, declaracion, tipo, lista_var, lista_var_prima, sentencias, sentencia, expresion, expresion_prima, termino, termino_prima, factor }`

**Conjunto $P$:**
1.  **programa** $\to$ declaraciones sentencias
2.  **declaraciones** $\to$ declaracion declaraciones | $\epsilon$
3.  **declaracion** $\to$ tipo lista_var **;**
4.  **tipo** $\to$ **int** | **float**
5.  **lista_var** $\to$ **identificador** lista_var_prima
6.  **lista_var_prima** $\to$ **,** **identificador** lista_var_prima | $\epsilon$
7.  **sentencias** $\to$ sentencia sentencias | $\epsilon$
8.  **sentencia** $\to$ **identificador** **=** expresion **;**
    | **if** **(** expresion **)** sentencias **else** sentencias
    | **while** **(** expresion **)** sentencias
9.  **expresion** $\to$ termino expresion_prima
10. **expresion_prima** $\to$ **+** termino expresion_prima | **-** termino expresion_prima | $\epsilon$
11. **termino** $\to$ factor termino_prima
12. **termino_prima** $\to$ **\*** factor termino_prima | **/** factor termino_prima | $\epsilon$
13. **factor** $\to$ **(** expresion **)** | **identificador** | **numero**

6. Definir el Analizador Léxico (lexer.ll) con las acciones léxicas correspondientes. (2 pts.)
7. Implementar el Analizador Sintáctico (Parser.cpp) de descenso recursivo, documentando las funciones de cada No-Terminal, de forma que el programa descrito en el archivo _prueba_ sea reconocido y aceptado por el analizador resultante. (4 pts.)

---
#### Extras

8. Documentar el código. (0.25pts)
9. Proponer 4 archivos de prueba nuevos, 2 válidos y 2 inválidos. (0.25pts)
10. Modificar el Makefile para poder simplificar el proceso de compilación de la práctica. (1pt)
