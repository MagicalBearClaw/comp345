OUTDIR = bin
OBJS = $(OUTDIR)\indexer.o $(OUTDIR)\document.o
CC = g++
DEBUG = -g
CFLAGS = -c $(DEBUG)

app.exe: $(OBJS)
	$(CC) $(DEBUG) $(OBJS) -o app.exe

$(OUTDIR)\indexer.o : indexer.cpp indexer.h
	$(CC) $(CFLAGS) indexer.cpp -o $(OUTDIR)\indexer.o

$(OUTDIR)\document.o : document.cpp document.h
	$(CC) $(CFLAGS) document.cpp -o $(OUTDIR)\document.o