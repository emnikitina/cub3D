/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pixel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odomenic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 13:54:07 by odomenic          #+#    #+#             */
/*   Updated: 2021/03/23 20:37:00 by odomenic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_dir_plane(t_param *prms)
{
	int x;
	int y;

	x = (int)prms->plr->x;
	y = (int)prms->plr->y;
	if (prms->map->map_str[prms->map->height - 1 - y][x] == 'N')
	{
		prms->plr->dir->y = 1;
		prms->plr->plane->x = 0.66;
	}
	else if (prms->map->map_str[prms->map->height - 1 - y][x] == 'S')
	{
		prms->plr->dir->y = -1;
		prms->plr->plane->x = -0.66;
	}
	else if (prms->map->map_str[prms->map->height - 1 - y][x] == 'W')
	{
		prms->plr->dir->x = -1;
		prms->plr->plane->y = 0.66;
	}
	else if (prms->map->map_str[prms->map->height - 1 - y][x] == 'E')
	{
		prms->plr->dir->x = 1;
		prms->plr->plane->y = -0.66;
	}
}

void	ft_raydir(t_param *prms, t_point *dist, int i)
{
	double	cam_x;

	cam_x = 2 * i / (double)prms->win->width - 1;
	prms->plr->ray_dir->x = prms->plr->dir->x + prms->plr->plane->x * cam_x;
	prms->plr->ray_dir->y = prms->plr->dir->y + prms->plr->plane->y * cam_x;
	if (!prms->plr->ray_dir->y)
		dist->x = 0;
	else
	{
		if (!prms->plr->ray_dir->x)
			dist->x = 1;
		else
			dist->x = fabs(1 / prms->plr->ray_dir->x);
	}
	if (!prms->plr->ray_dir->x)
		dist->y = 0;
	else
	{
		if (!prms->plr->ray_dir->y)
			dist->y = 1;
		else
			dist->y = fabs(1 / prms->plr->ray_dir->y);
	}
}

void	ft_step(t_param *prms, t_point *side, t_point dist, t_point_int point)
{
	if (prms->plr->ray_dir->x < 0)
	{
		prms->plr->step->x = -1;
		side->x = (prms->plr->x - point.x) * dist.x;
	}
	else
	{
		prms->plr->step->x = 1;
		side->x = (point.x + 1.0 - prms->plr->x) * dist.x;
	}
	if (prms->plr->ray_dir->y < 0)
	{
		prms->plr->step->y = -1;
		side->y = (prms->plr->y - point.y) * dist.y;
	}
	else
	{
		prms->plr->step->y = 1;
		side->y = (point.y + 1.0 - prms->plr->y) * dist.y;
	}
}

void	ft_wall(t_param *prms, t_point dist, t_point side_dist, t_point_int
		*map_point)
{
	int hit;

	hit = 0;
	while (hit == 0)
	{
		if (side_dist.x < side_dist.y)
		{
			side_dist.x += dist.x;
			map_point->x += prms->plr->step->x;
			prms->plr->side = 0;
		}
		else
		{
			side_dist.y += dist.y;
			map_point->y += prms->plr->step->y;
			prms->plr->side = 1;
		}
		if (prms->map->map[prms->map->height - 1 - map_point->y][map_point->x]
				== 1)
			hit = 1;
	}
}

int		ft_raycasting(t_param *prms)
{
	int			i;
	t_point_int	map_point;
	t_point		dist;
	t_point		side_dist;
	double		sprite_normal[8000];

	ft_move(prms);
	i = -1;
	while (++i < prms->win->width)
	{
		map_point.x = (int)prms->plr->x;
		map_point.y = (int)prms->plr->y;
		ft_raydir(prms, &dist, i);
		ft_step(prms, &side_dist, dist, map_point);
		ft_wall(prms, dist, side_dist, &map_point);
		sprite_normal[i] = ft_draw(prms, map_point, i);
	}
	ft_sprite(prms, sprite_normal);
	if (!prms->config->screenshot)
		mlx_put_image_to_window(prms->win->mlx, prms->win->win, prms->win->img,
				0, 0);
	return (0);
}
