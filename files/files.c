#include "files.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menu() {

	char comm[1024]; // 1024 во избежание переполнения

	printf("%s\n%s", "Type commands here (type -help or -h to open help window):", ">");
	scanf("%s", comm);

	if (!strcmp(comm, "-help") || !strcmp(comm, "-h")) {
		printf("%s%s",
			"Type '-quit' or '-q' to exit. \n",
			"Type '11','12','13' to find out the average and maximum number of requests per m/h/d.\n");
	}
	else if (!strcmp(comm, "-quit") || !strcmp(comm, "-q")) {
		exit("");
	}
	else if (!strcmp(comm, "11")) {
		first_task(15, "m: ");
	}
	else if (!strcmp(comm, "12")) {
		first_task(12, "h: ");
	}
	else if (!strcmp(comm, "13")) {
		first_task(0, "d: ");
	}

	menu();
}

void first_task(int length, char str[3]) {

	FILE *file;
	char c;
	unsigned int i = 0, j = 0, k = 0, max = 0, summ = 0, arr[59474], val[8160];

	file = fopen("access.txt", "r");

	if (file != NULL) {

		while ((c = fgetc(file)) != EOF) {
			if (c == '[') {

				for (i = 0; i < length; i++) {
					fgetc(file);
				}

				fscanf(file, "%i", &arr[j]);

				if (j == 0) {
					val[k] = 1;
				}
				else {
					if (arr[j] == arr[j - 1]) {
						val[k]++;
					}
					else {

						if (val[k] > max) max = val[k];

						summ += val[k];

						k++;
						val[k] = 1;
					}
				}

				j++;
			}
		}

		printf("%s%s%i\n", "The average number of requests per ", str , summ / k);
		printf("%s%s%i\n", "The maximum number of requests per ", str , max);

		fclose(file);
	}
	else {
		printf("Cannot open file! Please, check file name and try again!\n");
		exit("");
	}

	return;
}