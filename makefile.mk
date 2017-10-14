OUTDIR = bin
OBJS = $(OUTDIR)\indexer.o $(OUTDIR)\document.o
CC = g++
DEBUG = -g
CFLAGS = -c $(DEBUG)
FLAGS = -std=c++11

app.exe: $(OBJS)
	$(CC) $(DEBUG) $(FLAGS) $(OBJS) -o app.exe

$(OUTDIR)\indexer.o : indexer.cpp indexer.h
	$(CC) $(CFLAGS) $(FLAGS) indexer.cpp -o $(OUTDIR)\indexer.o

$(OUTDIR)\document.o : document.cpp document.h
	$(CC) $(CFLAGS) $(FLAGS) document.cpp -o $(OUTDIR)\document.o

$(OUTDIR)\stopword.o : stopword.cpp stopword.h
	$(CC) $(CFLAGS) $(FLAGS) stopword.cpp -o $(OUTDIR)\document.o