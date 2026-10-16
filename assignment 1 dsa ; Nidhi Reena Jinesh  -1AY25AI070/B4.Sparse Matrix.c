#include <stdio.h>

#define MAX_TERMS 101
#define MAX_COLS  50

typedef struct { int row, col, value; } term;

void print_triples(term a[]) {
    printf("Row Col Value\n");
    for (int i = 0; i <= a[0].value; i++)
        printf("%3d %3d %5d\n", a[i].row, a[i].col, a[i].value);
}

void fast_transpose(term a[], term b[]) {
    int row_terms[MAX_COLS], starting_pos[MAX_COLS];
    int num_cols = a[0].col, num_terms = a[0].value;

    b[0].row = num_cols;
    b[0].col = a[0].row;
    b[0].value = num_terms;

    if (num_terms > 0) {
        for (int i = 0; i < num_cols; i++) row_terms[i] = 0;
        for (int i = 1; i <= num_terms; i++) row_terms[a[i].col]++;

        starting_pos[0] = 1;
        for (int i = 1; i < num_cols; i++)
            starting_pos[i] = starting_pos[i - 1] + row_terms[i - 1];

        printf("\nrow_terms[]    : ");
        for (int i = 0; i < num_cols; i++) printf("%d ", row_terms[i]);
        printf("\nstarting_pos[] : ");
        for (int i = 0; i < num_cols; i++) printf("%d ", starting_pos[i]);
        printf("\n");

        for (int i = 1; i <= num_terms; i++) {
            int j = starting_pos[a[i].col]++;
            b[j].row = a[i].col;
            b[j].col = a[i].row;
            b[j].value = a[i].value;
        }
    }
}

int main() {
    term a[MAX_TERMS], b[MAX_TERMS];
    int r, c, x, k = 1;

    printf("Enter rows and cols: ");
    scanf("%d %d", &r, &c);
    printf("Enter the matrix elements:\n");
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++) {
            scanf("%d", &x);
            if (x != 0) {
                a[k].row = i; a[k].col = j; a[k].value = x;
                k++;
            }
        }
    a[0].row = r; a[0].col = c; a[0].value = k - 1;

    printf("\nOriginal triples:\n");
    print_triples(a);

    fast_transpose(a, b);

    printf("\nTransposed triples:\n");
    print_triples(b);

    int ordered = 1;
    for (int i = 1; i < b[0].value; i++)
        if (b[i].row > b[i + 1].row ||
            (b[i].row == b[i + 1].row && b[i].col > b[i + 1].col))
            ordered = 0;
    printf("\nTransposed triples are %s in row-major order.\n",
           ordered ? "already" : "NOT");
    return 0;
}
