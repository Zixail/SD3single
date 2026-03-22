// stack.c

#include <stdio.h>
#include <stdlib.h>

typedef struct staticStack {
    int* array;
    int size;
    int last;
} staticStack;

staticStack* createStaticStack(int size){
    staticStack* stack = (staticStack*)malloc(sizeof(staticStack));
    stack->size = size;
    stack->array = (int*)malloc(size * sizeof(int));
    stack->last = 0;
    return stack;
}

int pushStaticStack(staticStack* stack, int elm){
    if (stack->last == stack->size){
        printf("Stack overflowed!\n");
        return -1;
    }

    stack->array[stack->last] = elm;
    stack->last++;
    return 0;
}

int popStaticStack(staticStack* stack){
    if (stack->last == 0){
        printf("Stack empty!\n");
        return ' ';
    }

    stack->last--;
    return stack->array[stack->last];
}

void printStaticStack(staticStack* stack){
    for(int i = stack->last - 1; i >= 0; --i){
        printf("%d --> ", stack->array[i]);
    }
    printf("NULL\n");
}

void freeStaticStack(staticStack* stack){
    if (stack != NULL){
        free(stack->array);
        free(stack);
    }
}

//  Динамичный стек
typedef struct dynamicStack {
    int data;
    struct dynamicStack *ptr_next;
} dynamicStack;

void pushDynamicStack(dynamicStack **head, int symb)
{
    dynamicStack *new_ptr = (struct dynamicStack*)malloc(sizeof(struct dynamicStack));
    if (new_ptr == NULL) {
        printf("Memory allocation error!\n");
        return;
    }

    new_ptr->data = symb;
    new_ptr->ptr_next = *head;
    *head = new_ptr;
}

int popDynamicStack(dynamicStack **head)
{
    if (*head == NULL) {
        printf("dynamicStack is empty\n");
        return 1;
    }

    dynamicStack *temp = *head;
    int value  = temp->data;
    *head = temp->ptr_next;
    free(temp);

    return value;
}

void printDynamicStack(struct dynamicStack *head)
{
    struct dynamicStack *curr = head;
    while (curr != NULL) {
        printf("%d --> ", curr->data);
        curr = curr->ptr_next;
    }
    printf("NULL\n");
}

void freeDynamicStack(struct dynamicStack **head)
{
    while (*head != NULL) {
        struct dynamicStack *temp = *head;
        *head = temp->ptr_next;
        free(temp);
    }
}




// deque.c

typedef struct staticDeque {
    int* array;
    int size;
    int head;
    int tail;
} staticDeque;

staticDeque* createStaticDeque(int size){
    staticDeque* deque = (staticDeque*)malloc(sizeof(staticDeque));
    deque->size = size + 1;
    deque->array = (int*)malloc(deque->size * sizeof(int));
    deque->head = 0;
    deque->tail = 0;
    return deque;
}

int pushHeadStaticDeque(staticDeque* deque, int elm){
    if ((deque->head - deque->tail + deque->size + 1) % deque->size == 0){
        printf("deque overflowed!\n");
        return -1;
    }
    deque->head = (deque->head + 1) % deque->size;
    deque->array[deque->head] = elm;
    return 0;
}

int pushTailStaticDeque(staticDeque* deque, int elm){
    if ((deque->head - deque->tail + deque->size + 1) % deque->size == 0){
        printf("deque overflowed!\n");
        return -1;
    }
    deque->array[deque->tail] = elm;
    deque->tail = (deque->tail - 1 + deque->size) % deque->size;
    return 0;
}

int popHeadStaticDeque(staticDeque* deque){
    if (deque->head == deque->tail){
        printf("deque empty!\n");
        return ' ';
    }

    int smbl = deque->array[deque->head];
    deque->head = (deque->head - 1 + deque->size) % deque->size;
    return smbl;
}

