/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odomenic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 18:01:42 by odomenic          #+#    #+#             */
/*   Updated: 2021/03/23 18:52:07 by odomenic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_move(t_param *prms)
{
	double	move;
	double	rot;
	int		k;

	k = prms->key->w + prms->key->s + prms->key->a + prms->key->d + prms->key->r
		+ prms->key->l;
	move = 0.1 / ((double)k);
	rot = 0.05 / ((double)k);
	if (prms->key->w == 1)
		ft_go_forw(prms, move);
	if (prms->key->s == 1)
		ft_go_back(prms, move);
	if (prms->key->a == 1)
		ft_go_left(prms, move);
	if (prms->key->d == 1)
		ft_go_right(prms, move);
	if (prms->key->r == 1)
		ft_rot_right(prms, rot);
	if (prms->key->l == 1)
		ft_rot_left(prms, rot);
}

int		ft_key_press(int keycode, t_param *prms)
{
	if (keycode == 13)
		prms->key->w = 1;
	if (keycode == 1)
		prms->key->s = 1;
	if (keycode == 0)
		prms->key->a = 1;
	if (keycode == 2)
		prms->key->d = 1;
	if (keycode == 123)
		prms->key->l = 1;
	if (keycode == 124)
		prms->key->r = 1;
	if (keycode == 53)
		ft_close(prms);
	return (0);
}

int		ft_key_unpress(int keycode, t_param *prms)
{
	if (keycode == 13)
		prms->key->w = 0;
	if (keycode == 1)
		prms->key->s = 0;
	if (keycode == 0)
		prms->key->a = 0;
	if (keycode == 2)
		prms->key->d = 0;
	if (keycode == 123)
		prms->key->l = 0;
	if (keycode == 124)
		prms->key->r = 0;
	return (0);
}

void	ft_malloc_memory(t_param *prms)
{
	if (!(prms->sprite_dist = (double *)malloc(sizeof(double) *
					prms->config->sprite_count)))
		ft_error(-5, prms);
	if (!(prms->sprites = (t_point *)malloc(sizeof(t_point) *
					prms->config->sprite_count)))
		ft_error(-5, prms);
}
