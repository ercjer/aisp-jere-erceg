#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct element Element;
typedef Element* Position;

struct element {
	int number;
	int priority;
	Position next;
};


int push(Position, int);
int popOrDequeue(Position);
int enqueue(Position, int, int);
int clearList(Position);
int printList(Position, int);
int stack();
int queue();


int main()
{
	int option = 0;

	while (1) {
		printf("1 - Stog sa maksimalnim brojem elemenata\n"
			"2 - Red s prioritetom\n"
			"3 - Izlaz iz programa\n\n");
		scanf(" %d", &option);
		
		switch (option) {
		case 1:
			stack();
			break;
		case 2:
			queue();
			break;
		case 3:
			return 0;
		default:
			printf("Neispravan unos.\n");
			break;
		}
	}

	return 0;
}


int stack() {
	srand((unsigned)time(NULL));
	Element stack; stack.next = NULL;
	int option = 0, min = 10, max = 100, maxStack = 0, stackCount = 0;
	while (maxStack <= 0) {
		printf("Maksimalni broj elemenata stoga: ");	scanf(" %d", &maxStack);
	}

	printf("1 - Push\n"
		"2 - Pop\n"
		"3 - Ispis stoga\n"
		"4 - Izlaz iz stoga\n\n");

	while (1) {
		scanf(" %d", &option);
		switch (option) {
		case 1:
			stackCount++;
			if (stackCount <= maxStack) {
				if (push(&stack, (rand() % (max - min + 1) + min)) < 0) {
					clearList(&stack);
					return -1;
				}
			}
			else {
				printf("Dosegnut maksimalan broj elemenata stoga.\n");
				stackCount--;
			}
			break;
		case 2:
			if (stackCount > 0) {
				stackCount--;
			}
			popOrDequeue(&stack);
			break;
		case 3:
			printList(&stack, 1);
			break;
		case 4:
			clearList(&stack);
			return 0;
		}
	}
}

int queue() {
	srand((unsigned)time(NULL));
	Element queue; queue.next = NULL;
	int option = 0, min = 10, max = 100;
	int minPriority = 1, maxPriority = 5;

	printf("1 - Queue\n"
		"2 - Dequeue\n"
		"3 - Ispis reda\n"
		"4 - Izlaz iz reda\n\n");

	while (1) {
		scanf(" %d", &option);
		
		switch (option) {
		case 1:
			
			if (enqueue(&queue, (rand() % (max - min + 1) + min), (rand() % (maxPriority - minPriority + 1) + minPriority)) < 0) {
				clearList(&queue);
				return -1;
			}
			break;
		case 2:
			popOrDequeue(&queue);
			break;
		case 3:
			printList(&queue, 0);
			break;
		case 4:
			clearList(&queue);
			return 0;
		default:
			printf("Neispravan unos\n");
			break;
		}
	}
}


int push(Position p, int number) {
	Position q = NULL;
	q = (Position)malloc(sizeof(Element));
	if (q == NULL) {
		printf("Greska pri alokaciji memorije.\n");
		return -1;
	}

	q->number = number;
	q->priority = 0;
	q->next = p->next;
	p->next = q;


	return 0;
}

int popOrDequeue(Position p) {
	if (p->next == NULL) {
		printf("Stog je prazan.\n");
		return 0;
	}

	Position q = p->next;
	p->next = q->next;
	free(q);

	return 0;
}

int enqueue(Position p, int number, int priority) {

	while (p->next != NULL && p->next->priority >= priority) {
		p = p->next;
	}

	Position q = NULL;
	q = (Position)malloc(sizeof(Element));
	if (q == NULL) {
		printf("Greska pri alokaciji memorije.\n");
		return -1;
	}

	q->priority = priority;
	q->number = number;
	q->next = p->next;
	p->next = q;


	return 0;
}

int clearList(Position head) {
	while (head->next != NULL) {
		Position p = head->next;
		head->next = p->next;
		free(p);
	}
	return 0;
}

int printList(Position p, int isStack) {
	if (isStack) {
		printf("Stog:\n");
	}
	else {
		printf("Red: ");
	}

	if (p->next == NULL) {
		printf("Prazno\n");
	}

	while (p->next != NULL) {
		p = p->next;
		printf("%d ", p->number);
		if (isStack) {
			printf("\n");
		}
		else {
			printf("(P = %d) ", p->priority);
		}
	}

	printf("\n");

	return 0;
}





