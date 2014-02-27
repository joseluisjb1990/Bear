CC    ?= clang
CXX   ?= clang++
 
EXE = bear
 
CDEBUG = -g -Wall
 
CXXDEBUG = -g -Wall
 
CSTD = -std=c99
CXXSTD = -std=c++11
 
CFLAGS = -O0  $(CDEBUG) $(CSTD) 
CXXFLAGS = -O0  $(CXXDEBUG) $(CXXSTD)
 
 
CPPOBJ = bear bear_driver
SOBJ =  parser lexer
 
FILES = $(addsuffix .cc, $(CPPOBJ))
 
OBJS  = $(addsuffix .o, $(CPPOBJ))
 
CLEANLIST =  $(addsuffix .o, $(OBJ)) $(OBJS) \
    			 bear_parser.tab.cc bear_parser.tab.hh \
				 location.hh position.hh \
			    stack.hh parser.o bear_parser.output\
				 lexer.o lexer.yy.cc $(EXE)\
 
.PHONY: all
all: calc
 
calc: $(FILES)
	$(MAKE) $(SOBJ)
	$(MAKE) $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXE) $(OBJS) parser.o lexer.o $(LIBS)
 
 
parser: bear_parser.yy
	bison -d -v bear_parser.yy
	$(CXX) $(CXXFLAGS) -c -o parser.o bear_parser.tab.cc
 
lexer: bear_scanner.ll
	flex --outfile=lexer.yy.cc  $<
	$(CXX)  $(CXXFLAGS) -c lexer.yy.cc -o lexer.o
 
 
.PHONY: clean
clean:
	rm -rf $(CLEANLIST)
