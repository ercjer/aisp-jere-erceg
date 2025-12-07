#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct element Element;
typedef Element* Position;

struct element {
	int number;
	Position next;
};

int readFromFile(char[]);
int push(Position, int);
int pop(Position);
int operation(Position, char[]);




// postfix.txt
int main()
{
	char filename[16];


	printf("Unesi ime datoteke: ");
	scanf(" %s", filename);

	readFromFile(filename);





	return 0;
}

int readFromFile(char filename[]) {
	char znak[16];
	int broj = 0;
	FILE *fp = NULL;
	Element stack; stack.next = NULL;

	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Greska pri otvaranju filea.\n");
		return -1;
	}


	while (fscanf(fp, " %s", znak) == 1) {
		//fscanf(fp, " %s", znak);
		if (strcmp(znak, "+") == 0 || strcmp(znak, "-") == 0 ||
			strcmp(znak, "*") == 0 || strcmp(znak, "/") == 0) {
			broj = operation(&stack, znak);
			push(&stack, broj);
		}
		else {
			broj = atoi(znak);
			if (push(&stack, broj) < 0) {
				return -1;
			}
		}
	}

	broj = pop(&stack);
	printf("Rezultat je: %d", broj);


	fclose(fp);
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

int pop(Position p) {
	int broj = 0;
	if (p->next == NULL) {
		printf("Stog je prazan.\n");
		return 0;
	}

	Position q = p->next;
	p->next = q->next;
	broj = q->number;
	free(q);

	return broj;
}

int operation(Position p, char znak[]) {
	int rez = 0, op1 = 0, op2 = 0;

	if (strcmp(znak, "+") == 0) {
		op2 = pop(p);
		op1 = pop(p);
		rez = op1 + op2;
	}
	else if (strcmp(znak, "-") == 0) {
		op2 = pop(p);
		op1 = pop(p);
		rez = op1 - op2;
	}
	else if (strcmp(znak, "*") == 0) {
		op2 = pop(p);
		op1 = pop(p);
		rez = op1 * op2;
	}
	else if (strcmp(znak, "/") == 0) {
		op2 = pop(p);
		if (op2 == 0) {
			printf("Djeljenje sa 0 nije moguce.\n");
			return -1;
		}
		op1 = pop(p);
		rez = op1 / op2;
	}

	return rez;
}


