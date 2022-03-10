/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_textures.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odomenic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 20:07:36 by odomenic          #+#    #+#             */
/*   Updated: 2021/03/18 20:28:35 by odomenic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_get_tex(t_param *p, char *path_tex, t_tex *tex)
{
	tex->img = mlx_xpm_file_to_image(p->win->mlx, path_tex, &tex->width,
			&tex->height);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_l,
			&tex->endian);
}

void	ft_open_textures(t_param *params)
{
	ft_get_tex(params, params->config->no, params->texs->tex_no);
	ft_get_tex(params, params->config->so, params->texs->tex_so);
	ft_get_tex(params, params->config->we, params->texs->tex_we);
	ft_get_tex(params, params->config->ea, params->texs->tex_ea);
	ft_get_tex(params, params->config->sprite, params->texs->tex_sprite);
}

t_tex	*ft_choose_tex(t_param *prms)
{
	if (prms->plr->side == 1)
	{
		if (prms->plr->step->y > 0)
			return (prms->texs->tex_no);
		if (prms->plr->step->y < 0)
			return (prms->texs->tex_so);
	}
	else
	{
		if (prms->plr->step->x > 0)
			return (prms->texs->tex_we);
		if (prms->plr->step->x < 0)
			return (prms->texs->tex_ea);
	}
	return (NULL);
}
