# mi wea de makefile para eda
# version lab 3 xD

# archivos de entrada y salida
executable = Prueba.o
debuggable = debug.out
#headers    =        lista.h grafo.h constantes.h
headers    =
#source     = main.c lista.c grafo.c
source     = ArbolAVL.c
objects    = $(source:.c=.o)

documents  = informe.pdf
zipfile    = lab3.zip

# compilador y banderas (active advertencias)
CC     = gcc
CFLAGS =
#CFLAGS = -Wall

# esta es la primera regla
# cuando escribo `make` en la terminal se ejecuta esta
# lo que hace es verificar si necesita compilar los .o
#    de nuevo, y si al menos uno cambio, compila a.out
$(executable) : $(objects)
	$(CC) $(CFLAGS) $(objects) -o $(executable)

# esta regla compila los .o
# como la escribi, cualquier cambio a un .h recompila
#    todos los .o xDD pero con tan pocos archivos no
#    importa en verdad
$(objects) : $(headers)

# no me interesa que se creen archivos "clean" ni "dist"
.PHONY : clean dist debug

# esta regla se llama con `make clean` y borra los .o,
#    el a.out y el .zip
clean :
	rm -f $(executable) $(objects) $(zipfile)

# esta regla se llama usando `make dist` y crea un .zip
#    con los .c, los .h y el informe, si cambiaron
# si ya existe lo borra primero porque me pasaban weas
dist : $(headers) $(source) $(documents)
	rm -f $(zipfile)
	@zip $(zipfile) $(headers) $(source) $(documents)

debug :
	$(CC) $(CFLAGS) -ggdb -o $(debuggable) $(source)
