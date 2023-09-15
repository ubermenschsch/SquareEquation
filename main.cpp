#include "SquareEq.h"
#define DEBUG
#define TEST

int main()
{
    #ifdef TEST
        test();
    #endif

    struct Coefficients coeff;
    input_sq(&coeff);
    #ifdef DEBUG
        assert(!isnan(coeff.a));
        assert(!isnan(coeff.b));
        assert(!isnan(coeff.c));
    #endif 

	struct Roots roots;
	solve_equation(coeff, &roots);

    output_sq(roots);
}



// enum, struct, assert, unit-test, -0                                               