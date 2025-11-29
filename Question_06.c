#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "members.txt"

typedef struct {
    int studentID;
    char fullName[100];
    char batch[20];           
    char membership[10];      
    char registrationDate[11];
    char dob[11];            
    char interest[10];      
} Student;

Student* students = NULL;  
int studentCount = 0;

void loadDatabaseText(const char *filename);
void saveDatabaseText(const char *filename);
int addStudent(Student s);
void updateStudent(int studentID);
void deleteStudent(int studentID);
void displayAll();
void batchReport(const char* batch);
int findStudentIndex(int studentID);

int main() {
    int choice;
    loadDatabaseText(FILENAME);

    while (1) {
        printf("\nMEMEBER REGISTRATION SYSTEM\n");
        printf("_____________________________\n");
        printf("\n1. Register new student\n");
        printf("2. Update student info\n");
        printf("3. Delete student registration\n");
        printf("4. View all registrations\n");
        printf("5. Generate batch-wise report\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); 

        if (choice == 1) {
            Student s;
            printf("\nEnter Student ID: ");
            scanf("%d", &s.studentID);
            getchar(); 

            if (findStudentIndex(s.studentID) != -1) {
                printf("\nError: Student ID already exists!\n");
                continue;
            }

            printf("\nEnter Full Name: ");
            fgets(s.fullName, sizeof(s.fullName), stdin);
            s.fullName[strcspn(s.fullName, "\n")] = '\0';

            printf("Enter Batch (CS/SE/Cyber Security/AI): ");
            fgets(s.batch, sizeof(s.batch), stdin);
            s.batch[strcspn(s.batch, "\n")] = '\0';

            printf("Enter Membership Type (IEEE/ACM): ");
            fgets(s.membership, sizeof(s.membership), stdin);
            s.membership[strcspn(s.membership, "\n")] = '\0';

            printf("Enter Registration Date (YYYY-MM-DD): ");
            fgets(s.registrationDate, sizeof(s.registrationDate), stdin);
            s.registrationDate[strcspn(s.registrationDate, "\n")] = '\0';

            printf("Enter Date of Birth (YYYY-MM-DD): ");
            fgets(s.dob, sizeof(s.dob), stdin);
            s.dob[strcspn(s.dob, "\n")] = '\0';

            printf("\nEnter Interest (IEEE/ACM/Both): ");
            fgets(s.interest, sizeof(s.interest), stdin);
            s.interest[strcspn(s.interest, "\n")] = '\0';

            if (addStudent(s))
                printf("\nStudent added successfully.\n");
            else
                printf("\nFailed to add student.\n");

        } else if (choice == 2) {
            int id;
            printf("\nEnter Student ID to update: ");
            scanf("%d", &id);
            getchar();
            updateStudent(id);

        } else if (choice == 3) {
            int id;
            printf("\nEnter Student ID to delete: ");
            scanf("%d", &id);
            getchar();
            deleteStudent(id);

        } else if (choice == 4) {
            displayAll();

        } else if (choice == 5) {
            char batch[20];
            printf("\nEnter Batch to generate report: ");
            fgets(batch, sizeof(batch), stdin);
            batch[strcspn(batch, "\n")] = '\0';
            batchReport(batch);

        } else if (choice == 6) {
            saveDatabaseText(FILENAME);
            free(students);
            printf("\nExiting program. Data saved to %s\n", FILENAME);
            break;
        } else {
            printf("\nInvalid choice!\n");
        }
    }

    return 0;
}
void loadDatabaseText(const char *filename) 
{
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("No existing database found, starting new.\n");
        return;
    }
    char line[512];
    while (fgets(line, sizeof(line), fp)) {
        Student s;
        line[strcspn(line, "\n")] = 0; 
        sscanf(line, "%d|%99[^|]|%19[^|]|%9[^|]|%10[^|]|%10[^|]|%9[^|]",
               &s.studentID,
               s.fullName,
               s.batch,
               s.membership,
               s.registrationDate,
               s.dob,
               s.interest);
        Student *tmp = (Student*)realloc(students, (studentCount + 1) * sizeof(Student));
        if (!tmp) { perror("Memory allocation failed"); exit(1); }
        students = tmp;
        students[studentCount++] = s;
    }

    fclose(fp);
    printf("Loaded %d student(s) from %s.\n", studentCount, filename);
}
void saveDatabaseText(const char *filename) {
	int i;
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("Cannot open file for writing");
        return;
    }

    for (i = 0; i < studentCount; i++) 
	{
        fprintf(fp, "%d|%s|%s|%s|%s|%s|%s\n",
                students[i].studentID,
                students[i].fullName,
                students[i].batch,
                students[i].membership,
                students[i].registrationDate,
                students[i].dob,
                students[i].interest);
    }
    fclose(fp);
    printf("Database saved to %s\n", filename);
}
int findStudentIndex(int studentID) {
	int i;
    for (i = 0; i < studentCount; i++)
        if (students[i].studentID == studentID) return i;
    return -1;
}
int addStudent(Student s) {
    Student *tmp = (Student*)realloc(students, (studentCount + 1) * sizeof(Student));
    if (!tmp) { perror("Memory allocation failed"); return 0; }
    students = tmp;
    students[studentCount++] = s;
    saveDatabaseText(FILENAME);
    return 1;
}
void updateStudent(int studentID) {
    int idx = findStudentIndex(studentID);
    if (idx == -1) {
        printf("Student ID not found.\n");
        return;
    }
    printf("Updating student %s (ID: %d)\n", students[idx].fullName, studentID);
    printf("Enter new Batch (current: %s): ", students[idx].batch);
    fgets(students[idx].batch, sizeof(students[idx].batch), stdin);
    students[idx].batch[strcspn(students[idx].batch, "\n")] = '\0';

    printf("Enter new Membership Type (current: %s): ", students[idx].membership);
    fgets(students[idx].membership, sizeof(students[idx].membership), stdin);
    students[idx].membership[strcspn(students[idx].membership, "\n")] = '\0';

    saveDatabaseText(FILENAME);
    printf("Student updated successfully.\n");
}
void deleteStudent(int studentID) {
    int i, idx = findStudentIndex(studentID);
    if (idx == -1) {
        printf("Student ID not found.\n");
        return;
    }
    for (i = idx; i < studentCount - 1; i++)
        students[i] = students[i + 1];

    studentCount--;
    students = (Student*)realloc(students, studentCount * sizeof(Student));
    saveDatabaseText(FILENAME);
    printf("Student deleted successfully.\n");
}
void displayAll() {
	int i;
    printf("\nAll Student Registrations\n");
    printf("_________________________\n");
    for (i = 0; i < studentCount; i++) {
        printf("\nID: %d | Name: %s | Batch: %s | Membership: %s | Reg: %s | DOB: %s | Interest: %s\n",
               students[i].studentID,
               students[i].fullName,
               students[i].batch,
               students[i].membership,
               students[i].registrationDate,
               students[i].dob,
               students[i].interest);
    }
    if (studentCount == 0) printf("No student records found.\n");
}
void batchReport(const char* batch) {
	int i;
    printf("\n--- Batch Report: %s ---\n", batch);
    int count = 0;
    for (i = 0; i < studentCount; i++) {
        if (strcmp(students[i].batch, batch) == 0) {
            printf("ID: %d | Name: %s | Membership: %s | Interest: %s\n",
                   students[i].studentID,
                   students[i].fullName,
                   students[i].membership,
                   students[i].interest);
            count++;
        }
    }
    if (count == 0) printf("No students found in this batch.\n");
}

