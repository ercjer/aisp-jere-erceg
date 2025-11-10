#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct list List;
typedef List* Position;


struct list {
	int number;
	Position next;
};


int readListFromFile(Position, char[]);
int addSorted(Position, int);
int clearList(Position);
int unijaListi(Position, Position, Position);
int presjekListi(Position, Position, Position);



int main()
{
	List list1; list1.next = NULL;
	List list2; list2.next = NULL;
	List unija; unija.next = NULL;
	List presjek; presjek.next = NULL;
	char fileName1[16], fileName2[16];
	//list1.txt list2.txt

	printf("Unesi ime prvog filea: ");	scanf(" %s", fileName1);
	printf("Unesi ime drugog filea: ");	scanf(" %s", fileName2);

	if (readListFromFile(&list1, fileName1) < 0) {
		clearList(&list1);
		return -1;
	}

	if (readListFromFile(&list2, fileName2) < 0) {
		clearList(&list1);
		clearList(&list2);
		return -1;
	}

	if (unijaListi(&list1, &list2, &unija) < 0) {
		clearList(&list1);
		clearList(&list2);
		clearList(&unija);
		return -1;
	}

	if(presjekListi(&list1, &list2, &presjek) < 0 ) {
		clearList(&list1);
		clearList(&list2);
		clearList(&unija);
		return -1;
	}



	return 0;
}

int readListFromFile(Position p, char fileName[16]) {
	FILE* fp = NULL;
	int number = 0;

	fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("Greska pri otvaranju filea.\n");
		return -1;
	}

	while (!feof(fp)) {
		fscanf(fp, " %d", &number);
		if (addSorted(p, number) < 0) {
			fclose(fp);
			return -1;
		}
	}



	fclose(fp);
	return 0;
}

int addSorted(Position p, int number) {
	Position q = NULL;
	q = (Position)malloc(sizeof(List));
	if (q == NULL) {
		printf("Greska pri alokaciji memorije.\n");
		return -1;
	}

	if (p->next == NULL) {
		q->number = number;
		q->next = p->next;
		p->next = q;
	}
	else {
		while (p->next != NULL && p->next->number < number) {
			p = p->next;
		}
		q->number = number;
		q->next = p->next;
		p->next = q;
	}

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

int unijaListi(Position list1, Position list2, Position unija) {
	list1 = list1->next;
	list2 = list2->next;

	while (list1 != NULL && list2 != NULL) {
		if (list1->number < list2->number) {
			if (addSorted(unija, list1->number) < 0) {
				return -1;
			}
			list1 = list1->next;
		}
		else if (list1->number > list2->number) {
			if (addSorted(unija, list2->number) < 0) {
				return -1;
			}
			list2 = list2->next;
		}
		else if(list1->number == list2->number) {
			if (addSorted(unija, list1->number) < 0) {
				return -1;
			}
			list1 = list1->next;
			list2 = list2->next;
		}
	}

	while (list1 != NULL) {
		if (addSorted(unija, list1->number) < 0) {
			return -1;
		}
		list1 = list1->next;
	}
	while (list2 != NULL) {
		if (addSorted(unija, list2->number) < 0) {
			return -1;
		}
		list2 = list2->next;
	}

	printf("Unija: ");
	unija = unija->next;
	while (unija != NULL) {
		printf("%d ", unija->number);
		unija = unija->next;
	}




	return 0;
}

int presjekListi(Position list1, Position list2, Position presjek) {
	list1 = list1->next;
	list2 = list2->next;

	while (list1 != NULL && list2 != NULL) {
		if (list1->number > list2->number) {
			list2 = list2->next;
		}
		else if (list1->number < list2->number) {
			list1 = list1->next;
		}
		else {
			if (addSorted(presjek, list1->number) < 0) {
				return -1;
			}
			list1 = list1->next;
			list2 = list2->next;
		}
	}

	printf("\nPresjek: ");
	presjek = presjek->next;
	while (presjek != NULL) {
		printf("%d ", presjek->number);
		presjek = presjek->next;
	}


	return 0;
}
