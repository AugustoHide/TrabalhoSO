#include<curses.h>
#include<stdio.h>
#include<string.h>
#include"processarDadosProc.h"
#include"lerFileProc.h"

#define max_proc 100000
#define max_v_proc 10000

int main(){

	//initialize screen
	initscr();
	/* -------------------- CABEÇALHO --------------------*/
	//Título
	printw("------------ TOP - Trabalho de SO ------------");
	move(1, 0);

	//pid
	printw("PID");
	move(1,7);
	//uusuário
	printw("USUARIO");
	move(1,15);
	//prioridade
	printw("PRIORIDADE");
	move(1,25);
	//estado
	printw(" ESTADO");
	move(1,45);
	//%cpu
	printw("CPU");
	move(1,55);
	//tempo
	printw("TEMPO");
	move(1,65);
	//comando
	printw("COMANDO");
	move(1,75);


	/* -------------------- VERSÃO INICIAL do /proc --------------------*/
	move(2,0);

	int y = 2, x = 0;
	double cpuId[max_v_proc][2];

	repetir_exec(cpuId, &y, &x);
	
	getch();
	//dealocates memory ends ncurses
	endwin();
	/*double cpuId2[max_proc][2];
	ArmazenaCpuId(cpuId2);*/

	return 0;
}

