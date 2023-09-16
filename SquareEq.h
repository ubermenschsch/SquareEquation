#ifndef SQUARE_EQ_H
#define SQUARE_EQ_H

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>

const double EPSILON = 1E-6;

enum NumRoots 
{
    NOT_EXIST      = -2,
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
    int num_roots = NOT_EXIST;
};

void solve_equation(const struct Coefficients * coeff, struct Roots * roots);
void solve_square(const struct Coefficients * coeff, struct Roots * roots);
void solve_lin(const struct Coefficients * coeff, struct Roots * roots);
void solve_without_variables(const struct Coefficients * coeff, struct Roots * roots);

int input_sq(struct Coefficients * coeff);
int output_sq(const struct Roots * roots);

void clear_input(void);
int is_zero(double x);
int is_clear_input();

void test(void);
int test_input(FILE * fp, struct Coefficients * coeff, struct Roots * scan_roots);
int test_is_equal(const struct Roots * roots, const struct Roots * scan_roots);

#endif // SQUARE_EQ_H
