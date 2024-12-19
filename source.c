#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#define imie_len 30
#define nazw_len 30

typedef struct Student{
	int id;
	char name[30];
	char surname[30];
	int grade;
} student;

typedef struct Student_Lista {
	student data;
	student* next;
} student_lista;

student new_student();
student_lista* new_student_list(student);
void print_student_list(student_lista*);
void free_student_list(student_lista*);

int main() {
	setlocale(LC_CTYPE, "Polish");
	student_lista* head = 0;
	int choice = 1;
	do {
		printf("Witaj w interfejsie u¿ytkownika!\n");
		if (head == 0) {
			printf("Brak studentów. Dodaj pierwszego studenta.\n");
		}
		printf("\n");
		printf("0. Wyjœcie\n\n");
		printf("1. Dodaj studenta. \n");
		printf("2. Wyœwietl wszystkich studentów.\n");

		printf("\nTwój wybór: ");
		scanf_s("%d", &choice);
		system("CLS");
		printf("Output: \n\n");

		switch (choice) {
			case 0: break;
			case 1:
				if (head == 0) {
					head = new_student_list(new_student());
					if (head == 0) {
						printf("Nie uda³o siê utworzyæ listy!\n");
					}
					else {
						printf("Uda³o siê utworzyæ listê!\n");
					}
				}
				break;
			case 2: 
				if (head == 0) {
					printf("Brak studentów do wyœwietlenia.\n");
					break;
				}
				
				print_student_list(head);
				break;
		}
		printf("\n");
	} while (choice != 0);
	free_student_list(head);
}

student new_student() {
	student nowy_stud;
	printf("WprowadŸ imiê studenta: ");
	scanf_s("%s", nowy_stud.name, imie_len);

	printf("WprowadŸ nazwisko studenta: ");
	scanf_s("%s", nowy_stud.surname, nazw_len);

	printf("WprowadŸ id studenta: ");
	scanf_s("%d", &nowy_stud.id);

	printf("WprowadŸ grade studenta: ");
	scanf_s("%d", &nowy_stud.grade);

	return nowy_stud;
}

student_lista* new_student_list(student first_student) {
	student_lista* head = (student_lista*)malloc(sizeof(student_lista));
	if (head == 0) {
		return 0;
	}
	head->data = first_student;
	head->next = NULL;
	return head;
}

void print_student_list(student_lista* list) {
	student_lista* current = list;
	int i = 0;
	while (current != NULL) {
		printf("Student %d: \n", i);
		printf("Fullname: %s %s\n",list->data.name, list->data.surname);
		printf("Id: %d\n", list->data.id);
		printf("Grade: %d\n", list->data.grade);
		current = current->next;
		i++;
	}
}

void free_student_list(student_lista* list) {
	student_lista* current = list, *next;
	while (current != NULL) {
		next = current->next;
		free(current);
		current = next;
	}
}
