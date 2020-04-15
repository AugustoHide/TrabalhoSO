all:
	gcc -W -Wall lerFileProc.h lerFileProc.c InterfaceInicial.c -lncurses -o tela

run:
	./tela

clean:
