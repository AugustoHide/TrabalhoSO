#include<curses.h>
#include<stdio.h>
#include<string.h>
#include"processarDadosProc.h"
#include"lerFileProc.h"

#define max_proc 10000

int main(){

	//initialize screen
	initscr();
	/* -------------------- CABEÇALHO --------------------*/
	//Título
	printw("------------ TOP - Trabalho de SO ------------");
	move(1, 0);

	//pid
	printw("PID");
	move(1,5);
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
	double cpuId[max_proc][2];

	repetir_exec(cpuId, &y, &x);
	

	getch();
	//dealocates memory ends ncurses
	endwin();
	/*double cpuId2[max_proc][2];
	ArmazenaCpuId(cpuId2);*/

	return 0;
}


/*
int mostraProcessos(int* y, int* x){
	int n = 0;
	FILE* proc_file;
	char proc_adr[20], s_n[4];

	
	while(n < 10000){
		sprintf(s_n, "%d", n);
		strcpy(proc_adr,"/proc/");
		strcat(proc_adr, s_n);
		strcat(proc_adr, "/stat");
		proc_file = fopen(proc_adr, "r");
		if(proc_file != NULL){
			//chama função de leitura no /proc/n
			if(leituraProcN(y, x, s_n) == 0){
				return 0;
			}
			//printw("%s", s_n);
			fclose(proc_file);
			*x = 0;
			*y += 1;
			move(*y, *x);
		}
		n++;
	}
	return 1;
}

//ParseInt do proc_pid
	char s_proc_pid[10];
	sprintf(s_proc_pid, "%d", 1);

	//---------- PID
	//le pid
	pid = lerPid(s_proc_pid);
	sprintf(s_pid, "%d", pid);
	//mostra prioridade + direciona apontador do ncurses
	printw(s_pid);
	x += 5;
	move(y, x);

	//---------- USUARIO
	//le USUARIO
	//pid = lerPid(s_proc_pid);
	//sprintf(s_pid, "%d", pid);
	//mostra prioridade + direciona apontador do ncurses
	//printw(s_pid);
	x += 10;
	move(y, x);

	//---------- PIRORIDADE
	//le prioridade
	pr = lerPr(s_proc_pid);
	sprintf(s_pr, "%ld", pr);
	//mostra prioridade + direciona apontador do ncurses
	printw(s_pr);
	x += 11;
	move(y, x);

	//---------- ESTADO
	//le ESTADO
	s = lerS(s_proc_pid);
	s_s[0] = s;
	//mostra prioridade + direciona apontador do ncurses
	printw(&s);
	x += 19;
	move(y, x);

	//---------- %CPU
	//le %CPU
	//pid = lerPid(s_proc_pid);
	//sprintf(s_pid, "%d", pid);
	//mostra prioridade + direciona apontador do ncurses
	//printw(s_pid);
	x += 10;
	move(y, x);

	//---------- TEMPO
	//le TEMPO
	time = lerTime(s_proc_pid);
	time = time / 1000000000;
	sprintf(s_time, "%lds", time);
	//mostra prioridade + direciona apontador do ncurses
	printw(s_time);
	x += 10;
	move(y, x);

	//---------- COMANDO
	//le COMANDO
	//lerCommand(s_proc_pid, command);
	//mostra prioridade + direciona apontador do ncurses
	printw(command);
	x = 0;
	move(y, x);

	y++;
	move(y, x);
*/