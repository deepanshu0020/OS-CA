#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef struct {
    int id;
    int arrival_time;
    int service_time;
} customer;

typedef struct {
    customer items[100];
    int front, rear;
} queue;

void init_queue(queue *q) {
    q->front = q->rear = 0;
}

int is_empty(queue *q) {
    return q->front == q->rear;
}

int is_full(queue *q) {
    return q->rear == 100;
}

void enqueue(queue *q, customer item) {
    if (is_full(q)) {
        printf("Error: The queue is full\n");
        exit(1);
    }
    q->items[q->rear++] = item;
}

customer dequeue(queue *q) {
    if (is_empty(q)) {
        printf("Error: The is queue is empty\n");
        exit(1);
    }
    return q->items[q->front++];
}

int main() {
    srand(time(NULL));
    queue regular_queue, new_queue;
    init_queue(&regular_queue);
    init_queue(&new_queue);
    int total_regular_queries = 0, total_new_queries = 0;
    int total_regular_time = 0, total_new_time = 0;
    int current_time = 540;  
    int end_time = 780;  

    while (current_time < end_time) {
        int is_new_customer = rand() % 2 == 0;
        customer c = {is_new_customer ? ++total_new_queries : ++total_regular_queries, current_time, rand() % 10 + 1};

        is_new_customer ? enqueue(&new_queue, c) : enqueue(&regular_queue, c);

       
        if (!is_empty(&regular_queue) && current_time < 720) {
            customer c = dequeue(&regular_queue);
            total_regular_time += c.service_time;
            current_time += c.service_time;
        }

       
        if (!is_empty(&new_queue) && current_time < 780) {
            customer c = dequeue(&new_queue);
            total_new_time += c.service_time;
            current_time += c.service_time;
        }
    }
    int total_queries = total_regular_queries + total_new_queries;
    int total_time = total_regular_time + total_new_time;
    double avg_query_time = (double) total_time / total_queries;
    printf("Total Queries that are handled: %d\n",total_queries);
    printf("Total time spent on handling queries: %dminutes\n", total_time);
    printf("Average query time: %.2f minutes\n", avg_query_time);
    

    return 0;
}
