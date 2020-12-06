#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int timestamp;
    double value;
} Record;

typedef struct Node {
    Record data;
    struct Node* next;
} Node;

typedef struct Node2 {
    Node* data;
    struct Node2* next;
} Node2;

void pushBackRecord(Node** head, Node** tail, Record newData) {
    Node* newNode = malloc(sizeof(Node));
    newNode->data = newData;
    newNode->next = NULL;
    if ((*tail) == NULL) {
        *tail = newNode;
        *head = newNode;
    } else {
        (*tail)->next = newNode;
        *tail = newNode;
    }
}

void pushFrontNode(Node2** head, Node* newData) {
    Node2* newNode = malloc(sizeof(Node));
    newNode->data = newData;
    newNode->next = *head;
    *head = newNode;
}

void destroyRecordList(Node** head, Node** tail) {
    Node* current = *head;
    while (current) {
        Node* toDelete = current;
        current = current->next;
        free(toDelete);
    }
    *head = NULL;
    *tail = NULL;
}

void destroyNodesList(Node2** head) {
    Node2* current = *head;
    while (current) {
        Node2* toDelete = current;
        current = current->next;
        free(toDelete);
    }
    *head = NULL;
}

int getSize(Node* head) {
    int size = 0;
    Node* current = head;
    while (current != NULL) {
        size++;
        current = current->next;
    }
    return size;
}

void print(Node* head) {
    Node* current = head;
    printf("%d\n", getSize(head));
    while (current != NULL) {
        printf("%d %.2lf\n", current->data.timestamp, current->data.value);
        current = current->next;
    }
}

double getAvg(double a, double b, double c, double d, double e) {
    double avg = (a + b + c + d + e) / 5;
    return avg;
}

double getStDev(double a, double b, double c, double d, double e) {
    double avg = getAvg(a, b, c, d, e);
    double stdev =
        ((a - avg) * (a - avg) + (b - avg) * (b - avg) + (c - avg) * (c - avg) +
         (d - avg) * (d - avg) + (e - avg) * (e - avg)) /
        5;
    stdev = sqrt(stdev);
    return stdev;
}

int outsideDomain(double min, double max, double value) {
    if (min < value && value < max) {
        return 0;
    }
    return 1;
}

void removeExceptions(Node** head, Node** tail) {
    Node2* head2 = NULL;

    Node* current = *head;
    while (current && current->next && current->next->next &&
           current->next->next->next && current->next->next->next->next) {
        Node* first = current;
        Node* second = first->next;
        Node* third = second->next;
        Node* forth = third->next;
        Node* fifth = forth->next;

        double avg =
            getAvg(first->data.value, second->data.value, third->data.value,
                   forth->data.value, fifth->data.value);

        double stdev =
            getStDev(first->data.value, second->data.value, third->data.value,
                     forth->data.value, fifth->data.value);

        if (outsideDomain(avg - stdev, avg + stdev, third->data.value)) {
            pushFrontNode(&head2, second);
        }
        current = current->next;
    }

    Node2* current2 = head2;
    while (current2) {
        Node* toDelete = (current2->data)->next;
        Node* prev = (current2->data);
        prev->next = prev->next->next;
        free(toDelete);
        current2 = current2->next;
    }
    destroyNodesList(&head2);
}

void swap(double* a, double* b) {
    double temp = *a;
    *a = *b;
    *b = temp;
}

double getMid(double a, double b, double c, double d, double e) {
    if (b < a) {
        swap(&a, &b);
    }
    if (c < a) {
        swap(&a, &c);
    }
    if (d < a) {
        swap(&a, &d);
    }
    if (e < a) {
        swap(&a, &e);
    }
    if (c < b) {
        swap(&b, &c);
    }
    if (d < b) {
        swap(&b, &d);
    }
    if (e < b) {
        swap(&b, &e);
    }
    if (d < c) {
        swap(&d, &c);
    }
    if (e < c) {
        swap(&e, &c);
    }
    return c;
}

void medianFilter(Node** head, Node** tail) {
    Node* newHead = NULL;
    Node* newTail = NULL;

    Node* current = *head;
    while (current && current->next && current->next->next &&
           current->next->next->next && current->next->next->next->next) {
        Node* first = current;
        Node* second = first->next;
        Node* third = second->next;
        Node* forth = third->next;
        Node* fifth = forth->next;

        Record newRecord;
        newRecord.timestamp = third->data.timestamp;
        newRecord.value =
            getMid(first->data.value, second->data.value, third->data.value,
                   forth->data.value, fifth->data.value);
        pushBackRecord(&newHead, &newTail, newRecord);

        current = current->next;
    }
    destroyRecordList(head, tail);
    *head = newHead;
    *tail = newTail;
}

void avgFilter(Node** head, Node** tail) {
    Node* newHead = NULL;
    Node* newTail = NULL;

    Node* current = *head;
    while (current && current->next && current->next->next &&
           current->next->next->next && current->next->next->next->next) {
        Record newRecord;
        newRecord.timestamp = current->next->next->data.timestamp;
        newRecord.value = (current->data.value + current->next->data.value +
                           current->next->next->data.value +
                           current->next->next->next->data.value +
                           current->next->next->next->next->data.value) /
                          5;

        pushBackRecord(&newHead, &newTail, newRecord);
        current = current->next;
    }
    destroyRecordList(head, tail);
    *head = newHead;
    *tail = newTail;
}

