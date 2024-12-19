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
int append_student(student_lista*, student);
int remove_student(student_lista**, int);

/*
	Kody błędów dla funkcji "append_student":
	0. Pomyślnie dodano studenta do listy.
	1. Nie udało się zaalokować pamięci na nową komórkę listy.
	2. Lista nie została jeszcze zainicjowana.

*/
int print_student_list(student_lista*);

/*
	Kody błędów dla funkcji print_student_list():
	0. Wyświetlono studentów.
	1. Lista studentów nie została zainicjalizowana.
*/
void free_student_list(student_lista*);

int save_to_file(student_lista*);
int load_from_file(student_lista**);

int main() {
	setlocale(LC_CTYPE, "Polish");
	student_lista* head = 0;
	int choice = 1;
	do {
		printf("Witaj w interfejsie użytkownika!\n");
		if (head == 0) {
			printf("Brak studentów. Dodaj pierwszego studenta.\n");
		}
		printf("\n");
		printf("0. Wyjście\n\n");
		printf("1. Dodaj studenta. \n");
		printf("2. Wyświetl wszystkich studentów.\n");
		printf("3. Usuń studenta z listy.\n\n");

		printf("4. Zapisz do pliku. \n");
		printf("5. Wczytaj z pliku. \n");

		printf("\nTwój wybór: ");
		scanf_s("%d", &choice);
		getchar();
		system("CLS");
		printf("Output: \n\n");

		switch (choice) {
			case 0: break;
			case 1: {
				if (head == 0) {
					head = new_student_list(new_student());
					if (head == 0) {
						printf("Nie udało się utworzyć listy!\n");
					}
					else {
						printf("Udało się utworzyć listę!\n");
					}
				}
				else {
					int outcome = append_student(head, new_student());
					switch (outcome) {
						case 0: 
							printf("New student added successfully!\n");
							break;
						default: 
							printf("Failed to add new student.\n");
							break;
					}
				}
				break;
			}
			case 2: {
				if (head == 0) {
					printf("Brak studentów do wyświetlenia.\n");
					break;
				}
				
				print_student_list(head);
				break;

			}
			case 3: {
				int outcome, index;
				if (head == 0) {
					printf("Najpierw zainicjuj listę. \n");
					break;
				}

				do {
					printf("Wprowadź indeks studenta, którego chcesz usunąć (kolejność w liście -1): ");
					scanf_s("%d", &index);
					
					if (index < 0) {
						printf("Wprowadź prawidłowy indeks. ");
						continue;
					}
					break;
				} while (1);

				outcome = remove_student(&head, index);
				switch (outcome) {
					case 2:
						printf("Nie odnaleziono studenta o podanym indeksie. \n");
						break;
					case 0: 
						printf("Udało się usunąć studenta. \n");
						break;
					default: 
						printf("Coś poszło nie tak. Nie udało się usunąć studenta. \n");
						break;
				}
				break;
			}
			case 4: {
				int outcome;
				char response;
				printf("Uwaga! Zapisanie do pliku danych spowoduje ich nadpisanie. Czy chcesz zapisać dane? (t/n): ");
				response = getchar();
				getchar();
				if (response == 't' || response == 'T') {
					printf("Odpowiedź: tak. Zapisuję dane do pliku. \n");
				}
				else {
					printf("Odpowiedź: nie. \n");
				}

				if (head == 0) {
					printf("Najpierw zainicjuj listę! Dodaj pierwszego studenta!\n");
					break;
				}
				outcome = save_to_file(head);
				switch (outcome) {
					case 0: {
						printf("Udało się zapisać dane studentów do pliku!\n");
						break;
					}
					case 2: {
						printf("Nie udało sie otworzyć pliku \"students.bin\". \n");
						break;
					}
					default: {
						printf("Coś poszło nie tak przy zapisie. \n");
						break;
					}
				}
				break;
			}
			case 5: {
				int outcome;
				char response;
				printf("Uwaga! Wczytanie do pliku danych spowoduje nadpisanie listy. Czy chcesz wczytać dane? (t/n): ");
				response = getchar();
				getchar();
				if (response == 't' || response == 'T') {
					printf("Odpowiedź: tak. Wczytuję dane z pliku. \n");
				}
				else {
					printf("Odpowiedź: nie. \n");
					break;
				}

				outcome = load_from_file(&head);
				switch (outcome) {
					case 0:
						printf("Pomyślnie załadowano listę. Wyświetl ją, aby się przekonać :)\n");
						break;
					default: 
						printf("Nie udało się załadować listy :(\n");
						printf("Kod błędu: %d\n", outcome);
						break;
				}
			}
			default: {
				printf("Taka opcja nie istnieje.\n");
				break;
			}
		}
		printf("\n");
	} while (choice != 0);
	system("CLS");
	free_student_list(&head);
}

