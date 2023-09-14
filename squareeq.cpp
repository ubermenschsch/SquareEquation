// #define DEBUG 

#include <stdio.h>
#include <math.h>
// #include <assert.h>

const double EPSILON = 1E-6;

enum NumRoots 
{
    INFINITY_ROOTS = -1,
    NO_ROOTS       = 0, 
    ONE_ROOT       = 1, 
    TWO_ROOTS      = 2, 
    NON_EXIST      = -2,
};

struct Coefficients
{
    double a = NAN;
    double b = NAN;
    double c = NAN;
};

struct Roots
{
    double x1 = NAN;
    double x2 = NAN;
    NumRoots num_roots = NON_EXIST;
};

void solve_equation(const struct Coefficients coeff, struct Roots * roots);
void solve_square(const struct Coefficients coeff, struct Roots * roots);
void solve_lin(const struct Coefficients coeff, struct Roots * roots);
void solve_without_variables(const struct Coefficients coeff, struct Roots * roots);
void input_sq(struct Coefficients * coeff);
void output_sq(const struct Roots roots);
void clear_input(void);
int is_zero(double x);

int main()
{
    struct Coefficients coeff;
    input_sq(&coeff);

	struct Roots roots;

    // #ifdef DEBUG
    //     coeff.a = 0;
    //     coeff.b = 0;
    //     coeff.c = 0;
    //     solve_equation(coeff, &roots);
    //     assert(ONE_ROOT == roots.num_roots);
    // #endif

	solve_equation(coeff, &roots);

    output_sq(roots);

    return 0;
}

void input_sq(struct Coefficients * coeff)
{
    printf("This program solves ax^2+bx+c=0\n");
	printf("Enter a b c:\n");

    int entered_num = scanf("%lg %lg %lg", &coeff->a, &coeff->b, &coeff->c);
    int symbol = getchar();

    while ((entered_num < 3) || (symbol != '\n' && symbol != ' '))
    {
        printf("Uncorrect data were entered\nTry again:\n");

        clear_input();

        entered_num = scanf("%lg %lg %lg", &coeff->a, &coeff->b, &coeff->c);
        symbol = getchar();
    }
}

void solve_equation(const struct Coefficients coeff, struct Roots * roots)
{
    if (is_zero(coeff.a))
    {
        solve_lin(coeff, roots);
    }
    else
    {
        solve_square(coeff, roots);
    }
}

void solve_square(const struct Coefficients coeff, struct Roots * roots)
{
    double discr = coeff.b * coeff.b - 4 * coeff.a * coeff.c;

    if (discr < 0)
    {
        roots->num_roots = NO_ROOTS;
    }
    else if (discr == 0)
    {
        roots->x1 = -coeff.b / (2 * coeff.a);
        roots->num_roots = ONE_ROOT;
    }
    else
    {
        double sqrt_discr = sqrt(discr);
        roots->x1 = (-coeff.b + sqrt_discr) / (2 * coeff.a);
        roots->x2 = (-coeff.b - sqrt_discr) / (2 * coeff.a);
        roots->num_roots = TWO_ROOTS;
    }
}

void solve_lin(const struct Coefficients coeff, struct Roots * roots)
{
    if (is_zero(coeff.b))
    {
        solve_without_variables(coeff, roots);
    }
    else
    {
        roots->x1 = -coeff.c / coeff.b;
        roots->num_roots = ONE_ROOT;
    }
}

void solve_without_variables(const struct Coefficients coeff, struct Roots * roots)
{
    if (is_zero(coeff.c))
    {
        roots->num_roots = INFINITY_ROOTS;
    }
    else
    {
        roots->num_roots = NO_ROOTS;
    }    
}

void output_sq(const struct Roots roots)
{
    if (roots.num_roots == NO_ROOTS)
    {
        printf("No real solutions.\n");
    }
    else if (roots.num_roots == INFINITY_ROOTS)
    {
        printf("Solutions of this qudratic equation is set of real numbers.\n");
    }
    else
    {
        if (roots.num_roots == ONE_ROOT)
        {
            printf("Solution of this qudratic equation:\nx=%lg\n", roots.x1);
        }
        else if (roots.x1 > roots.x2)
        {
            printf("Solutions of this qudratic equation:\nx1=%lg\tx2=%lg\n", roots.x1, roots.x2);
        }
        else
        {
            printf("Solutions of this qudratic equation:\nx1=%lg\tx2=%lg\n", roots.x2, roots.x1);
        }
    }
}

void clear_input(void)
{
    while (getchar() != '\n')
    {
        continue;
    }
}

int is_zero(double x)
{
    return fabs(x) < EPSILON;
}


// enum, struct, assert, unit-test                                               