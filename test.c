#include <unistd.h>

int main(int ac, char **av)
{
    char str[1024];

    read(STDIN_FILENO, str, 1024);
    return (0);
}