int popTailStaticDeque(staticDeque* deque){
    if (deque->head == deque->tail){
        printf("deque empty!\n");
        return ' ';
    }

    deque->tail = (deque->tail + 1) % deque->size;
    int smbl = deque->array[deque->tail];
    return smbl;
}

void printStaticDeque(staticDeque* deque){
    if (deque->head != deque->tail){
        printf("NULL --> ");
        int i = deque->head;
        while (i != deque->tail) {
            printf("%d -> ", deque->array[i]);
            
            i = (i - 1 + deque->size) % deque->size;
        }
    }
    printf("NULL\n");
}

void freeStaticDeque(staticDeque* deque){
    if (deque != NULL){
        free(deque->array);
        free(deque);
    }
}

//  Динамичный Дек

typedef struct dynamicDeque {
    int data;
    struct dynamicDeque *prev;
    struct dynamicDeque *next;
} dynamicDeque;

typedef struct coord {
    struct dynamicDeque *head;
    struct dynamicDeque *tail;
} coord;

void pushFrontDynamicDeque(struct coord *dq, const int value)
{
    struct dynamicDeque *new_ptr = (struct dynamicDeque*)malloc(sizeof(struct dynamicDeque));
    if (new_ptr == NULL) {
        printf("Memory allocation error!\n");
        return;
    }

    new_ptr->data = value;
    new_ptr->prev = NULL;
    new_ptr->next = dq->head;

    if (dq->head == NULL) {
        dq->tail = new_ptr;
    }
    else {
        dq->head->prev = new_ptr;
    }
    dq->head = new_ptr;
}

void pushBackDynamicDeque(struct coord *dq, const int value)
{
    struct dynamicDeque *new_ptr = (struct dynamicDeque*)malloc(sizeof(struct dynamicDeque));
    if (new_ptr == NULL) {
        printf("Memory allocation error!\n");
        return;
    }

    new_ptr->data = value;
    new_ptr->next = NULL;
    new_ptr->prev = dq->tail;

    if (dq->head == NULL) {
        dq->head = new_ptr;
    }
    else {
        dq->tail->next = new_ptr;
    }
    dq->tail = new_ptr;

}

int popFrontDynamicDeque(struct coord  *dq)
{
    if (dq->head == NULL) {
        printf("deque is empty\n");
        return -1;
    }

    struct dynamicDeque *temp = dq->head;
    int value = temp->data;
    dq->head = dq->head->next;
    if (dq->head == NULL) {
        dq->tail = NULL;
    }
    else {
        dq->head->prev = NULL;
    }
    free(temp);

    return value;
}

int popBackDynamicDeque(struct coord *dq)
{
    if (dq->head == NULL) {
        printf("deque is empty\n");
        return -1;
    }

    struct dynamicDeque *temp = dq->tail;
    int value = temp->data;
    dq->tail = dq->tail->prev;
    if (dq->tail == NULL) {
        dq->head = NULL;
    }
    else {
        dq->tail->next = NULL;
    }
    free(temp);

    return value;
}

void printDynamicDeque(struct coord *dq)
{
    struct dynamicDeque *curr = dq->head;
    if (dq->head != NULL){
        printf("NULL --> ");
        while (curr != NULL) {
            printf("%d --> ", curr->data);
            curr = curr->next;
    }
    }
    printf("NULL\n");
}

void freeDynamicDeque(struct coord *dq)
{
    while (dq->head != NULL) {
        struct dynamicDeque *temp = dq->head;
        dq->head = temp->next;
        free(temp);
    }
    dq->tail = NULL;
}


// main.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum Program{
    PROG_EXIT = 0,
    STATIC_STACK_TEST = 1,
    DYNAMIC_STACK_TEST = 2,
    STATIC_DEQUE_TEST = 3,
    DYNAMIC_DEQUE_TEST = 4,
    PROG_NEED_CHOICE = 5
};

enum StackOperation{
    STACK_EXIT = 0,
    STACK_PUSH = 1,
    STACK_POP = 2,
    STACK_PRINT = 3,
    STACK_NEED_CHOICE = 4
};

