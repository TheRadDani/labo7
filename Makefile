CC=gcc
LIBS=-pg -lm 
#librerias extra
#variable de compilador
SFLAGS=-g -Wall -c
#flag de creacion de archivos.o
CFLAGS=-I./include/
#incluir archivos de encabezado en la ruta 
all: programa
programa: main.o lista.o
	$(CC) -o ejecutable lista.c main.c  $(CFLAGS) $(LIBD)
	mv ejecutable ../build/
	mv *.o ../obj/
#mover los archivos extension .o a build 
#mover el ejecutable a build
main.o: src/main.c
	$(CC) $(SFLAGS) $(CFLAGS) $< -o $@
lista.o: src/lista.c
	$(CC) $(SFLAGS) $(CFLAGS) $< -o $@
#al ejecutar make clen, borra todos los archivo con extension.o 
#el programa se podria borrar con make clean pero en el ubicacion del archivo
#la cual es build
.PHONY: clean
clean:
	rm -rf obj/*.o
#eliminar archivos.o en directorio build 
	rm -rf build/ejecutable
