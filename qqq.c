#include "includes/lemin.h"

# define BUF 9999

int main(int ac, char *av[])
{
    int fd;
    int i;
    char line[BUFF_SIZE + 1];
    char *tmp;
    char *tmp2;
    char **str;

    fd = open(av[1], O_RDONLY);
    tmp = NULL;
    while ((i = read(fd, line, BUFF_SIZE)) > 0)
    {
        line[i] = '\0';
        if (!tmp)
            tmp = ft_strdup(line);
        else
            tmp = ft_strjoin(tmp, line);
    }
    str = malloc(sizeof(char *) * (ft_wordcount(tmp, '\n') + 1));
    i = 0;
    while (*tmp)
    {
        str[i++] = tmp;
        if ((tmp = ft_strchr(tmp, '\n')))
            *tmp = '\0';
        if (*(tmp + 1) != '\0')
            tmp += 1;
    }
    i = -1;
    while (str[++i])
        printf("str[%d] = %s\n", i, str[i]);
    return (0);
}