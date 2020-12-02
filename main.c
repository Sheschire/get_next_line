#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdio.h>

int	main(int ac, char **av)
{
	int		fd;
	char	*line;
	int		ret;

	if (ac == 1)
		return (EXIT_FAILURE);
	line = NULL;
	fd = open(av[1], O_RDONLY);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		printf("line : |%s| ret : %d\n", line, ret);
		free(line);
		line = NULL;
	}
	printf("line : |%s| ret : %d\n", line, ret);
	free(line);
	close(fd);
    //system("leaks a.out");
	return (EXIT_SUCCESS);
}

/*
int main(void)
{
    int fd;
	int u;
	int i = 1;
    char *line;

    fd = open("fichier.txt", O_RDONLY);

    while((u = get_next_line(fd, &line)) != 0)
	{
		if (u == -1)
			return (-1);
		printf("\033[31m[LIGNE %d GNL=%d] : %s\n\033[0m",i,u, line);
		free(line);
		i++;
	}
    u = get_next_line(fd, &line);
	free(line);
    printf("\033[31m[LIGNE %d GNL=%d] : %s\n\033[0m\n\n>>>         TOTAL LIGNES : %d\n\n",i,u, line, i);
    system("leaks a.out");
	return(0);
}
*/