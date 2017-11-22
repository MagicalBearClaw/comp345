OUTDIR = bin
SRC = src
INCLUDES = includes
OBJS = $(OUTDIR)/indexer.o $(OUTDIR)/sentence_tokenizer_strategy.o $(OUTDIR)/word_tokenizer_strategy.o $(OUTDIR)/tokenizer.o $(OUTDIR)/document.o $(OUTDIR)/sentence.o $(OUTDIR)/stopword.o $(OUTDIR)/util.o $(OUTDIR)/index_item.o $(OUTDIR)/term_index.o $(OUTDIR)/query_result.o $(OUTDIR)/document_indexer.o $(OUTDIR)/sentence_indexer.o $(OUTDIR)/movie_indexer.o $(OUTDIR)/movie.o
CC = g++
DEBUG = -O
CFLAGS = -c $(DEBUG)
FLAGS = -std=c++11

indexing.exe: $(OBJS) $(OUTDIR)/indexing.o
	$(CC) $(DEBUG) $(FLAGS) $(OBJS) $(OUTDIR)/indexing.o -o indexing.exe

googler.exe: $(OBJS) $(OUTDIR)/googler.o
	$(CC) $(DEBUG) $(FLAGS) $(OBJS) $(OUTDIR)/googler.o -o googler.exe

summarizer.exe: $(OBJS) $(OUTDIR)/summarizer.o
	$(CC) $(DEBUG) $(FLAGS) $(OBJS) $(OUTDIR)/summarizer.o -o summarizer.exe

recommender.exe: $(OBJS) $(OUTDIR)/recommender.o
	$(CC) $(DEBUG) $(FLAGS) $(OBJS) $(OUTDIR)/recommender.o -o recommender.exe

$(OUTDIR)/indexing.o : $(SRC)/indexing.cpp $(INCLUDES)/indexing.h
	$(CC) $(CFLAGS) $(FLAGS) $(SRC)/indexing.cpp -o $(OUTDIR)/indexing.o

$(OUTDIR)/googler.o : $(SRC)/googler.cpp $(INCLUDES)/googler.h
	$(CC) $(CFLAGS) $(FLAGS) $(SRC)/googler.cpp -o $(OUTDIR)/googler.o

$(OUTDIR)/summarizer.o : $(SRC)/summarizer.cpp $(INCLUDES)/summarizer.h
	$(CC) $(CFLAGS) $(FLAGS) $(SRC)/summarizer.cpp -o $(OUTDIR)/summarizer.o

$(OUTDIR)/indexer.o : $(SRC)/indexer.cpp $(INCLUDES)/indexer.h
	$(CC) $(CFLAGS) $(FLAGS) $(SRC)/indexer.cpp -o $(OUTDIR)/indexer.o

$(OUTDIR)/abstract_tokenizer_strategy.o : $(INCLUDES)/abstract_tokenizer_strategy.h
	$(CC) $(CFLAGS) $(FLAGS) $(INCLUDES)/abstract_tokenizer_strategy.h -o $(OUTDIR)/abstract_tokenizer_strategy.o

$(OUTDIR)/sentence_tokenizer_strategy.o : $(SRC)/sentence_tokenizer_strategy.cpp $(INCLUDES)/sentence_tokenizer_strategy.h
	$(CC) $(CFLAGS) $(FLAGS) $(SRC)/sentence_tokenizer_strategy.cpp -o $(OUTDIR)/sentence_tokenizer_strategy.o

$(OUTDIR)/word_tokenizer_strategy.o : $(INCLUDES)/word_tokenizer_strategy.h $(SRC)/word_tokenizer_strategy.cpp
	$(CC) $(CFLAGS) $(FLAGS) $(SRC)/word_tokenizer_strategy.cpp -o $(OUTDIR)/word_tokenizer_strategy.o

$(OUTDIR)/tokenizer.o : $(SRC)/tokenizer.cpp  $(INCLUDES)/tokenizer.h
	$(CC) $(CFLAGS) $(FLAGS) $(SRC)/tokenizer.cpp -o $(OUTDIR)/tokenizer.o

$(OUTDIR)/document.o : $(SRC)/document.cpp $(INCLUDES)/document.h
	$(CC) $(CFLAGS) $(FLAGS) $(SRC)/document.cpp -o $(OUTDIR)/document.o

$(OUTDIR)/sentence.o : $(SRC)/sentence.cpp $(INCLUDES)/sentence.h
	$(CC) $(CFLAGS) $(FLAGS) $(SRC)/sentence.cpp -o $(OUTDIR)/sentence.o

$(OUTDIR)/stopword.o : $(SRC)/stopword.cpp $(INCLUDES)/stopword.h
	$(CC) $(CFLAGS) $(FLAGS) $(SRC)/stopword.cpp -o $(OUTDIR)/stopword.o
	
$(OUTDIR)/util.o : $(SRC)/util.cpp $(INCLUDES)/util.h
	$(CC) $(CFLAGS) $(FLAGS) $(SRC)/util.cpp -o $(OUTDIR)/util.o

$(OUTDIR)/index_item.o : $(SRC)/index_item.cpp $(INCLUDES)/index_item.h
	$(CC) $(CFLAGS) $(FLAGS) $(SRC)/index_item.cpp -o $(OUTDIR)/index_item.o

$(OUTDIR)/term_index.o : $(SRC)/term_index.cpp $(INCLUDES)/term_index.h
	$(CC) $(CFLAGS) $(FLAGS) $(SRC)/term_index.cpp -o $(OUTDIR)/term_index.o

$(OUTDIR)/query_result.o : $(SRC)/query_result.cpp $(INCLUDES)/query_result.h
	$(CC) $(CFLAGS) $(FLAGS) $(SRC)/query_result.cpp -o $(OUTDIR)/query_result.o

$(OUTDIR)/document_indexer.o : $(SRC)/document_indexer.cpp $(INCLUDES)/document_indexer.h
	$(CC) $(CFLAGS) $(FLAGS) $(SRC)/document_indexer.cpp -o $(OUTDIR)/document_indexer.o

$(OUTDIR)/sentence_indexer.o : $(SRC)/sentence_indexer.cpp $(INCLUDES)/sentence_indexer.h
	$(CC) $(CFLAGS) $(FLAGS) $(SRC)/sentence_indexer.cpp -o $(OUTDIR)/sentence_indexer.o
	
$(OUTDIR)/recommender.o : $(SRC)/recommender.cpp
	$(CC) $(CFLAGS) $(FLAGS) $(SRC)/recommender.cpp -o $(OUTDIR)/recommender.o
	
$(OUTDIR)/movie_indexer.o : $(SRC)/movie_indexer.cpp $(INCLUDES)/movie_indexer.h
	$(CC) $(CFLAGS) $(FLAGS) $(SRC)/movie_indexer.cpp -o $(OUTDIR)/movie_indexer.o

$(OUTDIR)/movie.o : $(SRC)/movie.cpp $(INCLUDES)/movie.h
	$(CC) $(CFLAGS) $(FLAGS) $(SRC)/movie.cpp -o $(OUTDIR)/movie.o
