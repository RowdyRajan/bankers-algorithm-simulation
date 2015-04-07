#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void multipleNumberInput(int spilts, int array[]);
void waitFiveSeconds();
void printSnapShot();
void printResource(int resource_num);

int main() {
	int resources_num;
	int process_num;

	printf("Number of different resource types: ");
	scanf("%d", &resources_num);
	printf("%d\n", resources_num);
	printResource(resources_num);
	printResource(resources_num);
	printResource(resources_num);
	printResource(resources_num);
	printResource(resources_num);
	printSnapShot(resources_num);
	int resource_instances[resources_num];
	printf("Number of instances of each resource type: ");
	multipleNumberInput(resources_num, resource_instances);

	/*
	int i = 0;
	for (i; i< resources_num; i++){
		printf("%d\n", resource_instances[i]);
	}*/

	/*
	struct procces{
		//int allocation[resources_num] = {0};
		//int request[resources_num] = {0};
		int max[resources_num];
	};*/

	printf("Number of processes: ");
	scanf("%d", &process_num);
	printf("%d\n", process_num);

	//struct procces processes[process_num];
	int max[resources_num];
	int process_numbers[process_num][resources_num];


	int i = 0;
	while(i < process_num){
		printf("Details of P%d: ", i +1);
		multipleNumberInput(resources_num,max);
		i++;
	}



	while(1){
		waitFiveSeconds();
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
void waitFiveSeconds(){
	time_t time_start = time(NULL);
	time_t end_time;
	do{
		end_time = time(NULL);
	}while(difftime(end_time, time_start) < 5);

}

void printSnapShot(int resource_num){
	printf("\n");
	printf("%-*s", (resource_num *3),"Allocation ");
	printf("%-*s", (resource_num *3)," request ");
	printf("%-*s", (resource_num *3)," available ");
	printf("%-*s", (resource_num *3)," Max Request  ");
	printf("%-*s", (resource_num *3)," Max avialable");

}

void printResource(int resource_num){
	int i = 0;
	while( i  < resource_num){
		printf("R%d ", i+1);
		i++;
	}
}
