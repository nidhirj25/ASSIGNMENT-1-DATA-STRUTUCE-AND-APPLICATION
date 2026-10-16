#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int   roll_no;
    char  name[20];
    float marks;
} Student;

void report(Student *ptr, int n, int updated) {
    float sum = 0;
    Student *top = ptr;
    for (int i = 0; i < n; i++) {
        sum += (ptr + i)->marks;
        if ((ptr + i)->marks > top->marks)
            top = ptr + i;
    }
    printf(updated ? "Updated average marks: %.2f\n" : "\nAverage marks: %.2f\n", sum / n);
    printf("Topper: %s (Roll %d, Marks %.2f)\n", top->name, top->roll_no, top->marks);
}

int main() {
    int n;
    char choice;

    printf("Enter number of students: ");
    scanf("%d", &n);

    Student *ptr = (Student *)malloc(n * sizeof(Student));
    if (ptr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("Enter roll, name, marks: ");
        scanf("%d %19s %f", &(ptr + i)->roll_no, (ptr + i)->name, &(ptr + i)->marks);
    }
    report(ptr, n, 0);

    printf("\nAdd 2 more students? (y/n): ");
    scanf(" %c", &choice);
    if (choice == 'y' || choice == 'Y') {
        Student *temp = (Student *)realloc(ptr, (n + 2) * sizeof(Student));
        if (temp == NULL) {
            printf("realloc failed, old data kept\n");
            free(ptr);
            return 1;
        }
        ptr = temp;
        for (int i = n; i < n + 2; i++) {
            printf("Enter roll, name, marks: ");
            scanf("%d %19s %f", &(ptr + i)->roll_no, (ptr + i)->name, &(ptr + i)->marks);
        }
        n += 2;
        report(ptr, n, 1);
    }

    free(ptr);
    return 0;
}