enum DequeOperation{
    DEQUE_EXIT = 0,
    DEQUE_PUSH_FRONT = 1,
    DEQUE_PUSH_BACK = 2,
    DEQUE_POP_FRONT = 3,
    DEQUE_POP_BACK = 4,
    DEQUE_PRINT = 5,
    DEQUE_NEED_CHOICE = 6
};

void testStaticStack(){
    int size;
    printf("Select stack size: ");
    scanf("%d", &size);
    staticStack* stack = createStaticStack(size);

    enum StackOperation op = STACK_NEED_CHOICE;
    while(op == STACK_NEED_CHOICE){
        int choice;
        printf("\t--------------------------\n");
        printf("\t|  Choose option         |\n");
        printf("\t|  1. Push               |\n");
        printf("\t|  2. Pop                |\n");
        printf("\t|  3. Print              |\n");
        printf("\t|  0. Exit               |\n");
        printf("\t--------------------------\n");
        printf("Select: ");
        scanf("%d", &choice);

        if (choice < 0 || choice > 3) choice = 4;
        op = choice;
        
        switch(op){
            case (STACK_EXIT):
                freeStaticStack(stack);
                return;
            case (STACK_NEED_CHOICE):
                break;
            case (STACK_PUSH):
                int smbl;
                printf("Push: ");
                scanf(" %d", &smbl);
                pushStaticStack(stack, smbl);
                break;
            case (STACK_POP):
                int elm = popStaticStack(stack);
                printf("Pop: %d\n", elm);
                break;
            case (STACK_PRINT):
                printStaticStack(stack);
                break;
        }
        op = STACK_NEED_CHOICE;
    }
}

void testDynamicStack(){
    dynamicStack *head = NULL;

    enum StackOperation op = STACK_NEED_CHOICE;
    while(op == STACK_NEED_CHOICE){
        int choice;
        printf("\t--------------------------\n");
        printf("\t|  Choose option         |\n");
        printf("\t|  1. Push               |\n");
        printf("\t|  2. Pop                |\n");
        printf("\t|  3. Print              |\n");
        printf("\t|  0. Exit               |\n");
        printf("\t--------------------------\n");
        printf("Select: ");
        scanf("%d", &choice);

        if (choice < 0 || choice > 3) choice = 4;
        op = choice;
        
        switch(op){
            case (STACK_EXIT):
                freeDynamicStack(&head);
                return;
            case (STACK_NEED_CHOICE):
                break;
            case (STACK_PUSH):
                int smbl;
                printf("Push: ");
                scanf(" %d", &smbl);
                pushDynamicStack(&head, smbl);
                break;
            case (STACK_POP):
                int elm = popDynamicStack(&head);
                printf("Pop: %d\n", elm);
                break;
            case (STACK_PRINT):
                printDynamicStack(head);
                break;
        }
        op = STACK_NEED_CHOICE;
    }
}

void testStaticDeque(){
    int size;
    printf("Select stack size: ");
    scanf("%d", &size);
    staticDeque* deque = createStaticDeque(size);

    enum DequeOperation op = DEQUE_NEED_CHOICE;
    while(op == DEQUE_NEED_CHOICE){
        int choice;
        printf("\t--------------------------\n");
        printf("\t|  Choose option         |\n");
        printf("\t|  1. Push Front         |\n");
        printf("\t|  2. Push Back          |\n");
        printf("\t|  3. Pop Front          |\n");
        printf("\t|  4. Pop Back           |\n");
        printf("\t|  5. Print              |\n");
        printf("\t|  0. Exit               |\n");
        printf("\t--------------------------\n");
        printf("Select: ");
        scanf("%d", &choice);

        if (choice < 0 || choice > 5) choice = 6;
        op = choice;
        
        switch(op){
            case (DEQUE_EXIT):
                freeStaticDeque(deque);
                return;
            case (DEQUE_NEED_CHOICE):
                break;
            case (DEQUE_PUSH_FRONT):
                int smblf;
                printf("Push: ");
                scanf(" %d", &smblf);
                pushHeadStaticDeque(deque, smblf);
                break;
            case (DEQUE_PUSH_BACK):
                int smblb;
                printf("Push: ");
                scanf(" %d", &smblb);
                pushTailStaticDeque(deque, smblb);
                break;
            case (DEQUE_POP_FRONT):
                int elmf = popHeadStaticDeque(deque);
                printf("Pop: %d\n", elmf);
                break;
            case (DEQUE_POP_BACK):
                int elmb = popTailStaticDeque(deque);
                printf("Pop: %d\n", elmb);
                break;
            case (DEQUE_PRINT):
                printStaticDeque(deque);
                break;
        }
        op = DEQUE_NEED_CHOICE;
    }
}

