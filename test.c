#include "./includes/lemin.h"

int main(int ac, char **av)
{
    int i;
    int j;

    i = -1;
    j = 0;
    while (++i < 30)
    {
        printf("1 << %d %d\n", i, i << i);
    }
    
    if (j & 7)
        printf("j & 10 = %d\n", (j & 7));
    printf("j = %d\n", j);
    return (0);
}
