//Structures in C
//Cole Krehnbrink

#include <stdio.h>
#include <string.h>
#include "structures.h"

void getOnePerson(person_t *ptr) {
	printf("Enter full name: ");
	scanf("%s", (*ptr).name);
	printf("Enter ssn: ");
	scanf("%s", (*ptr).ssn);
 	printf("Enter year of birth: ");
	scanf("%d", &(*ptr).yearOfBirth);
}

void printOnePerson(person_t p) {
	printf("%s:%s:%d\n", p.name, p.ssn, p.yearOfBirth);
}

void getPeople(person_t p[], int num) {
	for(int i = 0 ; i < num; i++) {
		getOnePerson(&p[i]);
	} 
}

void printPeople(person_t p[], int num) {
	for(int i = 0 ; i < num; i++) {
                printOnePerson(p[i]);
        }
}

