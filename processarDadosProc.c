#include<stdio.h>
#include<time.h>
#include<string.h>
#include<unistd.h>
#include<pwd.h>
#include<stdlib.h>
#include"lerFileProc.h"

#define max_proc 10000

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
			cpuId[n_esimo][0] = lerCpu(s_n);
			cpuId[n_esimo][1] = lerPid(s_n);
			printf("pid: %lf, n: %d, n_esimo: %d, %d\n", cpuId[n_esimo][0],n, n_esimo, max_proc);
			n_esimo++;
		}
		n += 1;
	}

	printf("Done\n");
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
	printf("n_proc: %d\n", n_proc);

}