void testDynamicDeque(){
    coord dq;
    dq.head = NULL;
    dq.tail = NULL;

    enum DequeOperation op = DEQUE_NEED_CHOICE;
    while(op == DEQUE_NEED_CHOICE){
        int choice;
        printf("\t--------------------------\n");
        printf("\t|  Choose option         |\n");
        printf("\t|  1. Push Front         |\n");
        printf("\t|  2. Push Back          |\n");
        printf("\t|  3. Pop Front          |\n");
        printf("\t|  4. Pop Back           |\n");
        printf("\t|  5. Print              |\n");
        printf("\t|  0. Exit               |\n");
        printf("\t--------------------------\n");
        printf("Select: ");
        scanf("%d", &choice);

        if (choice < 0 || choice > 5) choice = 6;
        op = choice;
        
        switch(op){
            case (DEQUE_EXIT):
                freeDynamicDeque(&dq);
                return;
            case (DEQUE_NEED_CHOICE):
                break;
            case (DEQUE_PUSH_FRONT):
                int smblf;
                printf("Push: ");
                scanf(" %d", &smblf);
                pushFrontDynamicDeque(&dq, smblf);
                break;
            case (DEQUE_PUSH_BACK):
                int smblb;
                printf("Push: ");
                scanf(" %d", &smblb);
                pushBackDynamicDeque(&dq, smblb);
                break;
            case (DEQUE_POP_FRONT):
                int elmf = popFrontDynamicDeque(&dq);
                printf("Pop: %d\n", elmf);
                break;
            case (DEQUE_POP_BACK):
                int elmb = popBackDynamicDeque(&dq);
                printf("Pop: %d\n", elmb);
                break;
            case (DEQUE_PRINT):
                printDynamicDeque(&dq);
                break;
        }
        op = DEQUE_NEED_CHOICE;
    }
}

int main(void){
    enum Program op = PROG_NEED_CHOICE;
    while(op == PROG_NEED_CHOICE){

        int choice;
        printf("\t--------------------------\n");
        printf("\t|  Choose option         |\n");
        printf("\t|  1. Static stack       |\n");
        printf("\t|  2. Dinamic stack      |\n");
        printf("\t|  3. Static deque       |\n");
        printf("\t|  4. Dinamic deque      |\n");
        printf("\t|  0. Exit               |\n");
        printf("\t--------------------------\n");
        printf("Select: ");
        scanf("%d", &choice);

        if (choice < 0 || choice > 4) choice = 5;
        op = choice;
        
        switch(op){
            case (PROG_EXIT):
                return 0;
            case (PROG_NEED_CHOICE):
                break;
            case (STATIC_STACK_TEST):
                testStaticStack();
                break;
            case (DYNAMIC_STACK_TEST):
                testDynamicStack();
                break;
            case (STATIC_DEQUE_TEST):
                testStaticDeque();
                break;
            case (DYNAMIC_DEQUE_TEST):
                testDynamicDeque();
                break;
        }
        op = PROG_NEED_CHOICE;
    }

    return 0;
}