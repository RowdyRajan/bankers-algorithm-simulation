#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <signal.h>

void multipleNumberInput(int spilts, int array[]);
void waitFiveSeconds();
void printSnapShot(int resource_num, int process_num, int * allocation, int * current_request, int c_avail[],int * maxpos,int max_avail[]);
void printResource(int resource_num);
void printArray(int size, int array[]);
void intCopy(int size, int source[], int dest[]);
void printInit(int resource_num);
int doCommand(int resource_num, int process_num,
		int * allocation, int * current_request,
		int c_avail[],int * maxpos,char* status);
void request(int resource_num, int process_num,
		int * allocation, int * current_request,
		int c_avail[],int * maxpos,char* status);
void release(int resource_num, int process_num,
		int * allocation, int * current_request,
		int c_avail[],int * maxpos,char* status);

void intMinus(int size, int source[], int dest[]);
void intAllocate(int size, int allocate[], int avial[], int granted[]);
void printArrayReg(int size, int array[]);
void intDeAllocate(int size, int allocate[], int avial[], int release[]);
int CheckWaiting(int resource_num, int process_num,
						int * allocation, int * current_request,
						int c_avail[],int * maxpos,char* status);
void catch(int signum){
	printf("Simulation ended\n");
	exit(0);
}

int main() {
	int resources_num;
	int process_num;
	signal(SIGINT,catch);
	printf("Number of different resource types: ");
	scanf("%d", &resources_num);
	//printf("%d\n", resources_num);


	int resource_instances[resources_num];
	int current_instances[resources_num];

	printf("Number of instances of each resource type: ");
	multipleNumberInput(resources_num, resource_instances);

	intCopy(resources_num, resource_instances, current_instances);
	
	printf("Number of processes: ");
	scanf("%d", &process_num);
	//printf("%d\n", process_num);

	int allocation[process_num][resources_num];
	memset(allocation,0,sizeof(allocation));

	int request[process_num][resources_num];
	memset(request,0,sizeof(request));

	int max[process_num][resources_num];


	char status[process_num];
	memset(status,'N' ,sizeof(status));




	int i = 0;
	while(i < process_num){
		printf("Details of P%d: ", i +1);
		multipleNumberInput(resources_num, max[i]);
		i++;
	}

	printInit(resources_num);
	int j;
	for(j = 0; j<process_num; j++){
		printSnapShot(resources_num, j+1, allocation[j], request[j], current_instances, max[j], resource_instances);
	}



	while(1){
		waitFiveSeconds();
		int k;
		for (k= 0; k< process_num; k++){
			int response = doCommand(resources_num, k, allocation[k], request[k], current_instances, max[k], status);
			if (response){
				printInit(resources_num);
				int j;
				for(j = 0; j<process_num; j++){
					printSnapShot(resources_num, j+1, allocation[j], request[j], current_instances, max[j], resource_instances);
				}
				printf("\n");
			}
		}

		for (k= 0; k< process_num; k++){
			int response = CheckWaiting(resources_num, k, allocation[k], request[k], current_instances, max[k], status);
					if (response){
						printInit(resources_num);
						int j;
						for(j = 0; j<process_num; j++){
							printSnapShot(resources_num, j+1, allocation[j], request[j], current_instances, max[j], resource_instances);
						}
						printf("\n");
					}
		}


	}

}

int doCommand(int resource_num, int process_num,
		int * allocation, int * current_request,
		int c_avail[],int * maxpos,char * status){
	int choice = rand() % 3;
	switch (choice){
		case 0:
			request(resource_num, process_num,
					allocation, current_request,
					 c_avail, maxpos, status);
			return 1;
		case 1:
			release(resource_num, process_num,
					allocation, current_request,
					 c_avail, maxpos, status);
			return 0;
	}
	return 0;

}


