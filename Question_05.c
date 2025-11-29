#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>

#define INITIAL_CAPACITY 5
#define MAX_LINE_LENGTH 1000   

void insertLine(char ***lines, int *count, int *capacity, int index, const char *text);
void deleteLine(char ***lines, int *count, int index);
void printAllLines(char **lines, int count);
void shrinkToFit(char ***lines, int *capacity, int count);
void saveToFile(char **lines, int count, const char *filename);
void loadFromFile(char ***lines, int *count, int *capacity, const char *filename);
void freeAll(char ***lines, int count);

int main() 
{
    int capacity = INITIAL_CAPACITY;
    int count = 0;

    char **lines = (char **) malloc(capacity * sizeof(char*));
    if (!lines) {
        fprintf(stderr, "Memory allocation failed. Exiting.\n");
        exit(1);
    }

    int choice;
    char buffer[MAX_LINE_LENGTH];

    printf("Line-Based Text Editor\n");
    printf("______________________\n");

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert line\n");
        printf("2. Delete line\n");
        printf("3. Print all lines\n");
        printf("4. Shrink to fit\n");
        printf("5. Save to file\n");
        printf("6. Load from file\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();

        if (choice == 1) {
            int index;
            printf("Enter index to insert at (0 to %d): ", count);
            scanf("%d", &index);
            getchar();

            printf("Enter text: ");
            fgets(buffer, MAX_LINE_LENGTH, stdin);
            buffer[strcspn(buffer, "\n")] = '\0';

            insertLine(&lines, &count, &capacity, index, buffer);
        }
        else if (choice == 2) {
            int index;
            printf("Enter index to delete (0 to %d): ", count - 1);
            scanf("%d", &index);
            deleteLine(&lines, &count, index);
        }
        else if (choice == 3) {
            printAllLines(lines, count);
        }
        else if (choice == 4) {
            shrinkToFit(&lines, &capacity, count);
        }
        else if (choice == 5) {
            saveToFile(lines, count, "editor.txt");
        }
        else if (choice == 6) {
            loadFromFile(&lines, &count, &capacity, "editor.txt");
        }
        else if (choice == 7) {
            freeAll(&lines, count);
            printf("Exiting editor. All memory freed.\n");
            break;
        }
        else {
            printf("Invalid choice.\n");
        }
    }

    return 0;
}
void insertLine(char ***lines, int *count, int *capacity, int index, const char *text) 
{
    if (index < 0 || index > *count) {
        printf("Invalid index.\n");
        return;
    }
    if (*count == *capacity) {
        *capacity *= 2;
        *lines = realloc(*lines, (*capacity) * sizeof(char*));
        if (!(*lines)) {
            fprintf(stderr, "Realloc failed.\n");
            exit(1);
        }
    }
    memmove(&((*lines)[index + 1]), &((*lines)[index]),(*count - index) * sizeof(char*));

    (*lines)[index] = (char*) malloc(strlen(text) + 1);
    strcpy((*lines)[index], text);

    (*count)++;
}
void deleteLine(char ***lines, int *count, int index) 
{
    if (index < 0 || index >= *count) {
        printf("Invalid index.\n");
        return;
    }

    free((*lines)[index]);

    memmove(&((*lines)[index]), &((*lines)[index + 1]),
            ((*count - index - 1) * sizeof(char*)));

    (*count)--;
}
void printAllLines(char **lines, int count) 
{
	int i;
    printf("\n------- Stored Lines -------\n");
    for (i = 0; i < count; i++)
        printf("%d: %s\n", i, lines[i]);
    printf("----------------------------\n");
}
void shrinkToFit(char ***lines, int *capacity, int count) {
    *capacity = count;
    *lines = realloc(*lines, count * sizeof(char*));

    if (!(*lines) && count > 0) {
        fprintf(stderr, "Shrink realloc failed.\n");
        exit(1);
    }

    printf("Memory optimized. Capacity = %d\n", *capacity);
}
void saveToFile(char **lines, int count, const char *filename) 
{
	int i;
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("File open failed");
        return;
    }
    for (i = 0; i < count; i++)
        fprintf(fp, "%s\n", lines[i]);

    fclose(fp);
    printf("Successfully saved to %s\n", filename);
}
void loadFromFile(char ***lines, int *count, int *capacity, const char *filename) 
{
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("File open failed");
        return;
    }
    freeAll(lines, *count);

    *count = 0;
    *capacity = INITIAL_CAPACITY;
    *lines = malloc((*capacity) * sizeof(char*));

    char buffer[MAX_LINE_LENGTH];

    while (fgets(buffer, MAX_LINE_LENGTH, fp)) {
        buffer[strcspn(buffer, "\n")] = '\0';

        insertLine(lines, count, capacity, *count, buffer);
    }
    fclose(fp);
    printf("Loaded data from %s\n", filename);
}
void freeAll(char ***lines, int count) 
{
	int i;
    for (i = 0; i < count; i++)
        free((*lines)[i]);

    free(*lines);
}

