
/*Função que
	le totdos os processos
	armazenaa %cpu de todos com seus respectivos id*/
void ArmazenaCpuId(double cpuId[10000][2]);

/*Função que
	ordena as linhas de cpuId[][2] pelo cpu maior*/
void ordenaCpuId(double cpuId[10000][2], int n_proc);
void troca(double* v1, double* v2);

/*Função que 
	mostra no ncurses
		os processos na ordem correta*/