void request(int resource_num, int process_num,
					int * allocation, int * current_request,
					int c_avail[],int * maxpos,char* status){
	int requests[resource_num];
	int accepted = 1;
	int i;

	if(status[process_num] == 'W'){
		return;
	}
	for(i = 0; i<resource_num; i++){
		requests[i] = rand() % (maxpos[i] + 1);
		if(requests[i] > c_avail[i]){
			accepted = 0;
		}
	}
	printf("Request ");
	printArrayReg(resource_num, requests);
	printf("Came from P%d\n" , process_num +1);
	if(!accepted){
		intCopy(resource_num, requests, current_request);
		status[process_num] = 'W';
		printf("Request ");
		printArrayReg(resource_num, requests);
		printf("From P%d can not be granted. P%d is in a waiting state\n" , process_num +1, process_num +1);
	}else{
		intAllocate(resource_num,allocation,c_avail,requests);
		printf("Request ");
		printArrayReg(resource_num, requests);
		status [process_num]= 'R';
		printf("From P%d is granted\n" , process_num +1);
	}
}

void release(int resource_num, int process_num,
						int * allocation, int * current_request,
						int c_avail[],int * maxpos,char* status){
	int release[resource_num];
	if(status[process_num] != 'R'){
		return;
	}

	int i;
	for (i =0; i<resource_num; i++){
		if(allocation[i]){
			release[i] = rand() % (allocation[i] +1);
		}else{
			release[i] = 0;
		}
	}
	intDeAllocate(resource_num, allocation,c_avail,release);
	printf("P%d has released " , process_num +1);
	printArrayReg(resource_num, release);
	printf(" Of its resources\n");

}

int CheckWaiting(int resource_num, int process_num,
						int * allocation, int * current_request,
						int c_avail[],int * maxpos,char* status){
	if(status[process_num] != 'W'){
		return 0;
	}
	int i;
	for(i = 0; i<resource_num; i++){
		if(current_request[i] > c_avail[i]){
				return 0;
		}
	}
	intAllocate(resource_num,allocation,c_avail,current_request);
	status[process_num] = 'R';
	printf("Previous Request of \n");
	printArrayReg(resource_num, current_request);
	printf("from P%d has been satisfied\n" , process_num +1);
	intMinus(resource_num, current_request, current_request);
	return 1;


}
//Will get resources_num number of inputs and save them in resource_instances
void multipleNumberInput(int resources_num, int resource_instances[]) {
	int i = 0;
	while(i < resources_num && scanf("%d", &resource_instances[i]) != 0){
		//printf("%d\n", resource_instances[i]);
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

void printSnapShot(int resource_num, int process_num,
					int * allocation, int * current_request,
					int c_avail[],int * maxpos,int max_avail[]){


	printf("P%d  " , process_num);
	printArray(resource_num, allocation);
	printArray(resource_num, current_request);
	printArray(resource_num, c_avail);
	printArray(resource_num, maxpos);
	printArray(resource_num, max_avail);
	printf("\n");



}

void printInit(int resource_num){
	printf("\nValues from left to right: Allocation, Current Request, Current available resources, max possible request, max available resources\n");
	printf("    ");
	int i = 0;
	while (i < 5){
		printResource(resource_num);
		i++;
	}
	printf("\n");
}



void printResource(int resource_num){
	int i = 0;
	while( i  < resource_num){
		printf("R%d ", i+1);
		i++;
	}
	printf("     ");
}

void printArray(int size, int array[]){
	int i =0;
	while(i<size){
		printf("%d  ",array[i]);
		i++;
	}
	printf("     ");
}

void printArrayReg(int size, int array[]){
	int i =0;
	while(i<size){
		printf("%d ",array[i]);
		i++;
	}
}

void intCopy(int size, int source[], int dest[]){
	int i;
	for(i =0; i < size; i++){
		dest[i] = source[i];
	}
}
void intMinus(int size, int source[], int dest[]){
	int i;
	for(i =0; i < size; i++){
		dest[i] = dest[i] - source[i];
	}
}
void intAllocate(int size, int allocate[], int avial[], int granted[]){
	int i;
	for(i=0; i<size; i++){
		allocate[i] = allocate[i] + granted[i];
		avial[i] = avial[i] - granted[i];
	}
}

void intDeAllocate(int size, int allocate[], int avial[], int release[]){
	int i;
	for(i=0; i<size; i++){
		allocate[i] = allocate[i] - release[i];
		avial[i] = avial[i] + release[i];
	}
}





