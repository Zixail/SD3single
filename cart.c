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

typedef struct Rails{
    int capacity;
    int count;
    staticDeque* cars;
} Rails;

typedef struct Station{
    Rails* rails;
    int count;
} Station;


Station* readStation(const char* path){
    Station* station = (Station*)malloc(sizeof(Station));

    FILE* fp = fopen(path, "r");

    fscanf(fp, "%d", &station->count);

    station->rails = (Rails*)malloc(station->count * sizeof(Rails));

    for(int i = 0; i < station->count; ++i){
        fscanf(fp, "%d", &station->rails[i].capacity);
        fscanf(fp, "%d", &station->rails[i].count);
        station->rails[i].cars = createStaticDeque(station->rails[i].capacity);

        for(int j = 0; j < station->rails[i].count; ++j){
            int tmp;
            fscanf(fp, "%d", &tmp);
            pushTailStaticDeque(station->rails[i].cars, (char)tmp);
        }
        printf("%d/%d\n", station->rails[i].count, station->rails[i].capacity);
        printStaticDeque(station->rails[i].cars);
    }

    return station;
}

int main(void){
    
    dynamicDeque* train = (dynamicDeque*)malloc(sizeof(dynamicDeque));
    Station* station = readStation("station.txt");



    return 0;
}