/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odomenic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 14:04:03 by odomenic          #+#    #+#             */
/*   Updated: 2020/12/06 17:58:42 by odomenic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>

int		ft_get_line(char **reminder, char **line)
{
	char	*c;
	char	*s;

	if ((c = ft_strchr(*reminder, '\n')))
	{
		*c = '\0';
		if (!(s = ft_strdup(*reminder)))
			return (-1);
		if (!(c = ft_strdup(++c)))
			return (-1);
		free(*reminder);
		*reminder = NULL;
		if (!(*line = ft_strdup(s)))
			return (-1);
		if (!(*reminder = ft_strdup(c)))
			return (-1);
		free(c);
		free(s);
		s = NULL;
		return (1);
	}
	return (0);
}

int		ft_end_of_line(int size, char **buff, char **reminder, char **line)
{
	char	*str;

	if ((size == 0) && (!(ft_strchr(*reminder, '\n'))))
	{
		if (!(*line = ft_strdup(*reminder)))
			return (-1);
		free(*reminder);
		*reminder = NULL;
		free(*buff);
		*buff = NULL;
		return (0);
	}
	if (!(str = ft_strdup(*reminder)))
		return (-1);
	free(*reminder);
	*reminder = NULL;
	if (!(*reminder = ft_strjoin(str, *buff)))
		return (-1);
	free(str);
	str = NULL;
	free(*buff);
	*buff = NULL;
	return (1);
}

int		get_next_line(int fd, char **line)
{
	char		*buff;
	int			size;
	static char *reminder;
	int			state;

	if ((BUFFER_SIZE < 1) || (fd < 0) || (!line))
		return (-1);
	if (!reminder)
		if (!(reminder = ft_strdup("")))
			return (-1);
	while (1)
	{
		if ((state = ft_get_line(&reminder, line)))
			return (state);
		if (!(buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
			return (-1);
		if ((size = read(fd, buff, BUFFER_SIZE)) == -1)
			return (-1);
		buff[size] = '\0';
		if ((state = ft_end_of_line(size, &buff, &reminder, line) == 1))
			continue ;
		else
			return (state);
	}
	return (-1);
}
