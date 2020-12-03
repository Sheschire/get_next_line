#include "get_next_line.h"

static int		ft_line(char **line, char **save, char *str)
{
	char	*tmp;

	if (str)
	{
		*line = ft_substr(*save, 0, str - *save);
		tmp = ft_substr(str, 1, ft_strlen(str));
		free(*save);
		*save = tmp;
		return (1);
	}
	if (*save)
	{
		*line = *save;
		*save = NULL;
	}
	else
		*line = ft_strdup("");
	return (0);
}

int	get_next_line(int fd, char **line)
{
	int			n_read;
	static char	buf[BUFFER_SIZE + 1];
	static char	*save;
	char		*tmp;
	char		*str;

	n_read = 1;
	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	while ((str = ft_strchr(save, '\n')) == 0 && ((n_read = read(fd, buf, BUFFER_SIZE)) > 0))
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
	if (n_read < 0)
		return (-1);
	return(ft_line(line, &save, str));
}
