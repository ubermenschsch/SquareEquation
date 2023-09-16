#include "SquareEq.h"

int input_sq(struct Coefficients * coeff)
{
    assert(coeff != nullptr);

    printf("This program solves ax^2+bx+c=0\n"
	       "Enter a b c:\n");

    int entered_num = scanf("%lg %lg %lg", &coeff->a, &coeff->b, &coeff->c);

    int execc_symbol = is_clear_input();

    while ((entered_num < 3) || execc_symbol)
    {
        printf("Uncorrect data were entered\nTry again:\n");

        entered_num = scanf("%lg %lg %lg", &coeff->a, &coeff->b, &coeff->c);

        execc_symbol = is_clear_input();
    }

    
    if (isnan(coeff->a) || isnan(coeff->b) || isnan(coeff->c))
    {
        printf("Programmer's error in input function");
        return -1;
    }

    return 0;
}

void solve_equation(const struct Coefficients * coeff, struct Roots * roots)
{
    assert(roots != nullptr);
    assert(coeff != nullptr);

    if (is_zero(coeff->a))
    {
        solve_lin(coeff, roots);
    }
    else
    {
        solve_square(coeff, roots);
    }
}

void solve_square(const struct Coefficients * coeff, struct Roots * roots)
{
    double discr = coeff->b * coeff->b - 4 * coeff->a * coeff->c;

    if (is_zero(discr))
    {
        roots->x1 = -coeff->b / (2 * coeff->a);
        roots->num_roots = ONE_ROOT;
    }
    else if (discr < 0)
    {
        roots->num_roots = NO_ROOTS;
    }
    else
    {
        double sqrt_discr = sqrt(discr);
        roots->x1 = (-coeff->b + sqrt_discr) / (2 * coeff->a);
        roots->x2 = (-coeff->b - sqrt_discr) / (2 * coeff->a);
        roots->num_roots = TWO_ROOTS;
    }
}

void solve_lin(const struct Coefficients * coeff, struct Roots * roots)
{
    if (is_zero(coeff->b))
    {
        solve_without_variables(coeff, roots);
    }
    else
    {
        roots->x1 = -coeff->c / coeff->b;
        roots->num_roots = ONE_ROOT;
    }
}

void solve_without_variables(const struct Coefficients * coeff, struct Roots * roots)
{
    if (is_zero(coeff->c))
    {
        roots->num_roots = INFINITY_ROOTS;
    }
    else
    {
        roots->num_roots = NO_ROOTS;
    }    
}

int output_sq(const struct Roots * roots)
{
    assert(roots != nullptr);

    switch (roots->num_roots)
    {
    case NO_ROOTS:
    {
        printf("No real solutions.\n");
        break;
    }
    case INFINITY_ROOTS:
    {
        printf("Solutions of this qudratic equation is set of real numbers.\n");
        break;
    }
    case ONE_ROOT:
    {
        if (is_zero(roots->x1))
        {
            printf("Solution of this qudratic equation:\nx=0\n");
        }
        else
        {
            printf("Solution of this qudratic equation:\nx=%lg\n", roots->x1);
        }
        break;
    }
    case TWO_ROOTS:
    {
        if (is_zero(roots->x1 - roots->x2))
        {
            printf("Solution of this qudratic equation:\nx=%lg\n", roots->x1);
        }
        else
        {
            printf("Solutions of this qudratic equation:\nx1=%lg\tx2=%lg\n", roots->x1, roots->x2);
        }
        break;
    }
    default:
    {
        printf("Programmer's error in output function");
        return -1;
    }
    }

    return 0;
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

int is_clear_input()
{
    int execc_symbol = 0;

    char symbol = getchar();
    while (symbol != '\n')
    {
        if (isgraph(symbol))
            execc_symbol = 1;
        symbol = getchar();
    }
    
    return execc_symbol;
}