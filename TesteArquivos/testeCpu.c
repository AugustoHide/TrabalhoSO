#include<stdio.h>
#include<time.h>
#include<string.h>
#include<curses.h>
#include<unistd.h>

long unsigned f_t_antes(char* proc_adr){
	FILE* proc_file;
	unsigned long int utime, stime, t_antes;
	char string[25];

	proc_file = fopen(proc_adr, "r");

	if (proc_file == NULL){
		printf("Falha ao tentar abrir o %s - cpu\n", proc_adr);
	}else{
		int i = 1;
		while(i < 18){
			if (i == 14){
				fscanf(proc_file, "%lu", &utime);
			}else if (i == 15){
				fscanf(proc_file, "%lu", &stime);
			}else{
				fscanf(proc_file, "%s", string);
			}
			i++;
		}
		t_antes = utime + stime;
		fclose(proc_file);
	}

	printf("%lu\n", utime);
	printf("%lu\n", stime);

	return t_antes;
}

long unsigned f_tot_antes(char* proc_adr){
	FILE* proc_file;
	unsigned long int times_cpu[10], tot_antes;
	char string[25];

	proc_file = fopen(proc_adr, "r");

	if (proc_file == NULL){
		printf("Falha ao tentar abrir o %s - cpu\n", proc_adr);
	}else{
		int i = 0;
		tot_antes = 0;
		while(i < 11){
			if (i != 0){
				fscanf(proc_file, "%lu", &times_cpu[i]);
			}else{
				fscanf(proc_file, "%s", string);
			}
			i++;
			tot_antes += times_cpu[i];
		}
		fclose(proc_file);
	}
	return tot_antes;
}

double lerCpu(char* proc_pid){

	double time;
	unsigned long int  t_antes, t_depois;
	long unsigned tot_antes, tot_depois;
	char proc_adr[20];

	/* ---------- Determinar t_antes ----------*/
	// --------- Concatenação de endereço
	strcpy(proc_adr,"/proc/");
	strcat(proc_adr, proc_pid);
	strcat(proc_adr, "/stat");
	//printf("%s\n", proc_adr);

	t_antes = f_t_antes(proc_adr);

	/* ---------- Determinar tot_antes ----------*/
	// --------- Concatenação de endereço
	strcpy(proc_adr,"/proc/");
	strcat(proc_adr, "stat");
	//printf("%s\n", proc_adr);

	tot_antes = f_tot_antes(proc_adr);

	/* ---------- pausa ----------*/
	sleep(3);

	/* ---------- Determinar t_antes ----------*/
	// --------- Concatenação de endereço
	strcpy(proc_adr,"/proc/");
	strcat(proc_adr, proc_pid);
	strcat(proc_adr, "/stat");
	//printf("%s\n", proc_adr);

	t_depois = f_t_antes(proc_adr);

	/* ---------- Determinar tot_antes ----------*/
	// --------- Concatenação de endereço
	strcpy(proc_adr,"/proc/");
	strcat(proc_adr, "stat");
	//printf("%s\n", proc_adr);

	tot_depois = f_tot_antes(proc_adr);

	time = (t_depois - t_antes)/(tot_depois - tot_antes);

	printf("%lu\n", t_antes);
	printf("%lu\n", t_depois);
	printf("%lu\n", tot_antes);
	printf("%lu\n", tot_depois);
	printf("%lf\n", time);
	return time;
}




int main(){
	char proc[] = "1";

	double cpu = lerCpu(proc);
	printf("%lf\n", cpu);

	return 1;
}