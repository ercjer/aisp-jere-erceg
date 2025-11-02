#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct polinom Polinom;
typedef Polinom* Position;


struct polinom {
	int koeficijent;
	int eksponent;
	Position next;
};

int readFromFile(Position, char[16]);
int addSorted(Position, int, int);
int sumTwoPoly(Position, Position, Position);
int addToList(Position, int, int);
int printPoly(Position);
int multiplyTwoPoly(Position, Position, Position);
int cleanList(Position);

int main() {
	Polinom first;
	first.next = NULL;
	Polinom second;
	second.next = NULL;
	Polinom result;
	result.next = NULL;
    char name1[16];
    char name2[16];
    int running = 1;
    int option = 0;
    //poli1.txt poli2.txt

    printf("Unesi ime prvog filea: ");
    scanf(" %s", name1);
    printf("Unesi ime drugog filea: ");
    scanf(" %s", name2);

    if (readFromFile(&first, name1) < 0) {
        return 0;
    }
    if (readFromFile(&second, name2) < 0) {
        return 0;
    }

        printf("Odaberi:\n1 - Zbrajanje polinoma.\n"
            "2 - Mnozenje polinoma.\n"
            "3 - Izlaz iz programa.\n\n");

    while (running) {
        scanf(" %d", &option);

        switch (option) {
        case 1:
            cleanList(&result);
            sumTwoPoly(&first, &second, &result);
            printPoly(&result);
            break;
        case 2:
            cleanList(&result);
            multiplyTwoPoly(&first, &second, &result);
            printPoly(&result);
            break;
        case 3:
            cleanList(&first);
            cleanList(&second);
            cleanList(&result);
            running = 0;
            break;
        }
    }


	return 0;
}

int readFromFile(Position p, char fileName[16]) {
    FILE* fp = NULL;
	Position q = NULL;
	int koeficijent = 0, eksponent = 0;


	fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("Greska pri otvaranju filea.\n");
		return -1;
	}

	while (!feof(fp)) {
		fscanf(fp, " %d %d", &koeficijent, &eksponent);
        if (addSorted(p, koeficijent, eksponent) < 0) {
            return -1;
        }
	}




	return 0;
}

int addSorted(Position p, int koeficijent, int eksponent) {
    Position q = NULL;

    if (p->next == NULL) {
        q = (Position)malloc(sizeof(Polinom));
        if (q == NULL) {
            printf("Greska pri alokaciji memorije.\n");
            return -1;
        }

        q->koeficijent = koeficijent;
        q->eksponent = eksponent;
        q->next = p->next;
        p->next = q;
        return 0;
    }

    while (p->next != NULL && p->next->eksponent > eksponent) {
        p = p->next;
    }

    if (p->next != NULL && p->next->eksponent == eksponent) {
        p->next->koeficijent += koeficijent;

        if (p->next->koeficijent == 0) {
            Position temp = p->next;
            p->next = temp->next;
            free(temp);
        }

        return 0;
    }

    q = (Position)malloc(sizeof(Polinom));
    if (q == NULL) {
        printf("Greska pri alokaciji memorije.\n");
        return -1;
    }

    q->koeficijent = koeficijent;
    q->eksponent = eksponent;
    q->next = p->next;
    p->next = q;

    return 0;

}

int sumTwoPoly(Position first, Position second, Position result) {

    first = first->next;
    second = second->next;
	
    while (first != NULL && second != NULL) {
        if (first->eksponent > second->eksponent) {
            if (addSorted(result, first->koeficijent, first->eksponent) < 0) {
                return -1;
            }
            first = first->next;
        }
        else if (second->eksponent > first->eksponent) {
            if (addSorted(result, second->koeficijent, second->eksponent) < 0) {
                return -1;
            }
            second = second->next;
        }
        else if (first->eksponent == second->eksponent) {
            if (first->koeficijent + second->koeficijent != 0) {
                if (addSorted(result, first->koeficijent + second->koeficijent, first->eksponent) < 0) {
                    return -1;
                }
            }
            first = first->next;
            second = second->next;
        }
    }

    while (first != NULL) {
        if (addSorted(result, first->koeficijent, first->eksponent) < 0) {
            return -1;
        }
        first = first->next;
    }
    while (second != NULL) {
        if (addSorted(result, second->koeficijent, second->eksponent) < 0) {
            return -1;
        }
        second = second->next;
    }

    if (result->next == NULL) {
        printf("Svi koeficijenti su se ponistili.\n");
    }


	return 0;
}

int printPoly(Position result) {

    result = result->next;

    while (result != NULL) {
        printf("%dx^%d ", result->koeficijent, result->eksponent);
        if (result->next != NULL) {
            if (result->next->koeficijent > 0) {
                printf("+ ");
            }
        }
        result = result->next;
    }



    return 0;
}

int multiplyTwoPoly(Position first, Position second, Position result) {
    Position temp = second->next;
    int newKoef = 0, newEks = 0;
    first = first->next;
    


    while (first != NULL) {
        while (temp != NULL) {
            newKoef = first->koeficijent * temp->koeficijent;
            newEks = first->eksponent + temp->eksponent;
            temp = temp->next;
            if (newKoef != 0) {
                if (addSorted(result, newKoef, newEks) < 0) {
                    return -1;
                }
            }
        }
        first = first->next;
        temp = second->next;
    }





    return 0;
}


int cleanList(Position head) {

    while (head->next != NULL) {
        Position p = head->next;
        head->next = p->next;
        free(p);
    }

    return 0;
}