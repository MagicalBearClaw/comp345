OUTDIR = bin
SRC = src
INCLUDES = includes
OBJS = $(OUTDIR)\indexer.o $(OUTDIR)\document.o $(OUTDIR)\util.o $(OUTDIR)\stopword.o $(OUTDIR)\main.o $(OUTDIR)\tokenizer.o $(OUTDIR)\ITokenizerStratergy.o
CC = g++
DEBUG = -g
CFLAGS = -c $(DEBUG)
FLAGS = -std=c++11

app.exe: $(OBJS)
	$(CC) $(DEBUG) $(FLAGS) $(OBJS) -o app.exe

$(OUTDIR)\indexer.o : indexer.cpp indexer.h
	$(CC) $(CFLAGS) $(FLAGS) indexer.cpp -o $(OUTDIR)\indexer.o

$(OUTDIR)\ITokenizerStratergy.o : $(INCLUDES)\ITokenizerStratergy.h
	$(CC) $(CFLAGS) $(FLAGS) $(INCLUDES)\ITokenizerStratergy.h -o $(OUTDIR)\ITokenizerStratergy.o

$(OUTDIR)\tokenizer.o : $(SRC)\tokenizer.cpp  $(INCLUDES)\tokenizer.h
	$(CC) $(CFLAGS) $(FLAGS) $(SRC)\tokenizer.cpp -o $(OUTDIR)\tokenizer.o

$(OUTDIR)\document.o : $(SRC)\document.cpp $(INCLUDES)\document.h
	$(CC) $(CFLAGS) $(FLAGS) $(SRC)\document.cpp -o $(OUTDIR)\document.o

$(OUTDIR)\stopword.o : $(SRC)\stopword.cpp $(INCLUDES)\stopword.h
	$(CC) $(CFLAGS) $(FLAGS) $(SRC)\stopword.cpp -o $(OUTDIR)\stopword.o
	
$(OUTDIR)\util.o : $(SRC)\util.cpp $(INCLUDES)\util.h
	$(CC) $(CFLAGS) $(FLAGS) $(SRC)\util.cpp -o $(OUTDIR)\util.o

$(OUTDIR)\main.o : $(SRC)\main.cpp 
	$(CC) $(CFLAGS) $(FLAGS) $(SRC)\main.cpp -o $(OUTDIR)\main.o