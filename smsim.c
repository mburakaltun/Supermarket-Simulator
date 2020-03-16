/*
 * THIS CODE IS MY OWN WORK. I DID NOT CONSULT TO ANY  PROGRAM WRITTEN
 * BY OTHER STUDENTS or DID NOT COPY ANY PROGRAM FROM OTHER SOURCES.
 * I READ AND FOLLOWED THE GUIDELINE GIVEN IN THE PROGRAMMING ASSIGNMENT.
 * NAME: Muhammed Burak Altun
 */

#include <stdio.h>
#include <time.h>
#include "queue.h"

struct Customer {
	int waiting_time;
}; typedef struct Customer customer;

int main(void) {
	int max_arrival_time;
	int max_service_time;
	int simulation_time;

	printf("Enter max arrival time: ");
	scanf("%d",&max_arrival_time);
	printf("Enter max service time: ");
	scanf("%d",&max_service_time);
	printf("Enter simulation time: ");
	scanf("%d",&simulation_time);
	printf("Simulation parameters: %d %d %d\n",max_arrival_time, max_service_time, simulation_time);
	printf("--------------------------------\n");

	QueueNodePtr headPtr = NULL;
	QueueNodePtr tailPtr = NULL;

	srand(time(NULL));
	// variables
	customer* new_customer = (customer*) malloc(sizeof(customer));
	customer customers[simulation_time];

	int total_service_time = 0;
	int service_time = 0;
	float average_service_time = 0;

	int total_arrival_time = 0;
	int arrival_time = 0;
	float average_arrival_time = 0;

	int total_waiting_time = 0;
	int max_waiting_time = 0;
	float average_waiting_time = 0;

	int current_time = 0;
	int new_customer_arrival_time = 0;
	int next_service_start_time = 0;
	int current_service_finish_time = 0;
	int line = 0;
	int max_line = 0;
	int total_customer = 0;
	int serviced_number = 0;

	new_customer_arrival_time = (rand() % max_arrival_time) + 1;
	service_time = (rand() % max_arrival_time) + 1;
	next_service_start_time = new_customer_arrival_time;
	current_service_finish_time = service_time + new_customer_arrival_time;

	while(current_time <= simulation_time) {
		current_time += 1;
		if(new_customer_arrival_time == current_time) {
			printf("\t%d: customer %d arrived\n",current_time,total_customer+1);
			enqueue(&headPtr,&tailPtr,new_customer);

			arrival_time = (rand() % max_arrival_time) + 1;
			total_arrival_time += arrival_time;

			new_customer_arrival_time =  arrival_time + current_time;
			customers[total_customer] = *new_customer;
			total_customer += 1;
			line += 1;
		}
		if(current_service_finish_time == current_time) {
			serviced_number += 1;
			printf("\t%d: service completed for customer %d\n",current_time,serviced_number);
			dequeue(&headPtr,&tailPtr);

			service_time = (rand() % max_service_time) + 1;
			total_service_time += service_time;

			if(headPtr == NULL) {
				current_service_finish_time = service_time + new_customer_arrival_time;
				next_service_start_time = new_customer_arrival_time;
			} else {
				current_service_finish_time = service_time + current_time;
				next_service_start_time = current_time;
			}
			line-=1;
		}
		if(next_service_start_time == current_time) {
			printf("\t%d: service starts for customer %d\n",current_time,total_customer);

		}

		for(int i=serviced_number;i<total_customer;i++) {
			customers[i].waiting_time += 1;
		}

		if(max_line < line) {
			max_line = line;
		}
		//printf("Current line: %d\n",line);
	}

	for(int i=0;i<total_customer;i++) {
		if(customers[i].waiting_time > max_waiting_time) {
			max_waiting_time = customers[i].waiting_time;
		}
		total_waiting_time += customers[i].waiting_time;
	}

	average_waiting_time = (float)total_waiting_time / total_customer;
	average_arrival_time = (float)total_arrival_time / total_customer;
	average_service_time = (float)total_service_time / serviced_number;

	printf("-----------------------------------------\n");
	printf("\tSimulation Statistics\n");
	printf("-----------------------------------------\n");

	printf("Simultion parameters: %d %d %d\n",simulation_time,max_arrival_time,max_service_time);
	printf("Number of Customers: %d\n",total_customer);
	printf("Average Wait Time: %f\n",average_waiting_time);
	printf("Average Service Time: %f\n",average_service_time);
	printf("Average Arrival Time: %f\n",average_arrival_time);
	printf("Maximum Wait Time: %d\n",max_waiting_time);
	printf("Maximum Queue Length: %d\n",max_line);

}
