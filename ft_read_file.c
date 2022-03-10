/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odomenic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 19:54:07 by odomenic          #+#    #+#             */
/*   Updated: 2021/03/21 17:39:50 by odomenic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_include(const char *s, t_flags *flags)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (!((s[i] == '0') || (s[i] == '1') || (s[i] == '2') || (s[i] == ' ')
					|| (s[i] == 'N') || (s[i] == 'S') || (s[i] == 'W') ||
					(s[i] == 'E')))
			return (-1);
		if ((s[i] == 'S') || (s[i] == 'N') || (s[i] == 'W') || (s[i] == 'E'))
			flags->pers++;
		i++;
	}
	return (1);
}

int		ft_map_or_not(char *objs, int map, char *line)
{
	if ((map == 1) || ((map == 0) && (ft_strncmp(objs, "NO", 3) != 0) &&
			(ft_strncmp(objs, "SO", 3) != 0) && (ft_strncmp(objs, "WE", 3) != 0)
			&& (ft_strncmp(objs, "EA", 3) != 0) &&
			(ft_strncmp(objs, "S", 2) != 0) && (ft_strncmp(objs, "R", 2) != 0)
			&& (ft_strncmp(objs, "F", 2) != 0)
			&& (ft_strncmp(objs, "C", 2) != 0) && (ft_strlen(line))))
		return (1);
	return (0);
}

int		ft_get_map(char *line, t_flags *flags, t_param *params)
{
	if (ft_strlen(line))
	{
		if (ft_include(line, flags) == -1)
			return (-6);
		ft_read_map(params, line);
	}
	else
		return (-3);
	return (0);
}

void	ft_free_objs(char **objs)
{
	int i;
	int num;

	i = 0;
	num = ft_numobjs(objs);
	while (i < num)
	{
		free(objs[i]);
		i++;
	}
	free(objs);
}

int		ft_read_file(int fd, t_flags *flags, t_param *params)
{
	char	*line;
	char	**objs;
	int		ret;

	while (get_next_line(fd, &line))
	{
		objs = ft_split(line, ' ');
		if (ft_numobjs(objs))
		{
			flags->map = ft_map_or_not(objs[0], flags->map, line);
			if (flags->map == 0)
				if ((ret = ft_get_params(objs, line, params->config, flags)))
					return (ret);
		}
		if (flags->map == 1)
			if ((ret = ft_get_map(line, flags, params)))
				return (ret);
		ft_free_objs(objs);
		free(line);
	}
	free(line);
	return (1);
}
