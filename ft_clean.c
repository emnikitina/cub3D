/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odomenic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 19:58:29 by odomenic          #+#    #+#             */
/*   Updated: 2021/03/23 19:59:12 by odomenic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_clean_texs(t_param *prms)
{
	if (prms->config->so)
		free(prms->config->so);
	if (prms->config->no)
		free(prms->config->no);
	if (prms->config->we)
		free(prms->config->we);
	if (prms->config->ea)
		free(prms->config->ea);
	if (prms->config->sprite)
		free(prms->config->sprite);
}

void	ft_clean(t_param *prms)
{
	int i;

	if (prms->map->map)
	{
		i = 0;
		while (i < prms->map->height)
		{
			free(prms->map->map[i]);
			i++;
		}
		free(prms->map->map);
	}
	if (prms->map->map_str)
	{
		i = 0;
		while (i < prms->map->height)
		{
			free(prms->map->map_str[i]);
			i++;
		}
		free(prms->map->map_str);
	}
	ft_clean_texs(prms);
	free(prms->sprites);
	free(prms->sprite_dist);
}
