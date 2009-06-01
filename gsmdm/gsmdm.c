// gsm modem app
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
	char *cmd;
	
	if (argc == 2) {

		printf("The arg %s\n",argv[1]);
		
		if (strcmp(argv[1],"on")==1)

		if (argv[1] == 'on') {
			printf("Modem turned ON\n");
		} else if (argv[1] == 'off') {
			printf("Modem Turned OFF\n");
		} else {
			printf("Invalid command\n");
		}

		
		
	} else if (argc > 2) {
		printf("Too many arguments\n");
	} else {
		printf("One arg expected...\n");
	}
	 
	return 0;
}
