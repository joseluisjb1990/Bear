LEX    = flex
BISON  = bison

lexer:	lex.yy.cc
		g++ $< -o $@

lex.yy.cc:	lexer.l
		flex -+ $<

clean:
		rm lexer lex.yy.cc
