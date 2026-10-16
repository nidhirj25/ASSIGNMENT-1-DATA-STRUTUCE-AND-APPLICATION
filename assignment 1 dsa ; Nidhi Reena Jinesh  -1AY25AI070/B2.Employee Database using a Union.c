#include <stdio.h>
#include <stdlib.h>

enum EmployeeType {
    FULL_TIME = 0,
    CONTRACT = 1
};

struct Employee {
    int emp_id;
    char name[50];
    enum EmployeeType type;

    union {
        float salary;

        struct {
            float hourly_rate;
            int hours_worked;
        } contract_info;

    } pay;
};

float total_pay(struct Employee *e)
{
    if (e->type == FULL_TIME) {
        return e->pay.salary;
    } else {
        return e->pay.contract_info.hourly_rate *
               e->pay.contract_info.hours_worked;
    }
}

int main(void)
{
    int n, i, choice;
    float total_bill = 0.0f;

    struct Employee *emp;

    printf("Enter number of employees: ");

    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of employees.\n");
        return 1;
    }

    emp = (struct Employee *)malloc(
        n * sizeof(struct Employee));

    if (emp == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (i = 0; i < n; i++) {
        printf("\n--- Employee %d ---\n", i + 1);

        printf("Enter employee ID: ");
        if (scanf("%d", &emp[i].emp_id) != 1) {
            printf("Invalid employee ID.\n");
            free(emp);
            return 1;
        }

        printf("Enter employee name (one word): ");
        if (scanf("%49s", emp[i].name) != 1) {
            printf("Invalid employee name.\n");
            free(emp);
            return 1;
        }

        printf("Enter employee type (0 = Full-time, 1 = Contract): ");
        if (scanf("%d", &choice) != 1 ||
            (choice != 0 && choice != 1)) {
            printf("Invalid employee type.\n");
            free(emp);
            return 1;
        }

        emp[i].type = (enum EmployeeType)choice;

        if (emp[i].type == FULL_TIME) {
            printf("Enter monthly salary: ");

            if (scanf("%f", &emp[i].pay.salary) != 1 ||
                emp[i].pay.salary < 0) {
                printf("Invalid salary.\n");
                free(emp);
                return 1;
            }
        } else {
            printf("Enter hourly rate: ");

            if (scanf("%f",
                &emp[i].pay.contract_info.hourly_rate) != 1 ||
                emp[i].pay.contract_info.hourly_rate < 0) {
                printf("Invalid hourly rate.\n");
                free(emp);
                return 1;
            }

            printf("Enter hours worked: ");

            if (scanf("%d",
                &emp[i].pay.contract_info.hours_worked) != 1 ||
                emp[i].pay.contract_info.hours_worked < 0) {
                printf("Invalid hours worked.\n");
                free(emp);
                return 1;
            }
        }
    }

    printf("\n========== EMPLOYEE PAYSLIPS ==========\n");

    for (i = 0; i < n; i++) {
        float salary = total_pay(&emp[i]);

        printf("\nEmployee ID: %d\n", emp[i].emp_id);
        printf("Name: %s\n", emp[i].name);

        if (emp[i].type == FULL_TIME) {
            printf("Type: Full-time\n");
        } else {
            printf("Type: Contract\n");
        }

        printf("Total Pay: %.2f\n", salary);

        total_bill += salary;
    }

    printf("\nTotal salary bill: %.2f\n", total_bill);

    free(emp);

    printf("\nPress any key to exit...");
    getchar();
    getchar();

    return 0;
}
