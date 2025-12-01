CXX=g++
EXE=analyzer
CXXFLAGS= -std=c++14 -Wall -g

# Archivos fuente
SRCS= main.cpp Parser.cpp Lexer.cpp

# Objetos
OBJS= $(SRCS:.cpp=.o)

.PHONY: all clean

all: $(EXE)

# Generar el Lexer C++ desde el archivo .ll
Lexer.cpp: lexer.ll
	flex lexer.ll

# Compilar el ejecutable
$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXE) $(OBJS)

clean:
	rm -f $(OBJS) $(EXE) Lexer.cpp