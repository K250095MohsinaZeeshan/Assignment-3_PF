#include <stdio.h>
#include <string.h>

struct Employee {
    int id;
    char name[50];
    char designation[50];
    float salary;
};
void displayEmployees(struct Employee emp[], int n) 
{
	int i;
    printf("\n-----------------------------------------------\n");
    printf("ID\tName\t\tDesignation\tSalary\n");
    printf("-----------------------------------------------\n");
    for (i = 0; i < n; i++) 
	{
        printf("%d\t%-10s\t%-12s\t%.2f\n",
               emp[i].id, emp[i].name, emp[i].designation, emp[i].salary);
    }
}
void findHighestSalary(struct Employee emp[], int n) 
{
    int i, index = 0;
    for (i = 1; i < n; i++) 
	{
        if (emp[i].salary > emp[index].salary)
            index = i;
    }
    printf("\nEmployee with Highest Salary:\n");
    printf("ID: %d\nName: %s\nDesignation: %s\nSalary: %.2f\n", emp[index].id, emp[index].name, emp[index].designation, emp[index].salary);
}
void searchEmployee(struct Employee emp[], int n) 
{
    int choice,i;
    printf("\nSearch Employee:\n1. By ID\n2. By Name\nEnter choice: ");
    scanf("%d", &choice);
    if (choice == 1) 
	{
        int id;
        printf("\nEnter Employee ID: ");
        scanf("%d", &id);

        for (i = 0; i < n; i++) 
		{
            if (emp[i].id == id) 
			{
                printf("\nEmployee Found:\n");
                printf("ID: %d\nName: %s\nDesignation: %s\nSalary: %.2f\n",
                      emp[i].id, emp[i].name, emp[i].designation, emp[i].salary);
                return;
            }
        }
        printf("\nEmployee with ID %d not found.\n", id);
    }
    else if (choice == 2) 
	{
        char name[50];
        printf("\nEnter Employee Name: ");
        scanf("%s", name);

        for (i = 0; i < n; i++)
		 {
            if (strcmp(emp[i].name, name) == 0) 
			{
                printf("\nEmployee Found:\n");
                printf("ID: %d\nName: %s\nDesignation: %s\nSalary: %.2f\n",
                      emp[i].id, emp[i].name, emp[i].designation, emp[i].salary);
                return;
            }
        }
        printf("Employee with name %s not found.\n", name);
    }
    else 
	{
        printf("Invalid choice.\n");
    }
}
void giveBonus(struct Employee emp[], int n, float threshold) 
{
	int i;
    for (i = 0; i < n; i++) 
	{
        if (emp[i].salary < threshold) 
		{
            emp[i].salary = emp[i].salary * 1.10; 
        }
    }
}
int main() 
{
    int n,i;
    printf("EMPLOYEE RECORDS SYSTEM\n");
    printf("_______________________\n");
    printf("\nEnter number of employees: ");
    scanf("%d", &n);

    struct Employee emp[n];
    for (i = 0; i < n; i++) 
	{
        printf("\nEnter details of Employee %d:\n", i + 1);

        printf("ID: ");
        scanf("%d", &emp[i].id);

        printf("Name: ");
        scanf("%s", emp[i].name);

        printf("Designation: ");
        scanf("%s", emp[i].designation);

        printf("Salary: ");
        scanf("%f", &emp[i].salary);
    }
    displayEmployees(emp, n);

    findHighestSalary(emp, n);

    searchEmployee(emp, n);
    
    printf("\nGiving 10%% bonus to employees with salary < 50000...\n");
    giveBonus(emp, n, 50000);

    printf("\nUpdated Employee Records:\n");
    displayEmployees(emp, n);

    return 0;
}

