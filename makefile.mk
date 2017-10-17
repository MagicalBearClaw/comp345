OUTDIR = bin
SRC = src
INCLUDES = includes
OBJS = $(OUTDIR)\indexer.o $(OUTDIR)\document.o $(OUTDIR)\util.o $(OUTDIR)\stopword.o $(OUTDIR)\tokenizer.o $(OUTDIR)\default_tokenizer_strategy.o
CC = g++
DEBUG = -g
CFLAGS = -c $(DEBUG)
FLAGS = -std=c++11

app.exe: $(OBJS)
	$(CC) $(DEBUG) $(FLAGS) $(OBJS) -o app.exe

$(OUTDIR)\indexer.o : $(SRC)\indexer.cpp $(INCLUDES)\indexer.h
	$(CC) $(CFLAGS) $(FLAGS) $(SRC)\indexer.cpp -o $(OUTDIR)\indexer.o

$(OUTDIR)\i_tokenizer_strategy.o : $(INCLUDES)\i_tokenizer_strategy.h
	$(CC) $(CFLAGS) $(FLAGS) $(INCLUDES)\i_tokenizer_strategy.h -o $(OUTDIR)\i_tokenizer_strategy.o

$(OUTDIR)\default_tokenizer_strategy.o : $(INCLUDES)\default_tokenizer_strategy.h $(SRC)\default_tokenizer_strategy.cpp
	$(CC) $(CFLAGS) $(FLAGS) $(SRC)\default_tokenizer_strategy.cpp -o $(OUTDIR)\default_tokenizer_strategy.o

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