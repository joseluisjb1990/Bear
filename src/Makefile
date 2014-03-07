CPP = g++

EXE = bear

CDEBUG = -g -Wall

CPPDEBUG = -g -Wall

CPPFLAGS = -O0  $(CPPDEBUG)


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
all: bear

bear: $(FILES)
	$(MAKE) $(SOBJ)
	$(MAKE) $(OBJS)
	$(CPP) $(CPPFLAGS) -o $(EXE) $(OBJS) parser.o lexer.o $(LIBS)


parser: bear_parser.yy
	bison -d -v bear_parser.yy
	$(CPP) $(CPPFLAGS) -c -o parser.o bear_parser.tab.cc

lexer: bear_scanner.ll
	flex --outfile=lexer.yy.cc  $<
	$(CPP)  $(CPPFLAGS) -c lexer.yy.cc -o lexer.o


.PHONY: clean
clean:
	rm -rf $(CLEANLIST)
