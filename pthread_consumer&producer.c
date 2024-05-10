#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>

// Define the structure for messages to be enqueued
typedef struct {
    int request_id;
    const char *msg;
} msg_t;

// Define the queue data structure
typedef struct node {
    msg_t message;
    struct node *next;
} node_t;

typedef struct {
    node_t *front;
    node_t *rear;
    int size;
    pthread_mutex_t lock;
    pthread_cond_t cond;
} queue_t;

// Initialize the queue
void queue_init(queue_t *q) {
    q->front = q->rear = NULL;
    q->size = 0;
    pthread_mutex_init(&q->lock, NULL);
    pthread_cond_init(&q->cond, NULL);
}

// Enqueue a message into the queue
void enqueue(queue_t *q, msg_t message) {
    node_t *new_node = malloc(sizeof(node_t));
    new_node->message = message;
    new_node->next = NULL;

    pthread_mutex_lock(&q->lock);
    if (q->size == 0) {
        q->front = q->rear = new_node;
    } else {
        q->rear->next = new_node;
        q->rear = new_node;
    }
    q->size++;
    pthread_mutex_unlock(&q->lock);
    pthread_cond_signal(&q->cond);
}

// Dequeue a message from the queue
msg_t dequeue(queue_t *q) {
    pthread_mutex_lock(&q->lock);
    while (q->size == 0) {
        pthread_cond_wait(&q->cond, &q->lock);
    }

    msg_t message = q->front->message;
    node_t *temp = q->front;

    if (q->size == 1) {
        q->front = q->rear = NULL;
    } else {
        q->front = q->front->next;
    }
    q->size--;
    free(temp);

    pthread_mutex_unlock(&q->lock);

    return message;
}

// Define the producer thread function
void *producer(void *arg) {
    queue_t *q = (queue_t *) arg;

    int request_id = 0;
    while (1) {
        // Generate a random message string
        char *msg = malloc(10 * sizeof(char));
        sprintf(msg, "Message %d", request_id);

        // Enqueue the message
        msg_t message = {request_id, msg};
        enqueue(q, message);

        request_id++;
        sleep(1); // Sleep for a second before enqueuing the next message
    }

    return NULL;
}

// Define the consumer thread function
void *consumer(void *arg) {
    queue_t *q = (queue_t *) arg;

    while (1) {
        // Dequeue the next message
        msg_t message = dequeue(q);

        // Print the message to the console
        printf("[%d] %s\n", message.request_id, message.msg);

        // Free the message string memory
        free((void *) message.msg);
    }

    return NULL;
}

// Signal handler for SIGINT
void sigint_handler(int sig) {
    exit(0);
}

int main() {
    // Initialize the queue
    queue_t q;
    queue_init(&q);

    // Set up the signal handler for SIGINT
    signal(SIGINT, sigint_handler);

    // Create the producer and consumer threads
    pthread_t producer_thread, consumer_thread;
    pthread_create(&producer_thread, NULL, producer, &q);
    pthread_create(&consumer_thread, NULL, consumer, &q);

    // Wait for the threads to complete (which should never happen)
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    return 0;
}
