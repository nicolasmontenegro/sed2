# target: dependencies
# [tab]	system commands

# -c elimina el procesa de linking y genera un .o por cada archivo fuente
# a este momento, no es necesario linkear con ninguna biblioteca
# ejemplo: g++ -c fuente1.cpp => fuente1.o
# -o genera el ejecutable final
# ejemplo: g++ fuente1.o fuente2.o fuente3.o -l<biblioteca> -o final => final
# -l<biblioteca>
# -L<directorio_biblioteca>
# -I<directorio_include>

# recordar que los ejecutable solo necesitan de los ficheros objetos y de las bibliotecas
# mientras que los ficheros objetos necesitan de los codigos fuente y de las cabeceras

CFLAGS=-c -Wall
CLIBS=-lm

all: exp

exp: buffer.o producer.o recognizer.o writer.o main.o
	u++ buffer.o producer.o recognizer.o writer.o main.o $(CLIBS) -o exp

buffer.o: buffer.h buffer.cpp
	u++ $(CFLAGS) buffer.cpp

producer.o: producer.h producer.cpp
	u++ $(CFLAGS) producer.cpp

recognizer.o: recognizer.h recognizer.cpp
	u++ $(CFLAGS) recognizer.cpp

writer.o: writer.h writer.cpp
	u++ $(CFLAGS) writer.cpp

main.o: main.cpp
	u++ $(CFLAGS) main.cpp

clean:
	rm -rf exp *.o