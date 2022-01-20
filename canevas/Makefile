IDIR = include
ODIR = obj
SDIR = src
JDIR = ../lib

CC = gcc -fPIC
CFLAGS = -g -Wall -I$(IDIR)
EXE = -o $(JDIR)/libDij.so

JINCLUDES = -I/usr/lib/jvm/java-11-openjdk-amd64/ -I/usr/lib/jvm/java-11-openjdk-amd64/include -I/usr/lib/jvm/java-11-openjdk-amd64/include/linux/


_DEPS = list.h tree.h dyntable.h heap.h list.h road.h town.h graph.h MyClass.h main.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ= list.o main.o tree.o dyntable.o heap.o list.o road.o town.o graph.o main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all : $(ODIR)/MyClass.o $(OBJ)
	$(CC) -shared $(EXE) $^


$(ODIR)/MyClass.o : $(SDIR)/MyClass.c $(DEPS)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

$(ODIR)/%.o : $(SDIR)/%.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

clean :
	rm -f $(ODIR)/*.o $(JDIR)/libDij.so

