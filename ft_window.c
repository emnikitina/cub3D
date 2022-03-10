/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_window.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odomenic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 20:15:20 by odomenic          #+#    #+#             */
/*   Updated: 2021/03/23 20:38:54 by odomenic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_close(t_param *prms)
{
	mlx_destroy_window(prms->win->mlx, prms->win->win);
	ft_clean(prms);
	exit(0);
	return (0);
}

int		ft_win_params(t_param *prms)
{
	mlx_get_screen_size(&prms->win->width, &prms->win->height);
	if (prms->win->width > prms->config->rx)
		prms->win->width = prms->config->rx;
	if (prms->win->height > prms->config->ry)
		prms->win->height = prms->config->ry;
	if (!prms->config->screenshot)
	{
		if (!(prms->win->win = mlx_new_window(prms->win->mlx, prms->win->width,
				prms->win->height, "cub3D")))
			return (-1);
	}
	else
	{
		if (prms->config->rx < 5000)
			prms->win->width = prms->config->rx;
		else
			prms->win->width = 5000;
		if (prms->config->ry < 5000)
			prms->win->height = prms->config->ry;
		else
			prms->win->height = 5000;
	}
	return (0);
}

int		ft_init_win(t_param *prms)
{
	ft_malloc_memory(prms);
	if (!(prms->win->mlx = mlx_init()))
		return (-1);
	if (ft_win_params(prms))
		return (-1);
	if (!(prms->win->img = mlx_new_image(prms->win->mlx, prms->win->width,
			prms->win->height)))
		return (-1);
	prms->win->addr = mlx_get_data_addr(prms->win->img, &prms->win->bpp,
			&prms->win->line_l, &prms->win->endian);
	ft_open_textures(prms);
	return (0);
}

int		ft_write_win(t_param *prms)
{
	if (ft_init_win(prms))
		return (-1);
	mlx_hook(prms->win->win, 2, (1L << 0), &ft_key_press, prms);
	mlx_hook(prms->win->win, 17, 0, ft_close, prms);
	mlx_hook(prms->win->win, 3, (1L << 0), &ft_key_unpress, prms);
	mlx_loop_hook(prms->win->mlx, ft_raycasting, prms);
	mlx_loop(prms->win->mlx);
	return (0);
}
