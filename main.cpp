#include "SquareEq.h"
#define TEST
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 #define sqrt(x) (int)((short)sqrt(x))
int main()
{
    #ifdef TEST
        test();
    #endif
    
    int error = 0;

    struct Coefficients coeff;
    error = input_sq(&coeff);

	struct Roots roots;
	solve_equation(&coeff, &roots);

    error += output_sq(&roots);

    return error;
}                                          

// ifdef nahui, asserty naxyi, input \t, discr == 0, switch in output, test input kucha proverok na ifax;