typedef struct Pair {
    int row;
    int col;
} Pair;

typedef struct Node {
    struct Pair data;
    struct Node* next;
} Node;

typedef struct Queue {
    Node* front;
    Node* rear;
    int size;
} Queue;

void initializeQueue(Queue* q);

void enqueue(Queue* q, Pair value);

Pair dequeue(Queue* q);

Pair peek(Queue* q);

int isEmpty(Queue* q);

int queueSize(Queue* q);
