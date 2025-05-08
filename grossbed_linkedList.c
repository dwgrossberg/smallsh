#include "grossbed_assignment4.h"

/*
    Function: add_node: add a node to the linked list
    Params: pointer to PID_llist struct - head of LL with all children PIDs, pid_t PID
    Returns: none
*/
void add_node(struct PID_llist *head, pid_t PID) {
    struct PID_llist *curr = head;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    // Allocate mem for new node
    curr->next = (struct PID_llist *) malloc(sizeof(struct PID_llist));
    curr = curr->next;
    // Add new PID
    curr->pid = PID;
}


/*
    Function: delete_node: delete a node from the linked list
    Params: pointer to PID_llist struct - head of LL with all children PIDs
    Returns: none
*/
struct PID_llist* del_node(struct PID_llist *head, pid_t PID) {
    struct PID_llist *curr = head;
    
}

void printLinkedList(struct PID_llist *head) {
    struct PID_llist *curr = head;
    while (curr->next != NULL) {
        printf("%d \n", curr->pid);
        curr = curr->next;
    }
    printf("%d \n", curr->pid);
}