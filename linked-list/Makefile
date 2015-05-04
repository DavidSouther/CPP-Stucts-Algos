CXX=clang++
CXXFLAGS=-g -std=c++11 -Wall -pedantic #-DDEBUG
BIN=list

SRC=$(wildcard *.cc)

OBJ=$(SRC:%.cc=%.o)

all: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(BIN) $^

%.o: %.c
	$(CXX) $(CXXFLAGS) $@ -c $<

clean:
	rm -f *.o
	rm $(BIN)
