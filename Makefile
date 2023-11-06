CXX = g++
CXXFLAGS = -Wall -pedantic -std=c++14 -Wno-long-long -g
SOURCE_DIR = src
SOURCES = $(wildcard $(SOURCE_DIR)/*.c)
HEADERS = $(wildcard $(SOURCE_DIR)/*.h)
OBJS = $(SOURCES: $(SOURCE_DIR)/%.c = $(SOURCE_DIR)/%.o)
EXEC = a.out

all: doc compile

compile: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS)

clean:
	rm -rf $(SOURCE_DIR)/.o $(EXEC) doc 2>/dev/null

run:
	./$(EXEC)

doc: Doxyfile README.md $(HEADERS)
	doxygen Doxyfile

reedmuller.o: $(SOURCE_DIR)/reedmuller.h $(SOURCE_DIR)/reedmuller.c $(SOURCE_DIR)/vector.h $(SOURCE_DIR)/matrix.h $(SOURCE_DIR)/util.h
matrix.o: $(SOURCE_DIR)/matrix.h $(SOURCE_DIR)/matrix.c $(SOURCE_DIR)/vector.h
vector.o: $(SOURCE_DIR)/vector.h $(SOURCE_DIR)/vector.c
util.o: $(SOURCE_DIR)/util.h $(SOURCE_DIR)/util.c