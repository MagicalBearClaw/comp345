OUTDIR = bin
SRC = src
INCLUDES = includes
#TODO should we seperate OBJS into smaller subsets based on what each exe needs?
OBJS = $(OUTDIR)\indexer.o $(OUTDIR)\document.o $(OUTDIR)\sentence.o $(OUTDIR)\util.o $(OUTDIR)\stopword.o $(OUTDIR)\tokenizer.o $(OUTDIR)\default_tokenizer_strategy.o $(OUTDIR)\query_result.o $(OUTDIR)\term_index.o
CC = g++
DEBUG = -g
CFLAGS = -c $(DEBUG)
FLAGS = -std=c++11

#TODO add missing classes to be compiled
indexing.exe: $(OBJS) $(OUTDIR)\indexing.o
	$(CC) $(DEBUG) $(FLAGS) $(OBJS) $(OUTDIR)\indexing.o -o indexing.exe

googler.exe: $(OBJS) $(OUTDIR)\googler.o
	$(CC) $(DEBUG) $(FLAGS) $(OBJS) $(OUTDIR)\googler.o -o googler.exe

summarizer.exe: $(OBJS) $(OUTDIR)\summarizer.o
	$(cc) $(DEBUG) $(FLAGS) $(OBJS) $(OUTDIR)\summarizer.o -o summarizer.exe
	
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

$(OUTDIR)\sentence.o : $(SRC)\sentence.cpp $(INCLUDES)\sentence.h
	$(CC) $(CFLAGS) $(FLAGS) $(SRC)\sentence.cpp -o $(OUTDIR)\sentence.o

$(OUTDIR)\stopword.o : $(SRC)\stopword.cpp $(INCLUDES)\stopword.h
	$(CC) $(CFLAGS) $(FLAGS) $(SRC)\stopword.cpp -o $(OUTDIR)\stopword.o
	
$(OUTDIR)\util.o : $(SRC)\util.cpp $(INCLUDES)\util.h
	$(CC) $(CFLAGS) $(FLAGS) $(SRC)\util.cpp -o $(OUTDIR)\util.o

$(OUTDIR)\indexing.o : $(SRC)\indexing.cpp $(INCLUDES)\indexing.h
	$(CC) $(CFLAGS) $(FLAGS) $(SRC)\indexing.cpp -o $(OUTDIR)\indexing.o

$(OUTDIR)\query_result.o : $(SRC)\query_result.cpp $(INCLUDES)\query_result.h
	$(CC) $(CFLAGS) $(FLAGS) $(SRC)\query_result.cpp -o $(OUTDIR)\query_result.o

$(OUTDIR)\term_index.o : $(SRC)\term_index.cpp $(INCLUDES)\term_index.h
	$(CC) $(CFLAGS) $(FLAGS) $(SRC)\term_index.cpp -o $(OUTDIR)\term_index.o

$(OUTDIR)\document_indexer.o : $(SRC)\document_indexer.cpp $(INCLUDES)\document_indexer.h
	$(CC) $(CFLAGS) $(FLAGS) $(SRC)\document_indexer.cpp -o $(OUTDIR)\document_indexer.o

$(OUTDIR)\sentence_indexer.o : $(SRC)\sentence_indexer.cpp $(INCLUDES)\sentence_indexer.h
	$(CC) $(CFLAGS) $(FLAGS) $(SRC)\sentence_indexer.cpp -o $(OUTDIR)\sentence_indexer.o