#include <main.h>

struct Queue {
    struct Queue* next; //next on the queue
    double row[8]; //The data in the register
};

void enqueue(double data[8], struct Queue* front, struct Queue* rear) {
    struct Queue* temp = (struct Queue*) malloc(sizeof(struct Queue));
    memcpy(&(temp->row), data, sizeof data);
    temp->next = NULL;
    if(front == NULL && rear == NULL) {
        front = rear = temp;
    }
    rear->next = temp;
    rear = temp;
}


void dequeue(struct Queue* front, struct Queue* rear) {
    struct Queue* temp = front;
    if(front == NULL) {
        return;
    }
    if(front == rear) {
        front = rear = NULL;
    }
    else {
        front = front->next;
    }
    free(temp);
}

double * Front(struct Queue* front) {
    if(front == NULL) {
        return NULL;
    }
    return front->row;
}



