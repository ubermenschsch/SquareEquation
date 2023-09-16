#include "SquareEq.h"

void test(void)
{
    int error = 0;

    FILE * fp = nullptr;
    fp = fopen("test.txt", "r");

    assert(fp != nullptr);

    struct Coefficients coeff;
    struct Roots scan_roots;
    struct Roots roots;

    char end_of_file;
    while (end_of_file != EOF)
    {
        error += test_input(fp, &coeff, &scan_roots);

        roots.x1 = NAN;
        roots.x2 = NAN;
        solve_equation(&coeff, &roots);

        error += test_is_equal(&roots, &scan_roots);

        end_of_file = getc(fp);
    }

    fclose(fp);

    if (error == 0)
    {
        printf("ALL TESTS SUCSEED\n");
    }
    else
    {
        printf("TEST NOT SUCSEED\n");
    }
}

int test_input(FILE * fp, struct Coefficients * coeff, struct Roots * scan_roots)
{
    assert(coeff != nullptr);
    assert(scan_roots != nullptr);

    scan_roots->x1 = NAN;
    scan_roots->x2 = NAN;

    int num_scanned = fscanf(fp, "%lg %lg %lg %d", &coeff->a, &coeff->b, &coeff->c, &scan_roots->num_roots);
    if (num_scanned != 4)
    {
        printf("Fail of scan test numbers");
        return -1;
    }
    if (isnan(coeff->a) || isnan(coeff->b) || isnan(coeff->c))
    {
        printf("Fail of scan coefficients");
        return -1;
    }

    if (scan_roots->num_roots == TWO_ROOTS)
    {
        num_scanned = fscanf(fp, "%lg %lg", &scan_roots->x1, &scan_roots->x2);
        if (num_scanned != 2)
        {
            printf("Fail of scan test numbers");
            return -1;
        }
    }
    else if (scan_roots->num_roots == ONE_ROOT)
    {
        num_scanned = fscanf(fp, "%lg", &scan_roots->x1);
        if (num_scanned != 1)
        {
            printf("Fail of scan test numbers");
            return -1;
        }
    }

    return 0;
}

int test_is_equal(const struct Roots * roots, const struct Roots * scan_roots)
{
    assert(roots != nullptr);
    assert(scan_roots != nullptr);

    if (roots->num_roots != scan_roots->num_roots)
    {
        printf("Nonequal number of roots");
        return -1;
    }

    if (!(isnan(roots->x1)) && !(isnan(scan_roots->x1)))
    {
        if (!(is_zero(roots->x1 - scan_roots->x1)))
        {
            printf("Nonequal first roots");
            return -1;
        }
    }
    else if(isnan(roots->x1) && isnan(scan_roots->x1))
    {
        ;
    }
    else if (isnan(roots->x1) && !(isnan(scan_roots->x1)) || !(isnan(roots->x1)) && isnan(scan_roots->x1))
    {
        printf("Nonequal first roots(NAN and not NAN)");
        return -1;
    }

    if (!(isnan(roots->x2)) && !(isnan(scan_roots->x2)))
    {
        if (!(is_zero(roots->x2 - scan_roots->x2)))
        {
            printf("Nonequal second roots");
            return -1;
        }
    }
    else if(isnan(roots->x2) && isnan(scan_roots->x2))
    {
        ;
    }
    else if (isnan(roots->x2) && !(isnan(scan_roots->x2)) || !(isnan(roots->x2)) && isnan(scan_roots->x2))
    {
        printf("Nonequal second roots(NAN and not NAN)");
        return -1;
    }

    return 0;
}