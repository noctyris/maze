#define MAX_HEAP_SIZE 100

typedef struct {
    int x, y; // Node coordinates
    float f; // Priority (f = g + h)
} Node;

typedef struct {
    Node heap[MAX_HEAP_SIZE];
    int size;
} PriorityQueue;

// Function to swap two integers
void swap(Node* a, Node* b) {
    Node temp = *a;
    *a = *b;
    *b  = temp;
}

// Add an item to the queue
void pushPQ(PriorityQueue* pq, int x, int y, float f) {
    if (pq->size >= MAX_HEAP_SIZE) {
        printf("Priority queue is full\n");
        return;
    }

    int i = pq->size++;
    pq->heap[i].x = x;
    pq->heap[i].y = y;
    pq->heap[i].f = f;

    // Maintain heap property (ascending)
    while (i>0 && pq->heap[(i-1)/2].f > pq->heap[i].f) {
        swap(&pq->heap[i], &pq->heap[(i-1)/2]);
        i = (i-1)/2;
    }
}

Node popPQ(PriorityQueue* pq) {
    if (pq->size <= 0) {
        printf("Priority queue is empty\n");
        exit(1);
    }
    Node min = pq->heap[0];
    pq->heap[0] = pq->heap[--pq->size];

    // Maintain heap property (descending)
    int i = 0;
    while (1) {
        int left = 2*i + 1;
        int right = 2*i + 2;
        int smallest = i;

        if (left < pq->size && pq->heap[left].f < pq->heap[smallest].f) smallest = left;
        if (right < pq->size && pq->heap[right].f < pq->heap[smallest].f) smallest = right;

        if (smallest == i) break;

        swap(&pq->heap[i], &pq->heap[smallest]);
        i = smallest;
    }
    return min;
}

int isEmpty(PriorityQueue* pq) {
    return pq->size == 0;
}
