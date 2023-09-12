#include <stdio.h>
#include <math.h>

const double EPSILON = 1E-6;

void solve_eq(const double a, const double b, const double c, double *px1, double *px2);
void solve_sq(const double a, const double b, const double c, double *px1, double *px2);
void solve_lin(const double b, const double c, double *px1);
void solve_without_variables(const double c, double *px1);
void input_sq(double *pa, double *pb, double *pc);
void output_sq(const double x1, const double x2);

int main()
{
    double a = NAN, b = NAN, c = NAN;
    input_sq(&a, &b, &c);

	double x1 = NAN, x2 = NAN;
	solve_eq(a, b, c, &x1, &x2);

    output_sq(x1, x2);

    return 0;
}

void input_sq(double *pa, double *pb, double *pc)
{
    printf("This program solves ax^2+bx+c=0\n");
	printf("Enter a b c:\n");

    int entered_num = scanf("%lg %lg %lg", pa, pb, pc);
    int symbol = getchar();

    while ((entered_num < 3) || (symbol != '\n'))
    {
        printf("Uncorrect data were entered\nTry again:\n");

        while (getchar() != '\n')
        {
            continue;
        }

        entered_num = scanf("%lg %lg %lg", pa, pb, pc);
        symbol = getchar();
    }
}

void solve_eq(const double a, const double b, const double c, double *px1, double *px2)
{
    if (fabs(a) < EPSILON)
    {
        solve_lin(b, c, px1);
        *px2 = *px1;
    }
    else
    {
        solve_sq(a, b, c, px1, px2);
    }
}

void solve_sq(const double a, const double b, const double c, double *px1, double *px2)
{
    double discr = b*b - 4*a*c;

    if (discr < 0)
    {
        *px1 = *px2 = NAN;                                                                  // have not equation
    }
    else
    {
        double sqrt_discr = sqrt(discr);
        *px1=(-b + sqrt_discr) / (2*a);
        *px2=(-b - sqrt_discr) / (2*a);
    }
}

void solve_lin(const double b, const double c, double *px1)
{
    if (fabs(b) < EPSILON)
    {
        solve_without_variables(c, px1);
    }
    else
    {
        *px1 = -1 * c / b;
    }
}

void solve_without_variables(const double c, double *px1)
{
    if (fabs(c) < EPSILON)
    {
        *px1 = INFINITY;                                                                    // any equation
    }
    else
    {
        *px1 = NAN;                                                                         // have not equation
    }    
}

void output_sq(const double x1, const double x2)
{
    if (isnan(x1) == 1)
    {
        printf("No real solutions.\n");
    }
    else if (isfinite(x1) == 0)
    {
        printf("Solutions of this qudratic equation is set of real numbers.\n");
    }
    else
    {
        if (fabs(x1 - x2) < EPSILON)
        {
            printf("Solution of this qudratic equation:\nx=%lg\n", x1);
        }
        else if (x1 > x2)
        {
            printf("Solutions of this qudratic equation:\nx1=%lg\tx2=%lg\n", x1, x2);
        }
        else
        {
            printf("Solutions of this qudratic equation:\nx1=%lg\tx2=%lg", x2, x1);
        }
    }
}
// enum, struct, assert, unit-test                                               