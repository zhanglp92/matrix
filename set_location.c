#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int 	i = 0;

	system("clear");
	for(i  = 0; i < argc; i++){

		printf("\033[2J\033[43;30m\033[5;10H%s\033[0m\n", argv[i]);
		sleep(1);
	}

	return 0;
}
