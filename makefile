
all: tesina

tesina.tab.c tesina.tab.h:	tesina.y
	bison -t -v -d tesina.y

lex.yy.c: tesina.l tesina.tab.h
	flex tesina.l

tesina: lex.yy.c tesina.tab.c tesina.tab.h tesinaFun.c
	gcc -o tesina tesinaFun.c tesina.tab.c lex.yy.c

clean:
	rm tesina tesinaFun.c tesina.tab.c lex.yy.c tesina.tab.h tesina.output