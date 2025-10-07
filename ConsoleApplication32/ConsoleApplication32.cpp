#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
	char name[16];
	char lastName[16];
	int score;
	float relative;
}; typedef struct student Student;

int getStudentCount();
int getStudentData(Student*, int);
void printStudentData(Student*, int);



int main() {
	int studentCount = 0;
	Student* students = NULL;

	studentCount = getStudentCount();
	if (studentCount < 0) {
		return -1;
	}
	printf("%d\n", studentCount);

	students = (Student*)malloc(studentCount * sizeof(Student));
	if (students == NULL) {
		printf("Greska pri alokacij memorije.\n");
		return -1;
	}

	if (getStudentData(students, studentCount) < 0) {
		return -1;
	}

	printStudentData(students, studentCount);




	free(students);
	return 0;
}

int getStudentCount() {
	int n = 0;
	FILE* fp = NULL;
	char buffer[512];

	fp = fopen("students.txt", "r");
	if (fp == NULL) {
		printf("Greska pri otvaranju filea.\n");
		return -1;
	}

	while (!feof(fp)) {
		fgets(buffer, 511, fp);
		n++;
	}

	fclose(fp);
	return n;
}

int getStudentData(Student* students, int studentCount) {
	FILE* fp = NULL;
	int maxScore = 0;

	fp = fopen("students.txt", "r");
	if (fp == NULL) {
		printf("Greska pri otvaranju datoteke.\n");
		return -1;
	}

	for (int i = 0; i < studentCount; i++) {
		fscanf(fp, " %s %s %d", students[i].name, students[i].lastName, &students[i].score);
		if (students[i].score > maxScore) {
			maxScore = students[i].score;
		}
	}

	for (int i = 0; i < studentCount; i++) {
		students[i].relative = students[i].score / (float)maxScore * 100;
	}



	fclose(fp);
	return 0;
}

void printStudentData(Student* students, int studentCount) {
	printf("Ime\tPrezime\tAps.\tRel.\n");
	for (int i = 0; i < studentCount; i++) {
		printf("%s\t%s\t%d\t%f\n", students[i].name, students[i].lastName, students[i].score, students[i].relative);
	}

	return;
}