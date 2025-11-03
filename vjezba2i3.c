#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct person Person;
typedef Person* Position;


struct person {
	char firstName[32];
	char lastName[32];
	int yearOfBirth;

	Position next;
};

int addStart(Position prev);
int printList(Position p);
int addEnd(Position p);
Position createNode(Position p);
int searchList(Position p);
int getAction(int actionOrSearch);
int clearMemory(Position p);
int deleteElement(Position p);
int addElementAfter(Position p);
int comparePersons(Position p, char name[16], char lastName[16], int year);
int addElementBefore(Position p);
int writeListInFile(Position p);
int readListFromFile(Position p);
int addSorted(Position p, char name[16], char lastName[16], int year);

int main()
{
	Person head;
	head.next = NULL;
	int action = -1;
	int isRunning = 1;


	printf("Odaberite akciju unosom broja:\n"
		"1 - Dodavanje osobe na pocetak liste.\n"
		"2 - Ispis liste.\n"
		"3 - Dodavanje osobe na kraj liste.\n"
		"4 - Trazenje osobe po imenu, prezimenu ili godini.\n"
		"5 - Brisanje odredene osobe.\n"
		"6 - Dodavanje osobe iza odredene.\n"
		"7 - Dodavanje osobe ispred odredene.\n"
		"8 - Upisuje listu u datoteku.\n"
		"9 - Sortirano po prezimenu, ucitava listu iz datoteke.\n"
		"10 - Izlaz iz programa.\n\n");

	while (isRunning) {
		action = getAction(0);


		switch (action) {
		case 1:
			if (addStart(&head) < 0) {
				clearMemory(&head);
				return -1;
			}
			break;
		case 2:
			printList(&head);
			break;
		case 3:
			if (addEnd(&head) < 0) {
				clearMemory(&head);
				return -1;
			}
			break;
		case 4:
			searchList(&head);
			break;
		case 5:
			deleteElement(&head);
			break;
		case 6:
			if (addElementAfter(&head) < 0) {
				clearMemory(&head);
				return -1;
			}
			break;
		case 7:
			if (addElementBefore(&head) < 0) {
				clearMemory(&head);
				return -1;
			}
			break;
		case 8:
			if (writeListInFile(&head) < 0) {
				clearMemory(&head);
				return -1;
			}
			break;
		case 9:
			if (readListFromFile(&head) < 0) {
				clearMemory(&head);
				return -1;
			}
			break;
		case 10:
			isRunning = 0;
			clearMemory(&head);
			break;
		default:
			printf("Neispravan unos.\n");
		}
	}

	return 0;
}


int addStart(Position prev) {
	Position p = NULL;
	p = createNode(p);
	if (p == NULL) {
		printf("Greska u alokaciji memorije.\n");
		return -1;
	}

	printf("Unesi ime, prezime i godinu rodenja: ");
	scanf(" %s %s %d", p->firstName, p->lastName, &p->yearOfBirth);

	p->next = prev->next;
	prev->next = p;

	return 0;
}

int printList(Position p) {
	if (p->next == NULL) {
		printf("Lista je prazna.\n");
		return 0;
	}
	while (p->next != NULL) {
		p = p->next;
		printf("%s %s %d\n", p->firstName, p->lastName, p->yearOfBirth);
	}
	return 0;
}

int addEnd(Position p) {
	Position q = NULL;
	q = createNode(q);
	if (q == NULL) {
		printf("Greska u alokaciji memorije.\n");
		return -1;
	}

	while (p->next != NULL) {
		p = p->next;
	}
	addStart(p);

	return 0;
}

Position createNode(Position p) {
	p = (Position)malloc(sizeof(Person));
	return p;
}

int searchList(Position p) {
	char searchByName[32];
	int searchByYear;
	int option = 0;

	if (p->next == NULL) {
		printf("Lista je prazna.\n");
		return 0;
	}

	while (option > 3 || option < 1) {
		printf("Izaberi po cemu zelis traziti:\n1 - Po imenu.\n2 - Po prezimenu.\n3 - Po godini.\n");
		option = getAction(1);
	}

	switch (option) {
	case 1:
		printf("Unesi ime: ");	scanf(" %s", searchByName);
		while (p->next != NULL) {
			p = p->next;
			if (_strcmpi(p->firstName, searchByName) == 0) {
				printf("Prvi je pronaden %s %s %d\n", p->firstName, p->lastName, p->yearOfBirth);
				return 0;
			}
		}
		printf("Nije pronadena osoba sa imenom %s.\n", searchByName);
		return 0;

	case 2:
		printf("Unesi prezime: ");	scanf(" %s", searchByName);
		while (p->next != NULL) {
			p = p->next;
			if (_strcmpi(p->lastName, searchByName) == 0) {
				printf("Prvi je pronaden %s %s %d\n", p->firstName, p->lastName, p->yearOfBirth);
				return 0;
			}
		}
		printf("Nije pronadena osoba sa prezimenom %s.\n", searchByName);
		return 0;
	case 3:
		printf("Unesi godinu: ");	scanf(" %d", &searchByYear);
		while (p->next != NULL) {
			p = p->next;
			if (searchByYear == p->yearOfBirth) {
				printf("Prvi je pronaden %s %s %d\n", p->firstName, p->lastName, p->yearOfBirth);
				return 0;
			}
		}
		printf("Nije pronadena osoba sa godinom rodenja %d.\n", searchByYear);
		return 0;
	default:
		printf("Neispravan unos.\n");
	}


	return 0;
}

