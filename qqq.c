#include "./includes/lemin.h"

int main()
{
    int i = -1;
    int p[10];

    // p = malloc(sizeof(int) * 10);
    printf("sizeof = %lu\n", sizeof(p));
    ft_bzero(p, sizeof(p));
    i = -1;
    while (++i < 10)
        printf("p[%d] = %d\n", i, p[i]);
    return (0);
}