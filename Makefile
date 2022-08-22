.PHONY: build clean

build: calculator.ll calculator.yy calculator.c calculator.h
	bison -vdty -o calculator.tab.c calculator.yy
	flex -o calculator.lex.c calculator.ll
	gcc calculator.c calculator.tab.c calculator.lex.c -o calculator

clean:
	rm -rf calculator.lex.c calculator.output calculator.tab.c calculator.tab.h calculator