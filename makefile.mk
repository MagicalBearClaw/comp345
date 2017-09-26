OUTDIR = bin
OBJS = $(OUTDIR)\indexer.o
CC = g++
DEBUG = -g
CFLAGS = -c $(DEBUG)

app.exe: $(OBJS)
	$(CC) $(DEBUG) $(OBJS) -o app.exe

$(OUTDIR)\indexer.o : indexer.cpp
	$(CC) $(CFLAGS) indexer.cpp -o $(OUTDIR)\indexer.o

