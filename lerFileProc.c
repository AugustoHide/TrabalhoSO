#include<stdio.h>
#include<time.h>
#include<string.h>
#include<unistd.h>
#include<pwd.h>
#include<stdlib.h>

char* lerUsuario(char* proc_pid){
	FILE* proc_file;
	char /*string[25] ,*/ proc_adr[25], *usuario;
	unsigned long int uid;
	register struct passwd *pw;

	//pegar userid
	strcpy(proc_adr,"/proc/");
	strcat(proc_adr, proc_pid);
	strcat(proc_adr, "/status");
	//printf("%s\n", proc_adr);

	proc_file = fopen(proc_adr, "r");

	if (proc_file == NULL){
		printf("Falha ao tentar abrir o %s - cpu\n", proc_adr);
	}else{
		char dado[20]; 
		fscanf(proc_file, "%s", dado);
		while(strcmp(dado, "Uid:") != 0 && strcmp(dado, "") != 0){
			fscanf(proc_file, "%s", dado);
			//printf("%s\n", dado);
		}
		fscanf(proc_file, "%lu", &uid);
		//printf("%lu\n", uid);
		fclose(proc_file);
	}
	//printf("\n\n");
	//pegar nome do usuario pelo userid
	pw = getpwuid(uid);
	if(pw){
		usuario = pw->pw_name;
		//printf("%s\n", usuario);
	}

	return usuario;
}

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

	/*printf("%lu\n", utime);
	printf("%lu\n", stime);
*/
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
		while(i < 10){
			if (i == 1){
				fscanf(proc_file, "%lu", &times_cpu[i]);
			}else if (i == 3){
				fscanf(proc_file, "%lu", &times_cpu[i]);
			}else{
				fscanf(proc_file, "%s", string);
				times_cpu[i] = 0;
			}
			tot_antes += times_cpu[i];
			//printf("\t%lu\t%lu\n", tot_antes, times_cpu[i]);
			i++;
		}
		//printf("\t%lu\n", tot_antes);
		fclose(proc_file);
	}
	return tot_antes;
}

double lerCpu(char* proc_pid){

	double time;
	unsigned long int  t_proc;
	long unsigned int total;
	char proc_adr[20];

	/* ---------- Determinar t_proc ----------*/
	// --------- Concatenação de endereço
	strcpy(proc_adr,"/proc/");
	strcat(proc_adr, proc_pid);
	strcat(proc_adr, "/stat");
	//printf("%s\n", proc_adr);

	t_proc = f_t_antes(proc_adr);

	/* ---------- Determinar total ----------*/
	// --------- Concatenação de endereço
	strcpy(proc_adr,"/proc/");
	strcat(proc_adr, "stat");
	//printf("%s\n", proc_adr);

	total = f_tot_antes(proc_adr);


	time = t_proc/total;

	/*printf("\tt_proc: %lu\n", t_proc);
	printf("\ttotal: %lu\n", total);
	printf("%lf\n", time*100);*/
	return time*100;
}

int lerPid(char* proc_pid){
	int pid; //ok
	FILE* proc_file;

	// --------- Concatenação de endereço
	char proc_adr[20];
	strcpy(proc_adr,"/proc/");
	strcat(proc_adr, proc_pid);
	strcat(proc_adr, "/stat");
	//printf("%s\n", proc_adr);


	proc_file = fopen(proc_adr, "r");

	if (proc_file == NULL){
		printf("Falha ao tentar abrir o /proc/%s/stat - pid\n", proc_pid);
	}else{
		fscanf(proc_file, "%d", &pid);
		//printf("pid: %d\n", pid);
		
	}
	fclose(proc_file);
	return pid;
}

long int lerPr(char* proc_pid){
	long int pr; //ok
	FILE* proc_file;

	// --------- Concatenação de endereço
	char proc_adr[20];
	strcpy(proc_adr,"/proc/");
	strcat(proc_adr, proc_pid);
	strcat(proc_adr, "/stat");
	//printf("%s\n", proc_adr);

	proc_file = fopen(proc_adr, "r");

	if (proc_file == NULL){
		printf("Falha ao tentar abrir o /proc/%s/stat - pr\n", proc_pid);
	}else{
		int i = 0;
		while(i != 18){
			if (i == 17){
				fscanf(proc_file, "%ld", &pr);
				//printf("pr: %d\n", pr);
			}else{
				char string[100];
				fscanf(proc_file, "%s", string);
			}
			i++;
		}
	}
	fclose(proc_file);
	return pr;
}

char lerS(char* proc_pid, char* s_s){
	char s = ' '; //ok
	char string[100];
	FILE* proc_file;

	// --------- Concatenação de endereço
	char proc_adr[20];
	strcpy(proc_adr,"/proc/");
	strcat(proc_adr, proc_pid);
	strcat(proc_adr, "/stat");
	//printf("%s\n", proc_adr);

	proc_file = fopen(proc_adr, "r");

	if (proc_file == NULL){
		printf("Falha ao tentar abrir o /proc/%s/stat - s\n", proc_pid);
	}else{
		int i = 0;
		while(i != 3){
			if (i == 2){
				fscanf(proc_file, "%s", s_s);
				//printf("s: %s\n", &s);
				break;
			}else{
				fscanf(proc_file, "%s", string);
			}
			i++;
		}
		s = 'Y';
		fclose(proc_file);
	}
	return s;
}
/*------------- time -------------*/ 
long int lerTime(char* proc_pid){
	long int time; //ok
	FILE* proc_file;

	// --------- Concatenação de endereço
	char proc_adr[20];
	strcpy(proc_adr,"/proc/");
	strcat(proc_adr, proc_pid);
	strcat(proc_adr, "/timerslack_ns");
	//printf("%s\n", proc_adr);

	proc_file = fopen(proc_adr, "r");

	if(proc_file == NULL){
		printf("Falha ao tentar abrir o /proc/%s/stat - time\n", proc_pid);
	}else{
		fscanf(proc_file, "%ld", &time);
		//printf("time: %ld\n", time);	
	}
	fclose(proc_file);
	return time/1000;
}
/* ------------- command ------------- */
void lerCommand(char* proc_pid, char* comando){
	FILE* proc_file;

	// --------- Concatenação de endereço
	char proc_adr[20];
	strcpy(proc_adr,"/proc/");
	strcat(proc_adr, proc_pid);
	strcat(proc_adr, "/comm");

	proc_file = fopen(proc_adr, "r");

	if(proc_file == NULL){
		printf("Falha ao tentar abrir o /proc/%s/stat - comando\n", proc_pid);
		
	}else{
		fscanf(proc_file, "%s", comando);
		//printf("command: %s\n", comando);
		fclose(proc_file);
	}
}


