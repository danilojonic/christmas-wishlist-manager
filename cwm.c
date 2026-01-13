#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 100
#define MAX_PEOPLE 1000

typedef struct Person {
    char name_and_surname[MAX_LEN + 1];
    char wish[MAX_LEN + 1];
} Person;

void clear_input_buffer();
int get_user_choice(const char* prompt, const char* option1, const char* option2);
void add_person(Person people[], int *index);
void search_person(Person people[], int index);
int case_insensitive_strcmp(const char *s1, const char *s2);
void display_wishlist(Person people[], int index);

int main() {
    Person people[MAX_PEOPLE];
    int index = 0;
    int running = 1;
    
    printf("=== Christmas Wishlist Manager ===\n");
    
    while (running) {
        printf("\nWhat would you like to do?\n");
        printf("1. Add a new person and their wish\n");
        printf("2. Search for a person's wish\n");
        printf("3. View all wishes\n");
        printf("4. Exit\n");
        printf("Enter choice (1-4): ");
        
        char choice_str[10];
        fgets(choice_str, sizeof(choice_str), stdin);
        choice_str[strcspn(choice_str, "\n")] = '\0';
        
        int choice = atoi(choice_str);
        
        switch (choice) {
            case 1:
                add_person(people, &index);
                break;
            case 2:
                search_person(people, index);
                break;
            case 3:
                display_wishlist(people, index);
                break;
            case 4:
                printf("Exiting program...\n");
                running = 0;
                break;
            default:
                printf("Invalid choice. Please enter 1, 2, 3, or 4.\n");
        }
    }
    
    return 0;
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int get_user_choice(const char* prompt, const char* option1, const char* option2) {
    char input[10];
    
    while (1) {
        printf("%s (%s/%s): ", prompt, option1, option2);
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        for (int i = 0; input[i]; i++) {
            input[i] = tolower((unsigned char)input[i]);
        }
        
        if (strcmp(input, option1) == 0) {
            return 1;
        } else if (strcmp(input, option2) == 0) {
            return 0;
        } else {
            printf("Please enter '%s' or '%s'.\n", option1, option2);
        }
    }
}

void add_person(Person people[], int *index) {
    if (*index >= MAX_PEOPLE) {
        printf("Maximum number of people reached (%d). Cannot add more.\n", MAX_PEOPLE);
        return;
    }
    
    printf("\n--- Adding New Person ---\n");
    
    while (1) {
        printf("Enter name and surname: ");
        fgets(people[*index].name_and_surname, MAX_LEN + 1, stdin);
        people[*index].name_and_surname[strcspn(people[*index].name_and_surname, "\n")] = '\0';
        
        if (strlen(people[*index].name_and_surname) > 0) {
            break;
        } else {
            printf("Name cannot be empty. Please try again.\n");
        }
    }

    while (1) {
        printf("Enter wish: ");
        fgets(people[*index].wish, MAX_LEN + 1, stdin);
        people[*index].wish[strcspn(people[*index].wish, "\n")] = '\0';
        
        if (strlen(people[*index].wish) > 0) {
            break;
        } else {
            printf("Wish cannot be empty. Please try again.\n");
        }
    }
    
    (*index)++;
    printf("Person added successfully!\n");

    if (*index < MAX_PEOPLE) {
        if (get_user_choice("Add another person?", "y", "n")) {
            add_person(people, index);
        }
    }
}

void search_person(Person people[], int index) {
    if (index == 0) {
        printf("No people in the wishlist yet. Please add some people first.\n");
        return;
    }
    
    printf("\n--- Search for Person ---\n");
    
    char search[MAX_LEN + 1];
    printf("Enter name to search for (or 'back' to return to main menu): ");
    fgets(search, sizeof(search), stdin);
    search[strcspn(search, "\n")] = '\0';
    
    if (strcmp(search, "back") == 0) {
        return;
    }
    
    int found = 0;
    printf("\nSearch results for '%s':\n", search);
    
    for (int i = 0; i < index; i++) {
        if (case_insensitive_strcmp(people[i].name_and_surname, search) == 0) {
            printf("- %s's wish: %s\n", people[i].name_and_surname, people[i].wish);
            found = 1;
        }
    }
    
    if (!found) {
        printf("No person found with that name.\n");
    }

    if (get_user_choice("Search for another person?", "y", "n")) {
        search_person(people, index);
    }
}

int case_insensitive_strcmp(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        if (tolower((unsigned char)*s1) != tolower((unsigned char)*s2)) {
            return (tolower((unsigned char)*s1) - tolower((unsigned char)*s2));
        }
        s1++;
        s2++;
    }
    return (tolower((unsigned char)*s1) - tolower((unsigned char)*s2));
}

void display_wishlist(Person people[], int index) {
    if (index == 0) {
        printf("No wishes in the list yet.\n");
        return;
    }
    
    printf("\n=== Complete Wishlist ===\n");
    for (int i = 0; i < index; i++) {
        printf("%d. %s: %s\n", i + 1, people[i].name_and_surname, people[i].wish);
    }
    printf("=========================\n");
    printf("Total: %d person(s)\n", index);
}
