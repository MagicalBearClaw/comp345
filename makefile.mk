OUTDIR = bin
SRC = src
INCLUDES = includes
OBJS = $(OUTDIR)\indexer.o $(OUTDIR)\document.o $(OUTDIR)\util.o $(OUTDIR)\stopword.o $(OUTDIR)\tokenizer.o $(OUTDIR)\default_tokenizer_strategy.o $(OUTDIR)\query_result.o
CC = g++
DEBUG = -g
CFLAGS = -c $(DEBUG)
FLAGS = -std=c++11

app.exe: $(OBJS) $(OUTDIR)\app.o
	$(CC) $(DEBUG) $(FLAGS) $(OBJS) $(OUTDIR)\app.o -o app.exe

googler.exe: $(OBJS) $(OUTDIR)\googler.o
	$(CC) $(DEBUG) $(FLAGS) $(OBJS) $(OUTDIR)\googler.o -o googler.exe
	
$(OUTDIR)\googler.o : $(SRC)\googler.cpp $(INCLUDES)\googler.h
	$(CC) $(CFLAGS) $(FLAGS) $(SRC)\googler.cpp -o $(OUTDIR)\googler.o


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

$(OUTDIR)\app.o : $(SRC)\app.cpp $(INCLUDES)\app.h
	$(CC) $(CFLAGS) $(FLAGS) $(SRC)\app.cpp -o $(OUTDIR)\app.o

$(OUTDIR)\query_result.o : $(SRC)\query_result.cpp $(INCLUDES)\query_result.h
	$(CC) $(CFLAGS) $(FLAGS) $(SRC)\query_result.cpp -o $(OUTDIR)\query_result.o