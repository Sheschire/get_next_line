#include "get_next_line.h"

static int		ft_line(char **line, char **save)
{
	char 	*tmp;
	int		j;

	j = 0;
	tmp = NULL;
	while (save[0][j] && save[0][j] != '\n')
		j++;
	if (!save[0][j])
	{
		free(save);
		return (0);
	}
	else
	{
		*line = ft_substr(save[0], 0, j);
		if (save[0][j + 1])
			tmp = ft_substr(save[0], j + 1, ft_strlen(save[0] + j));
		else
			tmp = "";
		free(*save);
		*save = tmp;
		return (1);
	}
}

int	get_next_line(int fd, char **line)
{
	int			n_read;
	static char	buf[BUFFER_SIZE + 1];
	static char	*save;
	char		*tmp;

	n_read = 1;
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
