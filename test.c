#include "./includes/lemin.h"

static char	**lm_split(char *str)
{
	char	**tmp;
	int		i;

	if (!str)
		return (NULL);
	i = ft_wordcount(str, '\n');
	if (!(tmp = malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	i = 0;
	while (*str)
	{
		tmp[i] = str;
		if ((str = ft_strchr(str, '\n')))
			*str = '\0';
		if (*(str + 1) != '\0')
			str += 1;
		i++;
	}
	tmp[i] = NULL;
	return (tmp);
}

char		**lm_read()
{
	char	str[BUFF_SIZE + 1];
	char	*s1;
	char	*s2;
	int		ret;

	s1 = NULL;
	while ((ret = read(STDIN_FILENO, str, BUFF_SIZE)) > 0)
	{
		str[ret] = '\0';
		if (!s1)
		{
			if ((s1 = ft_strdup(str)) == NULL)
				return (NULL);
		}
		else
		{
			s2 = s1;
			s1 = ft_strjoin(s2, str);
			free(s2);
			if (s1 == NULL)
				return (NULL);
		}
	}
	return (lm_split(s1));
}

int main(int ac, char **av)
{
    // char **str;

    // str = lm_read();
    char	str[BUFF_SIZE + 1];
	char	*s1;
    int		ret;

	s1 = NULL;
    // printf("step_1\n");
	// ret = read(STDIN_FILENO, str, BUFF_SIZE);
	printf("%s\n", str);
	printf("ac = %d\n", ac);
	ret = 0;
	while (av[++ret])
		printf("%s\n", av[ret]);
    // if (STDIN_FILENO)
    // {
        // printf("SUCCESS\n");
	    // while ((ret = read(STDIN_FILENO, str, BUFF_SIZE)) > 0)
        //     printf("%s\n", str);
    // }
    printf("step_2\n");
    return (0);
}
