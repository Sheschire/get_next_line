#include "get_next_line.h"

static int		ft_line(char **line, char **save)
{
	char 	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (save[i][j])
	{
		if (save[i][j] == '\n')
		{
			*line = ft_substr(*save, 0, j);		
			tmp = ft_substr(save[i], j + 1, ft_strlen(save[i] + j));
			free(*save);
			*save = tmp;
			return (1);
		}
		j++;
	}
	return (0);
}

int	get_next_line(int fd, char **line)
{
	int			n_read;
	static char	buf[BUFFER_SIZE + 1];
	static char	*save;
	char		*tmp;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	while (ft_strchr(save, '\n') == 0 && ((n_read = read(fd, buf, BUFFER_SIZE)) > 0))
	{
		buf[n_read] = '\0';
		if (save == NULL)
			tmp = ft_substr(buf, 0, ft_strlen(buf));
		else
			tmp = ft_strjoin(save, buf);
		if (save)
			free(save);
		save = tmp;
	}
	if (n_read > 0)
		return (ft_line(line, &save));
	if (n_read < 0)
		return (-1);
	if (n_read == 0 && save)
		*line = save;
	if (n_read == 0 && !save)
		*line = ft_strdup("");
	return (0);
}
/*
int main()
{
	int fd;
	char *line;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
		return (-1);
	while (get_next_line(fd, &line) > 0)
		printf("LINE = %s\n", line);
	if (get_next_line(fd, &line) == 0)
		printf("!!!! LAST LINE == %s\n", line);
	return (0);
}*/