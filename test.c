#include "./includes/lemin.h"

int main(int ac, char **av)
{
    int i;
    float a;
    float b;
    float f;
    a = 688/12;
    b = 277/12;
    f = a + b - 1;
    i = (int)f;
    printf("a = %f | b = %f | f = %f | i = %d\n", a, b, f, i);
    return (0);
}
