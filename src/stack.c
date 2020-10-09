#include "header.h"

// Utility function to initialize stack
stack *newStack(int capacity) {
    stack *pt = (stack *)malloc(sizeof(stack));
    pt->maxsize = capacity;
    pt->top = NULL;
    pt->items = (node**)malloc(sizeof(node*) * capacity);
    return pt;
}

// Utility function to return the size of the stack
int size(stack *pt) {
    int size = 0;
    while (pt->items[size] != NULL) size++;
    return size;
}

// Utility function to check if the stack is empty or not
int isEmpty(stack *pt) {
    return pt->items[0] == NULL;  // or return size(pt) == 0;
}

// Utility function to check if the stack is full or not
int isFull(stack *pt) {
    return size(pt) == pt->maxsize;  // or return size(pt) == pt->maxsize;
}

// Utility function to add an element x in the stack
void push(stack *pt, node *x) {
    // check if stack is already full. Then inserting an element would
    // lead to stack overflow
    if (isFull(pt)) {
        printf("OverFlow\nProgram Terminated\n");
        exit(666);
    }
    pt->top = x;
    pt->items[size(pt)] = x;
}

// Utility function to return top element in a stack
node* peek(stack *pt) {
    // check for empty stack
    if (!isEmpty(pt))
        return pt->items[size(pt) - 1];
    else
        return NULL;
}

// Utility function to pop top element from the stack
node* pop(struct stack *pt) {
    // check for stack underflow
    if (isEmpty(pt)) {
        return NULL;
    }
    node* buffer = peek(pt);
    pt->items[size(pt) - 1] = NULL;
    if (size(pt) > 0)
        pt->top = pt->items[size(pt) - 1];
    else 
        return NULL;
    // decrease stack size by 1 and (optionally) return the popped element
    return buffer;
}