void timeUniformize(Node** head, Node** tail) {
    Node* current = *head;
    Record lastRecord = current->data;
    current = current->next;
    while (current) {
        double diff = fabs(current->data.timestamp - lastRecord.timestamp);
        if (diff >= 100 && diff <= 1000) {
            current->data.timestamp =
                (current->data.timestamp + lastRecord.timestamp) / 2;
            current->data.value = (current->data.value + lastRecord.value) / 2;
        }
        lastRecord = current->data;
        current = current->next;
    }
}

double w(int i, int k) {
    double sum = 0;
    for (int j = 0; j < k; ++j) {
        sum += (0.9 * j * j / ((k - 1) * (k - 1)) + 0.1);
    }
    return (0.9 * i * i / ((k - 1) * (k - 1)) + 0.1) / sum;
}

double getC(int timestamp, int leftMarginTimestamp, int rightMarginTimestamp) {
    return 1.0 * (timestamp - leftMarginTimestamp) /
           (rightMarginTimestamp - leftMarginTimestamp);
}

double getNewValue(double left0, double left1, double left2, double right2,
                   double right1, double right0, int timestamp,
                   int leftMarginTimestamp, int rightMarginTimestamp) {
    double C = getC(timestamp, leftMarginTimestamp, rightMarginTimestamp);
    double value =
        (1.0 - C) * (left0 * w(0, 3) + left1 * w(1, 3) + left2 * w(2, 3)) +
        C * (right0 * w(0, 3) + right1 * w(1, 3) + right2 * w(2, 3));
    return value;
}

void completeData(Node** head, Node** tail) {
    Node* current = *head;

    while (current && current->next && current->next->next &&
           current->next->next->next && current->next->next->next->next &&
           current->next->next->next->next) {
        Node* first = current;
        Node* second = first->next;
        Node* third = second->next;
        Node* forth = third->next;
        Node* fifth = forth->next;
        Node* sixth = fifth->next;

        if (((forth->data).timestamp) - ((third->data).timestamp) > 1000) {
            int start = ((third->data).timestamp);
            int end = ((forth->data).timestamp);
            Node* newHead = NULL;
            Node* newTail = NULL;
            for (int timestamp = start + 200; timestamp < end;
                 timestamp += 200) {
                Record newRecord;
                newRecord.timestamp = timestamp;
                newRecord.value = getNewValue(
                    first->data.value, second->data.value, third->data.value,
                    forth->data.value, fifth->data.value, sixth->data.value,
                    timestamp, third->data.timestamp, forth->data.timestamp);
                pushBackRecord(&newHead, &newTail, newRecord);
            }
            third->next = newHead;
            newTail->next = forth;
        }
        current = current->next;
    }
}

int countInside(int start, int end, Node* head) {
    int num = 0;
    Node* current = head;
    while (current) {
        if (start <= (current->data.value) && (current->data.value) <= end) {
            num++;
        }
        current = current->next;
    }
    return num;
}

double getMin(Node* head) {
    double min = 1e9;
    Node* current = head;
    while (current) {
        if ((current->data.value) < min) {
            min = current->data.value;
        }
        current = current->next;
    }
    return min;
}

double getMax(Node* head) {
    double max = -1e9;
    Node* current = head;
    while (current) {
        if ((current->data.value) > max) {
            max = current->data.value;
        }
        current = current->next;
    }
    return max;
}

int main(int argv, char* argc[]) {
    Node* head = NULL;
    Node* tail = NULL;

    int numElements;
    scanf("%d", &numElements);

    for (int i = 0; i < numElements; ++i) {
        int timestamp;
        double value;
        scanf("%d %lf", &timestamp, &value);
        Record newData;
        newData.timestamp = timestamp;
        newData.value = value;
        pushBackRecord(&head, &tail, newData);
    }

    int printList = 1;
    for (int i = 1; i < argv; ++i) {
        if (strcmp(argc[i] + 2, "e1") == 0) {
            removeExceptions(&head, &tail);
        } else if (strcmp(argc[i] + 2, "e2") == 0) {
            medianFilter(&head, &tail);
        } else if (strcmp(argc[i] + 2, "e3") == 0) {
            avgFilter(&head, &tail);
        } else if (strcmp(argc[i] + 2, "u") == 0) {
            timeUniformize(&head, &tail);
        } else if (strcmp(argc[i] + 2, "c") == 0) {
            completeData(&head, &tail);
        } else if (strncmp(argc[i] + 2, "st", 2) == 0) {
            printList = 0;
            int delta = atoi(argc[i] + 4);
            int min = getMin(head);
            min = min - delta - (min % delta);
            int max = getMax(head);
            max = max + delta - (max % delta);
            for (int i = min; i <= max; i += delta) {
                int start = i;
                int end = i + delta;
                int count = countInside(start, end, head);
                if (count) {
                    printf("[%d, %d] %d\n", start, end, count);
                }
            }
        }
    }
    if (printList) print(head);
    destroyRecordList(&head, &tail);
}