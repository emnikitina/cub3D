/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprites.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odomenic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 17:35:37 by odomenic          #+#    #+#             */
/*   Updated: 2021/03/23 22:00:51 by odomenic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_sprite_init(t_param *prms)
{
	int		i;
	int		j;
	int		k;

	k = 0;
	i = 0;
	while (i < prms->map->height)
	{
		j = 0;
		while (j < prms->map->width)
		{
			if (prms->map->map[i][j] == 2)
			{
				prms->sprites[k].x = j + 0.5;
				prms->sprites[k].y = prms->map->height - 1 - i + 0.5;
				k++;
			}
			j++;
		}
		i++;
	}
}

void	ft_sprite_params(t_point point, t_sprite *s, t_param *prms)
{
	double inv_det;

	inv_det = 1.0 / (prms->plr->plane->x * prms->plr->dir->y - prms->plr->dir->x
			* prms->plr->plane->y);
	s->tform->x = inv_det * (prms->plr->dir->y * point.x - prms->plr->dir->x *
			point.y);
	s->tform->y = inv_det * (-prms->plr->plane->y * point.x +
			prms->plr->plane->x * point.y);
	s->screen_x = (int)((prms->win->width / 2) * (1 + s->tform->x /
				s->tform->y));
	s->height = abs((int)(prms->win->height /
				(s->tform->y * ((double)(prms->win->height * 4) /
								(double)(prms->win->width * 3)))));
	if ((s->draw_start->y = (-s->height / 2 + prms->win->height / 2)) < 0)
		s->draw_start->y = 0;
	if ((s->draw_end->y = (s->height / 2 + prms->win->height / 2)) >=
			prms->win->height)
		s->draw_end->y = prms->win->height - 1;
	s->width = abs((int)(prms->win->height /
				(s->tform->y * ((double)(prms->win->height * 4) /
								(double)(prms->win->width * 3)))));
	if ((s->draw_start->x = -s->width / 2 + s->screen_x) < 0)
		s->draw_start->x = 0;
	if ((s->draw_end->x = s->width / 2 + s->screen_x) >= prms->win->width)
		s->draw_end->x = prms->win->width - 1;
}

void	ft_sprites_to_win(t_sprite *s, double *sprite_normal, t_param *prms)
{
	int			s_order;
	t_point_int	tex;
	int			d;
	int			clr;
	int			j;

	s_order = s->draw_start->x - 1;
	while (++s_order < s->draw_end->x)
	{
		tex.x = (int)(256 * (s_order - (-s->width / 2 + s->screen_x)) * 64 /
				s->width) / 256;
		if ((s->tform->y > 0) && (s_order > 0) && (s_order < prms->win->width)
				&& (s->tform->y < sprite_normal[s_order]))
		{
			j = s->draw_start->y - 1;
			while (++j < s->draw_end->y)
			{
				d = j * 256 - prms->win->height * 128 + s->height * 128;
				tex.y = ((d * 64) / s->height) / 256;
				clr = ((int *)prms->texs->tex_sprite->addr)[64 * tex.y + tex.x];
				if ((clr & 0x00FFFFFF) != 9961608)
					my_mlx_pixel_put(prms, s_order, j, clr);
			}
		}
	}
}

void	ft_sprite_draw(t_param *prms, t_point *sprites, double *sprite_normal)
{
	int			i;
	t_point		sprite_point;
	t_sprite	*sprite_conf;

	i = 0;
	sprite_conf = &(t_sprite){0, 0, 0, &(t_point){0.0, 0.0},
		&(t_point){0.0, 0.0}, &(t_point){0.0, 0.0}};
	while (i < prms->config->sprite_count)
	{
		sprite_point.x = sprites[i].x - prms->plr->x;
		sprite_point.y = sprites[i].y - prms->plr->y;
		ft_sprite_params(sprite_point, sprite_conf, prms);
		ft_sprites_to_win(sprite_conf, sprite_normal, prms);
		i++;
	}
}

void	ft_sprite(t_param *prms, double *sprite_normal)
{
	int		i;

	ft_sprite_init(prms);
	i = 0;
	while (i < prms->config->sprite_count)
	{
		prms->sprite_dist[i] = ((prms->plr->x - prms->sprites[i].x) *
				(prms->plr->x - prms->sprites[i].x) + (prms->plr->y -
					prms->sprites[i].y) * (prms->plr->y - prms->sprites[i].y));
		i++;
	}
	ft_sprite_sort(prms->config->sprite_count, prms->sprites,
			prms->sprite_dist);
	ft_sprite_draw(prms, prms->sprites, sprite_normal);
}
