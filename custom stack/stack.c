#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 8

int top = -1;
int *stack = NULL;
int sum = 0;
int size = MAX_SIZE;

void push(){
    if (top == size - 1){
        size += MAX_SIZE;
        stack = realloc(stack, size * sizeof(int));
        printf("Memory expand\n");
        if(stack == NULL){
            printf("Memory allocation failed\n");
            exit(1);
        }
    }
    
    int x;
    printf("Enter the element to add onto the stack: ");
    scanf("%d", &x);
    top = top + 1;
    stack[top] = x;
    sum += x;
}

void pop(){
    if (top == -1){
        printf("The stack is empty\n");
    }
    else{
        int temp = stack[top];
        printf("Popped element: %d\n", temp);
        top = top - 1;
        sum -= temp;

        if ((top >= 0) && (top < size - MAX_SIZE)) {
            size -= MAX_SIZE;
            stack = realloc(stack, size * sizeof(int));
            printf("Memory shrink\n");
            if(stack == NULL){
                printf("Memory allocation failed\n");
                exit(1);
            }
        }
    }
}


void peek(){
    printf("Top element on the stack: %d\n", stack[top]);
}

void total(){
    printf("The total value of the elements in the stack: %d\n", sum);
}

void isEmpty(){
    printf("The stack is %s\n", top == -1 ? "empty":"NOT empty");
}

void display(){
    if (top == -1){
        printf("The stack is empty\n");
    }
    else{
        printf("The stack: \n");
        for (int i = top; i >= 0; --i)
            printf("%d\n", stack[i]);
    }
}

int main(){
    int choice;
    
    stack = malloc(size * sizeof(int));
    
    printf("How to use the stack:");
    printf("\n1-Push\n2-Pop\n3-Peek\n4-Total\n5-Is Empty?\n6-Display\n0-Exit\n");
    
    while (1) {
        printf("\nEnter the operation code: ");
        scanf("%d", &choice);

        if (choice == 1)        push();
        else if (choice == 2)   pop();
        else if (choice == 3)   peek();
        else if (choice == 4)   total();
        else if (choice == 5)   isEmpty();
        else if (choice == 6)   display();
        else if (choice == 0)   return 0;
        else                    printf("\nInvalid choice");
    }
    
    free(stack);
    return 0;
}
