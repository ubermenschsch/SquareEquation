#include "SquareEq.h"

void test(void)
{
    FILE * fp;
    fp = fopen("test.txt", "r");

    struct Coefficients coeff;
    struct Roots scan_roots;
    struct Roots roots;
    char end_of_file;

    while (end_of_file != EOF)
    {
        test_input(fp, &coeff, &scan_roots);

        roots.x1 = NAN;
        roots.x2 = NAN;
        solve_equation(coeff, &roots);

        test_assert(roots, scan_roots);

        end_of_file = getc(fp);
    }

    fclose(fp);
}

void test_input(FILE * fp, struct Coefficients * coeff, struct Roots * scan_roots)
{
    int num_scanned;
    scan_roots->x1 = NAN;
    scan_roots->x2 = NAN;

    num_scanned = fscanf(fp, "%lg %lg %lg %d", &coeff->a, &coeff->b, &coeff->c, &scan_roots->num_roots);
    assert(num_scanned == 4);
    if (scan_roots->num_roots == TWO_ROOTS)
    {
        num_scanned = fscanf(fp, "%lg %lg", &scan_roots->x1, &scan_roots->x2);
        assert(num_scanned == 2);
    }
    else if (scan_roots->num_roots == ONE_ROOT)
    {
        num_scanned = fscanf(fp, "%lg", &scan_roots->x1);
        assert(num_scanned == 1);
    }
}

void test_assert(const struct Roots roots, const struct Roots scan_roots)
{
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
}