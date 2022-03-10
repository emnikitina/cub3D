/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_params.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odomenic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 21:08:26 by odomenic          #+#    #+#             */
/*   Updated: 2021/03/23 21:59:40 by odomenic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_get_colors_utils(int *r, int *g, int *b, char *s)
{
	int i;

	i = ft_get_nbr(s, r);
	while ((s[i] == ' ') && (s[i] != '\0'))
		i++;
	if (s[i] == ',')
		i++;
	else
		return (-1);
	while ((s[i] == ' ') && (s[i] != '\0'))
		i++;
	i += ft_get_nbr(&s[i], g);
	while ((s[i] == ' ') && (s[i] != '\0'))
		i++;
	if (s[i] == ',')
		i++;
	else
		return (-1);
	while ((s[i] == ' ') && (s[i] != '\0'))
		i++;
	i += ft_get_nbr(&s[i], b);
	return (0);
}

int		ft_get_colors(const char *line, int *r, int *g, int *b)
{
	char	*s;

	if (!(s = ft_check_colors(line)))
		return (-1);
	if (ft_get_colors_utils(r, g, b, s) == -1)
	{
		free(s);
		return (-1);
	}
	free(s);
	return (0);
}

void	ft_get_textures(char **objs, t_config *config_cub, t_flags *flags)
{
	if (!(ft_strncmp(objs[0], "NO", 3)))
	{
		config_cub->no = ft_strdup(objs[1]);
		flags->no++;
	}
	else if (!(ft_strncmp(objs[0], "SO", 3)))
	{
		config_cub->so = ft_strdup(objs[1]);
		flags->so++;
	}
	else if (!(ft_strncmp(objs[0], "WE", 3)))
	{
		config_cub->we = ft_strdup(objs[1]);
		flags->we++;
	}
	else if (!(ft_strncmp(objs[0], "EA", 3)))
	{
		config_cub->ea = ft_strdup(objs[1]);
		flags->ea++;
	}
	else if (!(ft_strncmp(objs[0], "S", 2)))
	{
		config_cub->sprite = ft_strdup(objs[1]);
		flags->s++;
	}
}

int		ft_get_resolution(char **objs, t_config *config, t_flags *flags)
{
	flags->r++;
	if (ft_isnum(objs[1]) && ft_isnum(objs[2]))
	{
		config->rx = ft_atoi(objs[1]);
		config->ry = ft_atoi(objs[2]);
	}
	else
		return (-2);
	if ((config->rx <= 0) || (config->ry <= 0))
		return (-2);
	return (0);
}

int		ft_get_params(char **objs, char *line, t_config *config, t_flags *flags)
{
	int	num;

	num = ft_numobjs(objs);
	if (!(ft_strncmp(objs[0], "F", 2)))
	{
		if (ft_get_colors(line, &config->fr, &config->fg, &config->fb))
			return (-1);
		flags->f++;
	}
	else if (!(ft_strncmp(objs[0], "C", 2)))
	{
		if (ft_get_colors(line, &config->cr, &config->cg, &config->cb))
			return (-1);
		flags->c++;
	}
	else if (num == 2)
		ft_get_textures(objs, config, flags);
	else if ((num == 3) && (!(ft_strncmp(objs[0], "R", 2))))
		return (ft_get_resolution(objs, config, flags));
	return (0);
}
