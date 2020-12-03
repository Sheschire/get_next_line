#include "get_next_line.h"

static int		ft_line(int fd, char **line, char *save[fd], char *str)
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
	static char	*save[256];
	int			n_read;
	char		buf[BUFFER_SIZE + 1];
	char		*tmp;
	char		*str;

	n_read = 1;
	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	while ((str = ft_strchr(save[fd], '\n')) == 0 && ((n_read = read(fd, buf, BUFFER_SIZE)) > 0))
	{
		buf[n_read] = '\0';
		if (save[fd] == NULL)
			tmp = ft_substr(buf, 0, BUFFER_SIZE);
		else
			tmp = ft_strjoin(save[fd], buf);
		if (save[fd])
			free(save[fd]);
		save[fd] = tmp;
	}
	if (n_read < 0)
		return (-1);
	return(ft_line(fd, line, &save[fd], str));
}
