#include <stdio.h>
#include <stdlib.h>

struct Employee {
    int empId;
    char empName[50];
    float empSalary;
};

int main() {
    FILE *file;
    struct Employee employee;

    file = fopen("employee_data.dat", "rb+");

    if (file == NULL) {
        file = fopen("employee_data.dat", "wb+");
        if (file == NULL) {
            perror("Error opening file");
            exit(EXIT_FAILURE);
        }
    }

    int choice;

    do {
        printf("\nEmployee Record System\n");
        printf("1. Add Employee\n");
        printf("2. Display All Employees\n");
        printf("3. Search Employee\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Employee ID: ");
                scanf("%d", &employee.empId);

                fseek(file, (employee.empId - 1) * sizeof(struct Employee), SEEK_SET);
                fread(&employee, sizeof(struct Employee), 1, file);
                if (employee.empId != 0) {
                    printf("Employee with ID %d already exists.\n", employee.empId);
                } else {
                    printf("Enter Employee Name: ");
                    scanf("%s", employee.empName);
                    printf("Enter Employee Salary: ");
                    scanf("%f", &employee.empSalary);

                    fseek(file, (employee.empId - 1) * sizeof(struct Employee), SEEK_SET);
                    fwrite(&employee, sizeof(struct Employee), 1, file);
                    printf("Employee added successfully.\n");
                }
                break;

            case 2:
                rewind(file);
                printf("\nEmployee Details\n");
                while (fread(&employee, sizeof(struct Employee), 1, file) == 1) {
                    if (employee.empId != 0) {
                        printf("ID: %d, Name: %s, Salary: %.2f\n", employee.empId, employee.empName, employee.empSalary);
                    }
                }
                break;

            case 3:
                printf("Enter Employee ID to search: ");
                int searchId;
                scanf("%d", &searchId);

                fseek(file, (searchId - 1) * sizeof(struct Employee), SEEK_SET);
                fread(&employee, sizeof(struct Employee), 1, file);

                if (employee.empId == 0) {
                    printf("Employee with ID %d not found.\n", searchId);
                } else {
                    printf("Employee Found - ID: %d, Name: %s, Salary: %.2f\n", employee.empId, employee.empName, employee.empSalary);
                }
                break;

            case 4:
                break;

            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (choice != 4);

    fclose(file);

    return 0;
}
