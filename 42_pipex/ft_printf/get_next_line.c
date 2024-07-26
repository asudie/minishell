/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 10:41:21 by svalchuk          #+#    #+#             */
/*   Updated: 2024/05/07 21:51:19 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_read(int fd, int *i)
{
	char	*buff;
	int		rd;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buff == NULL)
		return (NULL);
	rd = read(fd, buff, BUFFER_SIZE);
	if (rd == -1)
	{
		free(buff);
		return (NULL);
	}
	else if (rd == 0)
		*i = 0;
	buff[rd] = '\0';
	return (buff);
}

static char	*ft_return(char **rem, int *i, char *pos)
{
	char	*line;
	char	*tmp;

	line = NULL;
	tmp = NULL;
	if (*rem && *i == 0)
		pos = ft_strchr_gnl(*rem, '\0');
	line = ft_substr_gnl(*rem, 0, pos - *rem + *i);
	if (line && *i == 1)
		tmp = ft_strjoin_gnl(pos + *i, "");
	free(*rem);
	*rem = tmp;
	return (line);
}

static char	*ft_check(char **rem, int fd, int *i)
{
	char	*line;
	char	*tmp;
	char	*pos;

	pos = NULL;
	if (*rem && *i == 1)
		pos = ft_strchr_gnl(*rem, '\n');
	if (pos == NULL && *i == 1)
	{
		line = ft_read(fd, i);
		if (line == NULL)
			return (NULL);
		tmp = ft_strjoin_gnl(*rem, line);
		if (tmp == NULL)
			return (NULL);
		free(*rem);
		free(line);
		*rem = tmp;
		line = ft_check(rem, fd, i);
	}
	else
		line = ft_return(rem, i, pos);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*rem;
	char		*line;
	int			i;

	i = 1;
	line = NULL;
	if (fd < 0)
		return (NULL);
	if (rem == NULL)
		rem = ft_read(fd, &i);
	if (rem)
		line = ft_check(&rem, fd, &i);
	if (line == NULL)
	{
		free(rem);
		rem = NULL;
	}
	return (line);
}
