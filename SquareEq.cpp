#include "SquareEq.h"
#define DEBUG

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
        // printf("%lg\n", roots->x2);
        solve_lin(coeff, roots);
        #ifdef DEBUG
            assert(roots->num_roots != TWO_ROOTS);
            // printf("%lg\n", roots->x2);
            assert(isnan(roots->x2));
            assert(isnan(roots->x1) || roots->num_roots == ONE_ROOT);
            assert(!isnan(roots->x1) || roots->num_roots == INFINITY_ROOTS || roots->num_roots == NO_ROOTS);
        #endif
    }
    else
    {
        solve_square(coeff, roots);
        #ifdef DEBUG
            assert(roots->num_roots != INFINITY_ROOTS);
            assert((!isnan(roots->x2)) || (roots->num_roots != TWO_ROOTS));
            assert((!isnan(roots->x1)) || (roots->num_roots == NO_ROOTS));
        #endif
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
    else if (roots.num_roots == ONE_ROOT || is_zero(roots.x1 - roots.x2))
    {
        if (is_zero(roots.x1))
            printf("Solution of this qudratic equation:\nx=0\n");
        else
            printf("Solution of this qudratic equation:\nx=%lg\n", roots.x1);
    }
    else if (roots.x1 > roots.x2)
    {
        printf("Solutions of this qudratic equation:\nx1=%lg\tx2=%lg\n", roots.x1, roots.x2);
    }
    // else if (roots.x1 < roots.x2)
    // {
    //     printf("Solutions of this qudratic equation:\nx1=%lg\tx2=%lg\n", roots.x2, roots.x1);
    // }
    #ifdef DEBUG
        else
        {
            assert(0);
        }
    #endif
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

void test(void)
{
    FILE * fp;
    fp = fopen("test.txt", "r");

    struct Coefficients coeff;
    struct Roots scan_roots;
    struct Roots roots;
    int num_scanned;
    char end_of_file;

    // printf("%lg\n", roots.x2);
    while (end_of_file != EOF)
    {
        roots.x1 = NAN;
        roots.x2 = NAN;
        scan_roots.x1 = NAN;
        scan_roots.x2 = NAN;

        num_scanned = fscanf(fp, "%lg %lg %lg %d", &coeff.a, &coeff.b, &coeff.c, &scan_roots.num_roots);
        // printf("<%d> %lg %lg %lg %d\n", num_scanned, coeff.a, coeff.b, coeff.c, scan_roots.num_roots);
        assert(num_scanned == 4);
        if (scan_roots.num_roots == TWO_ROOTS)
        {
            num_scanned = fscanf(fp, "%lg %lg", &scan_roots.x1, &scan_roots.x2);
            // printf("%lg %lg\n", scan_roots.x1, scan_roots.x2);
            assert(num_scanned == 2);
        }
        else if (scan_roots.num_roots == ONE_ROOT)
        {
            num_scanned = fscanf(fp, "%lg", &scan_roots.x1);
            // printf("%lg\n", scan_roots.x1);
            assert(num_scanned == 1);
        }

        solve_equation(coeff, &roots);

        assert(roots.num_roots == scan_roots.num_roots);
        if (!isnan(roots.x1) && !isnan(scan_roots.x1))
            assert(is_zero(roots.x1 - scan_roots.x1));
        else if (isnan(roots.x1) && isnan(scan_roots.x1))
            ;
        else
            assert(0);
        if (!isnan(roots.x2) && !isnan(scan_roots.x2))
            assert(is_zero(roots.x2 - scan_roots.x2));
        else if (isnan(roots.x2) && isnan(scan_roots.x2))
            ;
        else
            assert(0);

        end_of_file = getc(fp);
    }

    fclose(fp);
}