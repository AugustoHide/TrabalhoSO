/*
int maidn(){
	char string[20];

	
	long int pr; //ok
	char s; //ok
	long int time; // /proc/[pid]/timerslack_ns 
	char command[100]; ///proc/[pid]/cmdline
	
	long double cpu; 
	int user;

	FILE* proc_file;
	int w = 0;
	while(1){
		if (w%5000000 != 0){
			if (w == 5000000){
				w = 0;
			}else{
				w++;
			}
			continue;
		}else{
			------------- pid, pr, s ------------- 			
			proc_file = fopen("/proc/1/stat", "r");

			if (proc_file == NULL){
				printf("Falha ao tentar abrir o proc_file\n");
			}else{
				int i = 1;
				while(!feof(proc_file) && i < 53){
					if(i == 1){
						fscanf(proc_file, "%d", &pid);
						printf("pid: %d\n", pid);
					}else if(i == 3){
						fscanf(proc_file, "%s", &s);
						printf("status: %s\n", &s);
					}else if(i == 18){
						fscanf(proc_file, "%ld", &pr);
						printf("priority: %ld\n", pr);
					}else if(i == 5){
						fscanf(proc_file, "%d", &user);
						printf("GROUPID/USERS??: %d\n", user);
					}else{
						fscanf(proc_file, "%s", string);
					}
					i++;
				}
				printf("proc_file: pid, s, pr - aberto com sucesso!\n");
			}
			fclose(proc_file);
			printf("\n\n\n");


		 ------------- time ------------- 
			proc_file = fopen("/proc/1/timerslack_ns", "r");

			if(proc_file == NULL){
				printf("Falha ao tentar abrir o proc_file\n");
			}else{
				fscanf(proc_file, "%ld", &time);
				printf("time: %ld\n", time);	
			}
			fclose(proc_file);
			printf("\n\n\n");*/
			/* ------------- command ------------- */
/*			proc_file = fopen("/proc/1/cmdline", "r");

			if(proc_file == NULL){
				printf("Falha ao tentar abrir o proc_file\n");
			}else{
				fscanf(proc_file, "%s", command);
				printf("command: %s\n", command);
					
			}
			fclose(proc_file);
			printf("\n\n\n");
		}
		w++;
	}


	return 0;
}
*/