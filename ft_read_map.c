/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odomenic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 21:28:21 by odomenic          #+#    #+#             */
/*   Updated: 2021/03/21 18:12:51 by odomenic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_fill_arr(t_param *params, int i, int j)
{
	if ((params->map->map_str[i][j] == '0') ||
			(params->map->map_str[i][j] == '1'))
		params->map->map[i][j] = (int)(params->map->map_str[i][j] - '0');
	else if (params->map->map_str[i][j] == '2')
	{
		params->config->sprite_count++;
		params->map->map[i][j] = (int)(params->map->map_str[i][j] - '0');
	}
	else if ((params->map->map_str[i][j] == 'N') ||
			(params->map->map_str[i][j] == 'W')
			|| (params->map->map_str[i][j] == 'S') ||
			(params->map->map_str[i][j] == 'E'))
	{
		params->map->map[i][j] = 3;
		params->plr->y = params->map->height - 1 - i + 0.5;
		params->plr->x = j + 0.5;
		ft_dir_plane(params);
	}
	else
		params->map->map[i][j] = -1;
}

void	ft_get_arr(t_param *params, int i)
{
	int	len;
	int	j;

	j = 0;
	len = ft_strlen(params->map->map_str[i]);
	while (j < len)
	{
		ft_fill_arr(params, i, j);
		j++;
	}
	while (j < params->map->width)
	{
		params->map->map[i][j] = -1;
		j++;
	}
}

int		ft_convert(t_param *prms)
{
	int	i;

	i = 0;
	if (!(prms->map->map = (int **)malloc(sizeof(int *) * prms->map->height)))
		return (-1);
	while (i < prms->map->height)
	{
		if (!(prms->map->map[i] = (int *)malloc(sizeof(int) *
						prms->map->width)))
			return (-1);
		ft_get_arr(prms, i);
		i++;
	}
	return (0);
}

void	ft_new_map(t_param *prms, int num, char *line, char **old_map)
{
	int i;

	if (!(prms->map->map_str = (char **)malloc(sizeof(char *) * (num + 2))))
		ft_error(-5, prms);
	i = 0;
	while (i < num)
	{
		if (!(prms->map->map_str[i] = ft_strdup(old_map[i])))
			ft_error(-5, prms);
		free(old_map[i]);
		i++;
	}
	if (old_map)
		free(old_map);
	if (!(prms->map->map_str[i] = ft_strdup(line)))
		ft_error(-5, prms);
	prms->map->map_str[i + 1] = NULL;
}

void	ft_read_map(t_param *prms, char *line)
{
	int		i;
	int		num;
	char	**old_map;

	num = 0;
	if (prms->map->map_str)
		num = ft_numobjs(prms->map->map_str);
	if (!(old_map = (char **)malloc(sizeof(char *) * num)))
		ft_error(-5, prms);
	i = 0;
	while (i < num)
	{
		if (!(old_map[i] = ft_strdup(prms->map->map_str[i])))
			ft_error(-5, prms);
		free(prms->map->map_str[i]);
		i++;
	}
	if (prms->map->map_str)
		free(prms->map->map_str);
	ft_new_map(prms, num, line, old_map);
}
