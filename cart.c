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

typedef struct Train{
    dynamicStack* cars;
    int countCur;
    int countPlan;
    int* plan;
} Train;

typedef struct Station{
    Train train;
    Rails* rails;
    int count;
} Station;


Station* initStation(const char* path){
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
    }

    station->train.cars = NULL;
    fscanf(fp, "%d", &station->train.countPlan);
    station->train.countCur = 0;
    station->train.plan = (int*)malloc(station->train.countPlan * sizeof(int));
    for(int i = 0; i < station->train.countPlan; ++i){
        fscanf(fp, "%d", &station->train.plan[i]);
    }

    return station;
}

char isFormed(Station* station){
    if (station->train.countCur == station->train.countPlan){
        char flag = 1;
        for(int i = 0; i < station->train.countPlan; ++i){
            dynamicStack* ptr = station->train.cars;
            while(ptr != NULL){
                if (station->train.plan[i] == ptr->data){
                    flag = 1;
                    break;
                }
                else{
                    ptr = ptr->ptr_next;
                    flag = 0;
                }
            }
            if (flag == 0) return 0;
        }
        return 1;
    }
    return 0;
}

int getSide(Rails* rails, Train* train) {
    if (rails->cars->head == rails->cars->tail) return 0;

    int fromHead = -1;
    int fromTail = -1;
    int totalCount = 0;

    int i = rails->cars->head;
    int currentStep = 1;

    while (i != rails->cars->tail) {
        char isNeeded = 0;
        for (int j = 0; j < train->countPlan; j++) {
            if (rails->cars->array[i] == train->plan[j]) {
                isNeeded = 1;
                break;
            }
        }

        if (isNeeded) {
            if (fromHead == -1) fromHead = currentStep;
            fromTail = currentStep; 
        }

        i = (i - 1 + rails->cars->size) % rails->cars->size;
        currentStep++;
    }
    
    totalCount = currentStep - 1;

    if (fromHead == -1) return 0;

    int distFromTail = (totalCount - fromTail) + 1;

    if (fromHead <= distFromTail) {
        return fromHead;
    } else {
        return -distFromTail;
    }
}

int main(int argc, char* argv[]){

    char verbose;
    if (argc < 2) return 0;
    if (argc == 2) verbose = 0;
    verbose = atoi(argv[2]) > 0;\

    int LINE_ADD = 0;
    int LINE_REMOVE = 0;
    int TRAIN_ADD = 0;
    int TRAIN_REMOVE = 0;

    Station* station = initStation(argv[1]);
    
    while(!isFormed(station)){
        for(int i = 0; i < station->count; ++i){
            int k = getSide(&station->rails[i], &station->train);

            if (k > 0){
                for(int l = 0; l < k; ++l){
                    int car = popHeadStaticDeque(station->rails[i].cars);
                    LINE_REMOVE++;
                    station->rails[i].count--;
                    pushDynamicStack(&station->train.cars, car);
                    TRAIN_ADD++;
                    station->train.countCur++;
                    if (verbose) printf("CART_%d LINE_%d<S> TRAIN\n", car, i + 1);
                }
            }

            if (k < 0){
                for(int l = 0; l < -k; ++l){
                    int car = popTailStaticDeque(station->rails[i].cars);
                    LINE_REMOVE++;
                    station->rails[i].count--;
                    pushDynamicStack(&station->train.cars, car);
                    TRAIN_ADD++;
                    station->train.countCur++;
                    if (verbose) printf("CART_%d LINE_%d<E> TRAIN\n", car, i + 1);
                }
            }
        }

        for(int i = 0; i < station->count && station->train.countCur != 0; ++i){
            while(station->rails[i].capacity != station->rails[i].count && station->train.countCur != 0){
                int car = popDynamicStack(&station->train.cars);
                TRAIN_REMOVE++;
                station->train.countCur--;
                char isNeeded = 0;
                for(int j = 0; j < station->train.countPlan; ++j){
                    if (station->train.plan[j] == car){
                        isNeeded = 1;
                        break;
                    }
                }
                if (isNeeded){
                    pushHeadStaticDeque(station->rails[i].cars, car);
                    LINE_ADD++;
                    station->rails[i].count++;
                    if (verbose) printf("CART_%d TRAIN LINE_%d<S>\n", car, i + 1);
                }
                else{
                    pushTailStaticDeque(station->rails[i].cars, car);
                    LINE_ADD++;
                    station->rails[i].count++;
                    if (verbose) printf("CART_%d TRAIN LINE_%d<E>\n", car, i + 1);
                }
            }
        }

        for(int i = 0; i < station->count; ++i){
            char isNeeded = 1;
            if(station->rails[i].count == 0) continue;
            while(isNeeded){
                for(int j = 0; j < station->train.countPlan; ++j){
                    isNeeded = 1;
                    if (station->train.plan[j] != station->rails[i].cars->array[station->rails[i].cars->head]){
                        isNeeded = 0;
                    }
                    else{
                        int car = popHeadStaticDeque(station->rails[i].cars);
                        LINE_REMOVE++;
                        station->rails[i].count--;
                        pushDynamicStack(&station->train.cars, car);
                        TRAIN_ADD++;
                        if (verbose) printf("CART_%d LINE_%d<S> TRAIN\n", car, i + 1);
                        station->train.countCur++;
                    }
                }
            }
        }

    }

    int TOTAL = LINE_ADD + LINE_REMOVE + TRAIN_ADD + TRAIN_REMOVE;
    printf("LINE_ADD: %d\n", LINE_ADD);
    printf("LINE_REMOVE: %d\n", LINE_REMOVE);
    printf("TRAIN_ADD: %d\n", TRAIN_ADD);
    printf("TRAIN_REMOVE: %d\n", TRAIN_REMOVE);
    printf("TOTAL: %d\n", TOTAL);



    return 0;
}