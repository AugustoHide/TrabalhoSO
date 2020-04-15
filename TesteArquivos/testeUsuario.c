#include<stdio.h>
#include<time.h>
#include<string.h>
#include<curses.h>
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



int main(){
	char pid[6] = "3099";
	char* username = lerUsuario(pid);
	printf("%s\n", username);

	return 1;
}