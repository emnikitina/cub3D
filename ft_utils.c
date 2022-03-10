/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odomenic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 21:04:19 by odomenic          #+#    #+#             */
/*   Updated: 2021/03/23 22:00:53 by odomenic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_numobjs(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int		ft_get_nbr(const char *s, int *num)
{
	int	i;

	i = 0;
	*num = 0;
	while ((ft_isdigit(s[i])) && (s[i] != '\0'))
	{
		*num = *num * 10 + (s[i] - '0');
		i++;
	}
	if (i == 0)
		*num = -1;
	return (i);
}

int		ft_isnum(const char *str)
{
	int		i;
	size_t	num;

	i = 0;
	num = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]))
			num++;
		i++;
	}
	if (num == ft_strlen(str))
		return (1);
	return (0);
}

size_t	ft_width_arr(char **map)
{
	size_t	max;
	int		i;

	i = 0;
	max = ft_strlen(map[0]);
	while (map[i])
	{
		if (max < ft_strlen(map[i]))
			max = ft_strlen(map[i]);
		i++;
	}
	return (max);
}

void	ft_sprite_sort(int count, t_point *sprites, double *sprite_dist)
{
	t_point	replace;
	double	dist;
	int		i;
	int		j;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (sprite_dist[j] < sprite_dist[j + 1])
			{
				dist = sprite_dist[j];
				replace = sprites[j];
				sprite_dist[j] = sprite_dist[j + 1];
				sprites[j] = sprites[j + 1];
				sprite_dist[j + 1] = dist;
				sprites[j + 1] = replace;
			}
			j++;
		}
		i++;
	}
}
