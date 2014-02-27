CC    ?= clang
CXX   ?= clang++
 
EXE = calc++
 
CDEBUG = -g -Wall
 
CXXDEBUG = -g -Wall
 
CSTD = -std=c99
CXXSTD = -std=c++11
 
CFLAGS = -O0  $(CDEBUG) $(CSTD) 
CXXFLAGS = -O0  $(CXXDEBUG) $(CXXSTD)
 
 
CPPOBJ = calc++ calc++-driver
SOBJ =  parser lexer
 
FILES = $(addsuffix .cc, $(CPPOBJ))
 
OBJS  = $(addsuffix .o, $(CPPOBJ))
 
CLEANLIST =  $(addsuffix .o, $(OBJ)) $(OBJS) \
    			 calc++-parser.tab.cc calc++-parser.tab.hh \
				 location.hh position.hh \
			    stack.hh parser.o calc++-parser.output\
				 lexer.o lexer.yy.cc $(EXE)\
 
.PHONY: all
all: calc
 
calc: $(FILES)
	$(MAKE) $(SOBJ)
	$(MAKE) $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXE) $(OBJS) parser.o lexer.o $(LIBS)
 
 
parser: calc++-parser.yy
	bison -d -v calc++-parser.yy
	$(CXX) $(CXXFLAGS) -c -o parser.o calc++-parser.tab.cc
 
lexer: calc++-scanner.ll
	flex --outfile=lexer.yy.cc  $<
	$(CXX)  $(CXXFLAGS) -c lexer.yy.cc -o lexer.o
 
 
.PHONY: clean
clean:
	rm -rf $(CLEANLIST)
