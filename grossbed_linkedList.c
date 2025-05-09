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
    // Head node will default to 0
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
struct PID_llist* del_node(struct PID_llist *curr, pid_t PID) {
    struct PID_llist *head = curr;
    struct PID_llist *prev = NULL;
    while (curr->next != NULL) {
        // Skip head node == 0
        if (curr->pid != 0) {
            // Check if node to del is head node 
            if (curr->pid == PID) {
                prev->next = curr->next;
                return head;
            } 
        }
        prev = curr;
        curr = curr->next;
    }
    // Check if node to del is the last one
    if (curr->pid != 0) {
        prev->next = NULL;
    }
    return head;
}

void printLinkedList(struct PID_llist *head) {
    struct PID_llist *curr = head;
    while (curr->next != NULL) {
        if (curr->pid != 0) {
            printf("%d \n", curr->pid);
        }
        curr = curr->next;
    }
    printf("%d \n", curr->pid);
}