all:
	gcc -W -Wall lerFileProc.h lerFileProc.c processarDadosProc.h processarDadosProc.c InterfaceInicial.c -lncurses -o tela

run:
	./tela

clean:
