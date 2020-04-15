#include<stdio.h>
#include<string.h>

int main(){
	//FILE *-> address to structure that contains all the info about the file

	//fopen("file_name", "mode"); 
	// r -> reading
	// w -> write or create file if it does not exist
	// a-> edit or create file if it does not exist
	// rb, wb, ab -> binari files

	FILE* Fpointer;

	//fputc(,);
	//fputs(string, file_pointer);
	//fprintf(file_pointer, "format specifier", list of variables);
	//fscanf(file_pointer, "fort_string", list_of_adress_var);
	//fgets(var_to_store, length(max numbeer of character), file_pointer);
	/*
	char data[25] = "Learning Lad";
	char input[25];
	char name[25];
	int age;
	char ch;
	char data[40];
	int age;
	*/
	char var[20];

	Fpointer = fopen("anil.txt", "r");

	if (Fpointer == NULL){
		printf("Unable to create the file\n");
	}else{
		/*
		for (int i = 0; i < strlen(data); i++){
			//printf("Writing the character: %c\n", data[i]);
			//fputc(data[i], Fpointer);
		}
		*/
		/*
		printf("Enter a string to write to the file: ");
		scanf("%[^\n]s", input);
		fputs(input, Fpointer);
		*/
		/*
		printf("Enter your name and age: ");
		scanf("%s%d", name, &age);
		fprintf(Fpointer, "%s\t%d\n", name, age);
		*/
		/*
		while(!feof(Fpointer)){
			ch = fgetc(Fpointer);
			printf("%c", ch);
		}
		*/
		/*
		while(fscanf(Fpointer, "%s\t%d", data, &age) && !feof(Fpointer)){
			printf("%s\t%d\n", data, age);
		}
		*/
		while(!feof(Fpointer) && fgets(var, 20, Fpointer)){
			printf("%s", var);
		}

		printf("File wrote/opened successfuly\n");
		fclose(Fpointer);
	}

	return 0;
}