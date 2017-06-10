#include <main.h>

void enqueue(char* data, char* address, struct Queue* front, struct Queue* rear) {
    struct Queue* temp = (struct Queue*) malloc(sizeof(struct Queue));
    temp->row = data;
    temp->address = address;
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