student new_student() {
	student nowy_stud;
	printf("Wprowadź imię studenta: ");
	scanf_s("%s", nowy_stud.name, imie_len);

	printf("Wprowadź nazwisko studenta: ");
	scanf_s("%s", nowy_stud.surname, nazw_len);

	printf("Wprowadź id studenta: ");
	scanf_s("%d", &nowy_stud.id);

	printf("Wprowadź grade studenta: ");
	scanf_s("%d", &nowy_stud.grade);

	return nowy_stud;
}

int append_student(student_lista* head, student another_student) {
	student_lista* new_next, *current;

	if (head == 0) {
		return 2;
	}
	new_next = (student_lista*)malloc(sizeof(student_lista));
	if (new_next == 0) {
		return 1;
	}
	new_next->data = another_student;
	new_next->next = NULL;
	current = head;
	while (current->next != NULL) {
		current = current->next;
	}
	current->next = new_next;
	return 0;
}

int remove_student(student_lista** head, int index) {
	student_lista* current = 0, *previous = 0;
	int i = 0;

	if (head == 0) {
		return 1;
	}

	current = *head;
	while (current->next != NULL && i != index) {
		previous = current;
		current = current->next;
		i++;
	}
	if (index != i) {
		return 2; // nie znaleziono studenta o podanym indeksie.
	}

	if (index == 0) {
		*head = 0;
	}

	if (previous != 0) {
		previous->next = current->next;
	}

	free(current);

	return 0;
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

int print_student_list(student_lista* list) {
	student_lista* current;
	int i = 0;

	if (list == NULL) {
		return 1;
	}

	current = list;
	printf("%-5s", "ID");
	printf("%-30s", "Name");
	printf("%-30s", "Surname");
	printf("%-5s", "Grade\n\n");
	while (current != NULL) {
		printf("%-5d", current->data.id);
		printf("%-30s", current->data.name);
		printf("%-30s", current->data.surname);
		printf("%-5d\n", current->data.grade);
		current = current->next;
		i++;
	}
	return 0;
}

void free_student_list(student_lista** list) {
	student_lista* current = *list, *next;
	while (current != NULL) {
		next = current->next;
		free(current);
		current = next;
	}
	*list = 0;
}

int save_to_file(student_lista* head) {
	FILE* file_ptr;
	student_lista* current;

	if (head == 0) {
		return 1;
	}

	fopen_s(&file_ptr, "students.bin", "wb");
	if (file_ptr == 0) {
		return 2;
	}
	current = head;
	while (current != NULL) {
		fwrite(&current->data, sizeof(student), 1, file_ptr);
		current = current->next;
	}


	fclose(file_ptr);
}


int load_from_file(student_lista** head_ptr) {
	FILE* file_ptr;
	student current_student;
	student_lista* current = 0, *new_next = 0;
	int size_in_bytes, amount, count;

	fopen_s(&file_ptr, "students.bin", "rb");
	if (file_ptr == 0) {
		return 1;
	}

	// Calculating size of file
	fseek(file_ptr, 0, SEEK_END);
	size_in_bytes = ftell(file_ptr);
	if (size_in_bytes < sizeof(student)) {
		return 2;
	}
	amount = size_in_bytes / sizeof(student);
	fseek(file_ptr, 0, SEEK_SET);

	// Deallocating data that's already there.
	if (*head_ptr != 0) {
		free_student_list(head_ptr);
	}

	// Reading data from file
	for (count = 0; count < amount; count++) {
		fread(&current_student, sizeof(student), 1, file_ptr);
		// Assuming that list is not initialised yet.
		if (count == 0) {
			current = new_student_list(current_student);
			if (current == 0) {
				return 3;
			}
			*head_ptr = current;
			continue;
		}

		// After list is initialised, this continues to place each
		// student inside the list.
		new_next = (student_lista*)malloc(sizeof(student_lista));
		if (new_next == 0) {
			free_student_list(head_ptr);
			return 4;
		}
		new_next->data = current_student;
		new_next->next = NULL;
		current->next = new_next;
		current = new_next;
	}


	fclose(file_ptr);
	return 0;
}
