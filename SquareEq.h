#ifndef SQUARE_EQ_H
#define SQUARE_EQ_H

#include <stdio.h>
#include <math.h>
#include <assert.h>

const double EPSILON = 1E-6;

enum NumRoots 
{
    INFINITY_ROOTS = -1,
    NO_ROOTS       = 0, 
    ONE_ROOT       = 1, 
    TWO_ROOTS      = 2,
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
    int num_roots;
};

void solve_equation(const struct Coefficients coeff, struct Roots * roots);
void solve_square(const struct Coefficients coeff, struct Roots * roots);
void solve_lin(const struct Coefficients coeff, struct Roots * roots);
void solve_without_variables(const struct Coefficients coeff, struct Roots * roots);

void input_sq(struct Coefficients * coeff);
void output_sq(const struct Roots roots);

void clear_input(void);
int is_zero(double x);

void test(void);
void test_input(FILE * fp, struct Coefficients * coeff, struct Roots * scan_roots);
void test_assert(const struct Roots roots, const struct Roots scan_roots);

#endif // SQUARE_EQ_H
