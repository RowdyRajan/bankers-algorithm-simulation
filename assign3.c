#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void multipleNumberInput(int spilts, int array[]);

int main() {
	int resources_num;
	int process_num;

	printf("Number of different resource types: ");
	scanf("%d", &resources_num);
	printf("%d\n", resources_num);

	int resource_instances[resources_num];
	printf("Number of instances of each resource type: ");
	multipleNumberInput(resources_num, resource_instances);

	/*
	int i = 0;
	for (i; i< resources_num; i++){
		printf("%d\n", resource_instances[i]);
	}*/

	struct procces{
		int allocation[resources_num] = {0};
		int request[resources_num] = {0};
		int max[resources_num];
	};

	printf("Number of processes: ");
	scanf("%d", &process_num);
	printf("%d\n", process_num);

	struct procces processes[process_num];

	int process_numbers[process_num][resources_num];


	int i = 0;
	while(i < process_num){
		printf("Details of P%d: ", i +1);
		multipleNumberInput(resources_num, processes[i].max);
		i++;
	}



}

//Will get resources_num number of inputs and save them in resource_instances
void multipleNumberInput(int resources_num, int resource_instances[]) {
	int i = 0;
	while(i < resources_num && scanf("%d", &resource_instances[i]) != 0){
		printf("%d\n", resource_instances[i]);
		i++;
	}

}
