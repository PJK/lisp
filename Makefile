CPPFLAGS += -std=c++11 -pedantic

ALL_BUT_BIN := 	$(patsubst %.cpp,%.o,$(patsubst src/%,build/%,$(wildcard src/*.cpp))) \
				$(patsubst %.cpp,%.o,$(patsubst src/%,build/%,$(wildcard src/corelib/*.cpp))) \
				$(patsubst %.cpp,%.o,$(patsubst src/%,build/%,$(wildcard src/value/*.cpp))) \
				$(patsubst %.cpp,%.o,$(patsubst src/%,build/%,$(wildcard src/ast/*.cpp))) \
				$(patsubst %.cpp,%.o,$(patsubst src/%,build/%,$(wildcard src/exceptions/*.cpp))) \
				build/tokenizer.o build/parser.o

.PHONY: clean docs

build/parser.cpp: src/parser.y build/.sentinel
	bison -d -o $@ src/parser.y

build/parser.hpp: build/parser.cpp 

build/tokenizer.cpp: src/tokenizer.l build/parser.hpp
	flex -o $@ src/tokenizer.l

build/parser.o: build/parser.cpp
	$(CXX) -c $(CPPFLAGS) -o $@ $<

build/tokenizer.o: build/tokenizer.cpp
	$(CXX) -c $(CPPFLAGS) -Wno-deprecated-register -o $@ $<

build/%.o: src/%.cpp build/.sentinel
	$(CXX) -c $(CPPFLAGS) -o $@ $<

build/bin/simple_parser: $(ALL_BUT_BIN) build/bin/simple_parser.o
	$(CXX) $(CPPFLAGS) -o $@ $^ -lpthread

build/bin/interpreter: $(ALL_BUT_BIN) build/bin/interpreter.o
	$(CXX) $(CPPFLAGS) -o $@ $^ -lpthread

clean:
	$(RM) -r build
	$(RM) -r docs

build/.sentinel:
	mkdir -p build/ast
	mkdir -p build/value
	mkdir -p build/corelib
	mkdir -p build/bin
	mkdir -p build/exceptions
	touch build/.sentinel

docs:
	doxygen

all: build/bin/simple_parser build/bin/interpreter docs