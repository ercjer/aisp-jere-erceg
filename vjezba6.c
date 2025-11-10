#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct element Element;
typedef Element* Position;

struct element {
	int number;
	Position next;
};

int push(Position, int);
int popOrDequeue(Position);
int enqueue(Position, int);
int clearList(Position);
int printList(Position, int);



int main()
{
	srand((unsigned) time(NULL));
	Element stack; stack.next = NULL;
	Element queue; queue.next = NULL;
	int option = 0, min = 10, max = 100;

	printf("1 - Push\n"
		"2 - Pop\n"
		"3 - Queue\n"
		"4 - Dequeue\n"
		"5 - Ispis stoga\n"
		"6 - Ispis reda\n"
		"7 - Izlaz\n\n");

	while (1) {
		scanf(" %d", &option);
		switch (option) {
		case 1:
			if (push(&stack, (rand() % (max - min + 1) + min)) < 0) {
				clearList(&stack);
				return -1;
			}
			break;
		case 2:
			popOrDequeue(&stack);
			break;
		case 3:
			if (enqueue(&queue, (rand() % (max - min + 1) + min)) < 0) {
				clearList(&queue);
				return -1;
			}
			break;
		case 4:
			popOrDequeue(&queue);
			break;
		case 5:
			printList(&stack, 1);
			break;
		case 6:
			printList(&queue, 0);
			break;
		case 7:
			clearList(&stack);
			clearList(&queue);
			return 0;
		default: 
			printf("Neispravan unos.\n");
			break;
		}
	}

	return 0;
}

int push(Position p, int number) {
	Position q = NULL;
	q = (Position)malloc(sizeof(Element));
	if (q == NULL) {
		printf("Greska pri alokaciji memorije.\n");
		return -1;
	}

	q->number = number;
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

int enqueue(Position p, int number) {
	
	while (p->next != NULL) {
		p = p->next;
	}
	push(p, number);


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
	}

	printf("\n");

	return 0;
}