/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odomenic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 20:46:02 by odomenic          #+#    #+#             */
/*   Updated: 2021/03/21 14:42:52 by odomenic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_closed_map(int **map, int i, int j, t_param *p)
{
	if ((map[i][j] == 1) || (map[i][j] == -1))
		return (map[i][j]);
	map[i][j] = 1;
	if ((i > 0) && (j > 0) && (i < (p->map->height - 1)) &&
			(j < (p->map->width - 1)))
	{
		if ((map[i - 1][j] == -1) || (map[i + 1][j] == -1) ||
				(map[i][j - 1] == -1) || (map[i][j + 1] == -1))
			return (-1);
		if ((ft_closed_map(map, i - 1, j, p)) == -1)
			return (-1);
		if ((ft_closed_map(map, i + 1, j, p)) == -1)
			return (-1);
		if ((ft_closed_map(map, i, j - 1, p)) == -1)
			return (-1);
		if ((ft_closed_map(map, i, j + 1, p)) == -1)
			return (-1);
	}
	return (0);
}

int		**ft_map_copy(int **map, int width, int lines)
{
	int	i;
	int	j;
	int	**map_copy;

	i = 0;
	if (!(map_copy = (int **)malloc(sizeof(int *) * lines)))
		return (NULL);
	while (i < lines)
	{
		j = 0;
		if (!(map_copy[i] = (int *)malloc(sizeof(int) * width)))
			return (NULL);
		while (j < width)
		{
			map_copy[i][j] = map[i][j];
			j++;
		}
		i++;
	}
	return (map_copy);
}

int		ft_map(t_param *params)
{
	int	i;
	int	**map_copy;
	int	error;

	error = 0;
	params->map->width = ft_width_arr(params->map->map_str);
	params->map->height = ft_numobjs(params->map->map_str);
	if (ft_convert(params))
		return (-5);
	i = 0;
	if ((map_copy = ft_map_copy(params->map->map, params->map->width,
					params->map->height)) == NULL)
		return (-5);
	if (ft_closed_map(map_copy, (int)(params->map->height -
					params->plr->y), (int)params->plr->x, params))
		error = -4;
	i = 0;
	while (i < params->map->height)
	{
		free(map_copy[i]);
		i++;
	}
	free(map_copy);
	return (error);
}
