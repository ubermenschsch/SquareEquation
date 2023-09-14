#include "SquareEq.h"

int main()
{
    struct Coefficients coeff;
    input_sq(&coeff);

	struct Roots roots;
	solve_equation(coeff, &roots);

    output_sq(roots);
}



// enum, struct, assert, unit-test, -0                                               