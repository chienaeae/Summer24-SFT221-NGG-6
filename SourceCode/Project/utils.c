#include "utils.h"

#include <stdio.h>
#include <stdlib.h>


void initializeQueue(Queue* q) {
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
}

void enqueue(Queue* q, Pair data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Error: out of memory.\n");
        return;
    }
    newNode->data = data;
    newNode->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    q->size++; 
}

Pair dequeue(Queue* q) {
    if (q->front == NULL) {
        struct Pair empty = {-1, -1};
        return empty;
    }

    Node* temp = q->front;
    Pair data = temp->data;
    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);
    q->size--;
    return data;
}

Pair peek(Queue* q) {
    if (q->front == NULL) {
        struct Pair empty = {-1, -1};
        return empty;
    }
    return q->front->data;
}

int isEmpty(Queue* q) {
    return q->front == NULL;
}


int queueSize(Queue* q){
    return q->size;
}