int getAction(int actionOrSearch) {
	char inputAction[32];
	int check = 1;
	int action = 0;
	while (1) {
		check = 1;
		scanf(" %s", inputAction);

		for (int i = 0; i < strlen(inputAction); i++) {
			if (!isdigit(inputAction[i])) {
				check = 0;
				break;
			}
		}
		if (check == 0 && actionOrSearch == 1) {
			printf("Izaberi po cemu zelis traziti:\n1 - Po imenu.\n2 - Po prezimenu.\n3 - Po godini.\n");
			continue;
		}
		else if (check == 0 && actionOrSearch == 0) {
			printf("Unesi broj.\n");
			continue;
		}
		action = atoi(inputAction);

		return action;
	}
}

int clearMemory(Position head) {

	while (head->next != NULL) {
		Position p = head->next;
		head->next = p->next;
		free(p);
	}



	return 0;
}

int deleteElement(Position p) {
	char name[16], lastName[16];
	int year;

	if (p->next == NULL) {
		printf("Lista je prazna.\n");
		return 0;
	}

	Position q = p->next;


	printf("Unesi ime, prezime i godinu osobe koju zelis ukloniti: ");	scanf(" %s %s %d", name, lastName, &year);

	do {
		q = p->next;
		if (_strcmpi(name, q->firstName) == 0 && _strcmpi(lastName, q->lastName) == 0 && year == q->yearOfBirth) {
			p->next = q->next;
			printf("Izbrisana je osoba %s %s %d.\n", q->firstName, q->lastName, q->yearOfBirth);
			free(q);
			return 0;
		}

		p = p->next;
	} while (q->next != NULL);

	printf("Nije pronadena osoba %s %s %d.\n", name, lastName, year);


	return 0;
}

int addElementAfter(Position p) {
	char name[16], lastName[16];
	int year;
	int i = 0;
	int personFound = 0;
	Position q = NULL;
	if (p->next == NULL) {
		printf("Lista je prazna.\n");
		return 0;
	}

	printf("Unesi ime osobe iza koje zelis ubaciti novu osobu: ");
	scanf(" %s %s %d", name, lastName, &year);

	while (p != NULL && personFound == 0) {
		if (comparePersons(p, name, lastName, year) == 0) {
			p = p->next;
		}
		else {
			personFound = 1;
		}
	}

	if (personFound == 1) {
		q = createNode(q);
		if (q == NULL) {
			printf("Greska u alokaciji memorije.\n");
			return -1;
		}
		printf("Unesi ime osobe: ");	scanf(" %s %s %d", q->firstName, q->lastName, &q->yearOfBirth);
		q->next = p->next;
		p->next = q;
	}
	else {
		printf("%s %s %d nije pronaden u listi.\n", name, lastName, year);
	}



	return 0;
}

int comparePersons(Position p, char name[16], char lastName[16], int year) {
	if (_strcmpi(p->firstName, name) == 0 && _strcmpi(p->lastName, lastName) == 0 && p->yearOfBirth == year) {
		return 1;
	}
	return 0;
}

int addElementBefore(Position p) {
	char name[16], lastName[16];
	int year;
	int personFound = 0;

	if (p->next == NULL) {
		printf("Lista je prazna.\n");
		return 0;
	}

	printf("Unesi ime osobe ispred koje zelis ubaciti novu osobu: ");
	scanf(" %s %s %d", name, lastName, &year);

	while (p != NULL && personFound == 0) {
		if (comparePersons(p->next, name, lastName, year) == 0) {
			p = p->next;
		}
		else {
			personFound = 1;
		}
	}

	if (personFound == 1) {
		if (addStart(p) < 0) {
			return -1;
		}
	}
	else {
		printf("%s %s %d nije u listi.\n", name, lastName, year);
	}





	return 0;
}

int writeListInFile(Position p) {
	char filename[16];
	FILE* f = NULL;

	if (p->next == NULL) {
		printf("Lista je prazna.\n");
		return 0;
	}


	printf("Unesi ime datoteke u koju zelis zapisati listu: ");
	scanf(" %s", filename);

	f = fopen(filename, "w");
	if (f == NULL) {
		printf("Greska pri otvaranju filea.\n");
		return -1;
	}

	while (p->next != NULL) {
		p = p->next;
		fprintf(f, "%s %s %d\n", p->firstName, p->lastName, p->yearOfBirth);
	}

	printf("Lista je upisana u datoteku.\n");


	fclose(f);
	return 0;
}

int readListFromFile(Position p) {
	char filename[16];
	FILE* f = NULL;
	char name[16], lastName[16];
	int year;

	if (p->next != NULL) {
		printf("Lista mora biti prazna!\n");
		return 0;
	}

	printf("Unesi ime datoteke iz koje zelis ucitati listu: ");
	scanf(" %s", filename);

	f = fopen(filename, "r");
	if (f == NULL) {
		printf("Greska pri otvaranju filea.\n");
		return -1;
	}


	while (!feof(f)) {
		fscanf(f, " %s %s %d", name, lastName, &year);
		if (addSorted(p, name, lastName, year) < 0) {
			return -1;
		}
	}





	fclose(f);
	return 0;
}

int addSorted(Position p, char name[16], char lastName[16], int year) {
	Position q = NULL;
	q = createNode(q);
	if (q == NULL) {
		printf("Greska u alokaciji memorije.\n");
		return -1;
	}


	if (p->next == NULL) {
		strcpy(q->firstName, name);
		strcpy(q->lastName, lastName);
		q->yearOfBirth = year;
		q->next = p->next;
		p->next = q;
	}
	else {
		while (p->next != NULL && _strcmpi(p->next->lastName, lastName) < 0) {
			p = p->next;
		}
		strcpy(q->firstName, name);
		strcpy(q->lastName, lastName);
		q->yearOfBirth = year;
		q->next = p->next;
		p->next = q;
	}

	return 0;
}
