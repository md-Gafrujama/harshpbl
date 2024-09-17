// This Pbl is repersent by Abhishek Kumar Singh...
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_QUEUE_SIZE 10

typedef struct {
    int ticketID;
    char name[50];
} Ticket;

typedef struct {
    Ticket tickets[MAX_QUEUE_SIZE];
    int front;
    int rear;
} Queue;

void initQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

int isQueueFull(Queue *q) {
    return (q->rear == MAX_QUEUE_SIZE - 1);
}

int isQueueEmpty(Queue *q) {
    return (q->front == -1 || q->front > q->rear);
}

void bookTicket(Queue *q, int ticketID, char *name) {
    if (isQueueFull(q)) {
        printf("Queue is full. No more tickets can be booked.\n");
        return;
    }
    if (q->front == -1) q->front = 0;
    q->rear++;
    q->tickets[q->rear].ticketID = ticketID;
    strcpy(q->tickets[q->rear].name, name);
    printf("Ticket booked successfully! Ticket ID: %d, Name: %s\n", ticketID, name);
}

void cancelTicket(Queue *q, int ticketID) {
    if (isQueueEmpty(q)) {
        printf("No tickets booked yet to cancel.\n");
        return;
    }

    int found = 0;
    for (int i = q->front; i <= q->rear; i++) {
        if (q->tickets[i].ticketID == ticketID) {
            found = 1;
            for (int j = i; j < q->rear; j++) {
                q->tickets[j] = q->tickets[j + 1];
            }
            q->rear--;
            if (q->rear < q->front) {
                q->front = -1;
                q->rear = -1;
            }
            printf("Ticket ID: %d has been cancelled.\n", ticketID);
            break;
        }
    }

    if (!found) {
        printf("Ticket ID: %d not found.\n", ticketID);
    }
}

void displayQueue(Queue *q) {
    if (isQueueEmpty(q)) {
        printf("No tickets booked yet.\n");
        return;
    }
    printf("List of booked tickets:\n");
    for (int i = q->front; i <= q->rear; i++) {
        printf("Ticket ID: %d, Name: %s\n", q->tickets[i].ticketID, q->tickets[i].name);
    }
}

void processPayment(int ticketID) {
    double amount;
    printf("Processing payment for Ticket ID: %d\n", ticketID);
    printf("Enter amount to pay: ");
    scanf("%lf", &amount);
    printf("Payment of %.2f received for Ticket ID: %d. Booking confirmed!\n", amount, ticketID);
}

int main() {
    Queue concertQueue;
    initQueue(&concertQueue);
    
    int choice;
    int ticketID = 1;
    char name[50];
    int cancelID;

    do {
        printf("\n==== Ticket Booking System ====\n");
        printf("1. Book Concert Ticket\n");
        printf("2. View Booked Concert Tickets\n");
        printf("3. Cancel Ticket\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter your name to book a ticket: ");
                scanf("%s", name);
                bookTicket(&concertQueue, ticketID, name);
                processPayment(ticketID);
                ticketID++;
                break;
            case 2:
                displayQueue(&concertQueue);
                break;
            case 3:
                printf("Enter Ticket ID to cancel: ");
                scanf("%d", &cancelID);
                cancelTicket(&concertQueue, cancelID);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}
// In this project we have four types cases to concluded like Book Concert Ticket, View Booked Concert Tickets, Cancel Ticket
//and my last case is exist of the program Exit