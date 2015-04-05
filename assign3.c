#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void multipleNumberInput(int spilts, int array[]);

int main() {
	int resources_num;
	char thing[70];
	printf("Number of different resource types: ");
	scanf("%d", &resources_num);
	printf("%d\n", resources_num);

	int resource_instances[resources_num];
	printf("Number of instances of each resource type: ");

	int i = 0;
	while(i < resources_num && scanf("%d", &resource_instances[i]) != 0){
		printf("%d\n", resource_instances[i]);
		i++;
	}



}

void multipleNumberInput(int spilts, int array[]) {
	char multipleNumbers[70];
	char* number;
	const char* s = " ";
	//fgets(multipleNumbers,spilts *3,stdin);
	//scanf("s", multipleNumbers);
	printf("%s\n", multipleNumbers);
	number = strtok(multipleNumbers, " ");
	printf("%s", number);
	//array[0] = atoi(number);
	number = strtok(NULL, " ");
	printf("%s", number);
	//array[1] = atoi(number);
	/*
	for (int i = 1; i < spilts; i++) {
		number = strtok(NULL, " ");
		array[i]= atoi(number);
	}*/

}
