#include<stdio.h>
#include<time.h>
#include<string.h>
#include<unistd.h>
#include<pwd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<signal.h>
#include"lerFileProc.h"
#include<curses.h>


#define max_proc 10000

int leituraProcN(int* y, int* x, char* s_n){
	//Variáveis dos dados dos processos
	int pid;
	long int pr; //ok
	long int time; // /proc/[pid]/timerslack_ns 
	char command[25]; ///proc/[pid]/cmdline
	char s_pid[5], s_s[2], s_pr[2], s_time[15], s_cpu[25];
	double cpu; 
	char* usuario;

	//---------- PID
	//le pid
	pid = lerPid(s_n);
	sprintf(s_pid, "%d", pid);
	//mostra prioridade + direciona apontador do ncurses
	printw(s_pid);
	*x += 5;
	move(*y, *x);

	//---------- USUARIO
	//le USUARIO
	usuario = lerUsuario(s_n);
	//sprintf(s_pid, "%d", pid);
	//mostra prioridade + direciona apontador do ncurses
	printw(usuario);
	*x += 10;
	move(*y, *x);

	//---------- PIRORIDADE
	//le prioridade
	pr = lerPr(s_n);
	sprintf(s_pr, "%ld", pr);
	//mostra prioridade + direciona apontador do ncurses
	printw(s_pr);
	*x += 11;
	move(*y, *x);

	//---------- ESTADO
	//le ESTADO
	lerS(s_n, s_s);
	//mostra prioridade + direciona apontador do ncurses
	printw(s_s);
	*x += 19;
	move(*y, *x);

	//---------- %CPU
	//le %CPU
	cpu = lerCpu(s_n);
	sprintf(s_cpu, "%lf", cpu);
	//mostra prioridade + direciona apontador do ncurses
	printw(s_cpu);
	*x += 10;
	move(*y, *x);

	//---------- TEMPO
	//le TEMPO
	time = lerTime(s_n);
	time = time / 1000000000;
	sprintf(s_time, "%lds", time);
	//mostra prioridade + direciona apontador do ncurses
	printw(s_time);
	*x += 10;
	move(*y, *x);

	//---------- COMANDO
	//le COMANDO
	lerCommand(s_n, command);
	//mostra prioridade + direciona apontador do ncurses
	printw(command);


	return 1;
}

void mostraOrdenado(double cpuId[10000][2], int n_proc, int* y, int* x){
	int n = 0;
	FILE* proc_file;
	char proc_adr[20], s_n[7];

	
	while(n < n_proc){
		sprintf(s_n, "%d", (int) cpuId[n][1]);
		strcpy(proc_adr,"/proc/");
		strcat(proc_adr, s_n);
		strcat(proc_adr, "/stat");
		proc_file = fopen(proc_adr, "r");
		if(proc_file != NULL){
			//chama função de leitura no /proc/n
			if(leituraProcN(y, x, s_n) == 0){
				return;
			}
			//printw("%s", s_n);
			fclose(proc_file);
			
		}else{
			printw("Erro ao tentar ler %s", proc_adr);
		}
		*x = 0;
		*y += 1;
		move(*y, *x);
		n++;
	}
}

void p_create_armazena(double cpuId[10000][2], int n_esimo, char* s_n){

	cpuId[n_esimo][0] = lerCpu(s_n);
	cpuId[n_esimo][1] = lerPid(s_n);
}

void ArmazenaCpuId(double cpuId[10000][2]){
	int n = 0, n_esimo = 0;
	FILE* proc_file;
	char proc_adr[20], s_n[7];

	for (int i = 0; i < max_proc; i++){
		cpuId[i][0] = 0;
		cpuId[i][1] = 0;
	}

	while(n < max_proc){
		sprintf(s_n, "%d", n);
		strcpy(proc_adr,"/proc/");
		strcat(proc_adr, s_n);
		strcat(proc_adr, "/stat");
		proc_file = fopen(proc_adr, "r");
		if(proc_file != NULL){
			//int pid = fork();
			
			//if (pid == 0){
				fclose(proc_file);
				p_create_armazena(cpuId, n_esimo, s_n);
				//printf("pid == 0, getpid == %d, getppit == %d\n", getpid(), getppid());
				/*kill(getpid(), SIGTERM);
			}*/
			//printf("pid: %lf, n: %d, n_esimo: %d, %d\n", cpuId[n_esimo][0],n, n_esimo, max_proc);
			n_esimo++;
		}
		n += 1;
	}

	//printf("Done\n");
}



void troca(double* v1, double* v2){
	int aux = *v1;
	*v1 = *v2;
	*v2 = aux;
}

void ordenaCpuId(double cpuId[10000][2], int n_proc){
	int i, j;

	for(i = 0; i < n_proc; i++){
		for (j = 0; j < n_proc; j++){
			if(cpuId[j][0] < cpuId[j+1][0]){
				troca(&cpuId[j][1], &cpuId[j+1][1]);
				troca(&cpuId[j][0], &cpuId[j+1][0]);
			}
		}
	}
	//printf("n_proc: %d\n", n_proc);

}

int achar_n_proc(double cpuId[10000][2]){
	int n = 0,
		n_proc;
	while(n < max_proc){
		if (cpuId[n][1] == 0.0){
			n++;
			continue;
		}
		//printf("pid%d:\t%lf\n", n, cpuId[n][0]);
		n_proc = n;	
		n++;
	}
	return n_proc;
}

void repetir_exec(double cpuId[10000][2], int* y,int* x){
	int n_proc, rep = 1;

	while(rep){
		ArmazenaCpuId(cpuId);
		//Determina n_proc == numero de processo atualmente no pc
		n_proc = achar_n_proc(cpuId);

		//Ordena cpuId de acordo com o maior %cpu
		ordenaCpuId(cpuId, n_proc);

		//mostra os processos em ordem de maior %cpu
		//quanto maior a janela do terminar, mais processos aparecem
		mostraOrdenado(cpuId, 16, y, x);

		rep = getch();
		if(rep != 'r'){
			break;
		}

		*x = 0;
		*y = 2;
	}

}