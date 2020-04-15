#include<stdio.h>
#include<time.h>
#include<string.h>
#include<curses.h>

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
		printf("command: %s\n", comando);
		fclose(proc_file);
	}
}

int main(){
	char s_proc_pid[10];
	sprintf(s_proc_pid, "%d", 2456);
	char s[25];
	lerCommand(s_proc_pid, s);
	printf("%s\n", s);

	initscr();
	printw(s);

	getch();
	endwin();


	return 0;
}