#include <stdio.h>

typedef struct {
    int   degree;
    float coef[101];   
} polynomial;

float get_coef(polynomial p, int e) {
    if (e > p.degree || e < 0) return 0;
    return p.coef[p.degree - e];
}

polynomial add(polynomial a, polynomial b) {
    polynomial c;
    c.degree = (a.degree > b.degree) ? a.degree : b.degree;
    for (int e = c.degree; e >= 0; e--)
        c.coef[c.degree - e] = get_coef(a, e) + get_coef(b, e);
    return c;
}

void display(polynomial p) {
    int first = 1;
    for (int i = 0; i <= p.degree; i++) {
        float c = p.coef[i];
        int e = p.degree - i;
        if (c == 0) continue;

        if (first) {
            if (c < 0) printf("-");
        } else {
            printf(c < 0 ? " - " : " + ");
        }
        float mag = (c < 0) ? -c : c;

        if (e == 0)
            printf("%g", mag);
        else {
            if (mag != 1) printf("%g", mag);
            printf(e == 1 ? "x" : "x^%d", e);
        }
        first = 0;
    }
    if (first) printf("0"); 
    printf("\n");
}

void read_poly(polynomial *p, char name) {
    printf("Degree of %c(x): ", name);
    scanf("%d", &p->degree);
    printf("Enter %d coefficients from x^%d down to x^0 (include zeros): ",
           p->degree + 1, p->degree);
    for (int i = 0; i <= p->degree; i++)
        scanf("%f", &p->coef[i]);
}

int main() {
    polynomial a, b, c;
    read_poly(&a, 'A');
    read_poly(&b, 'B');

    printf("A(x) = "); display(a);
    printf("B(x) = "); display(b);

    c = add(a, b);
    printf("A(x) + B(x) = "); display(c);
    return 0;
}
