
all: tesina

tesina.tab.c tesina.tab.h:	tesina.y
	bison -t -v -d tesina.y

lex.yy.c: tesina.l tesina.tab.h
	flex tesina.l

tesina: lex.yy.c tesina.tab.c tesina.tab.h TESINA.c
	gcc -w -o tesina TESINA.c functions/registroFunctions.c functions/newFunctions.c functions/evalFunctions.c functions/freeFunctions.c tesina.tab.c lex.yy.c

clean:
	rm tesina functions/TESINA.c tesina.tab.c lex.yy.c tesina.tab.h tesina.output