/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odomenic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 20:07:15 by odomenic          #+#    #+#             */
/*   Updated: 2021/03/17 20:59:31 by odomenic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_go_forw(t_param *prms, double move)
{
	double	i;
	int		a_plus;
	int		a_minus;

	i = prms->map->height - prms->plr->y;
	a_plus = (int)(i - prms->plr->dir->y * move + 0.01);
	a_minus = (int)(i - prms->plr->dir->y * move - 0.01);
	if (((prms->map->map[a_minus][(int)prms->plr->x] == 0)
				|| (prms->map->map[a_minus][(int)prms->plr->x] == 3))
			&& ((prms->map->map[a_plus][(int)prms->plr->x] == 0)
				|| (prms->map->map[a_plus][(int)prms->plr->x] == 3)))
		prms->plr->y += (prms->plr->dir->y * move);
	a_plus = (int)(prms->plr->x + prms->plr->dir->x * move + 0.01);
	a_minus = (int)(prms->plr->x + prms->plr->dir->x * move - 0.01);
	if (((prms->map->map[(int)i][a_plus] == 0)
				|| (prms->map->map[(int)i][a_plus] == 3))
			&& ((prms->map->map[(int)i][a_minus] == 0)
				|| (prms->map->map[(int)i][a_minus] == 3)))
		prms->plr->x += (prms->plr->dir->x * move);
}

void	ft_go_back(t_param *prms, double move)
{
	double	i;
	int		a_plus;
	int		a_minus;

	i = prms->map->height - prms->plr->y;
	a_plus = (int)(i + prms->plr->dir->y * move + 0.01);
	a_minus = (int)(i + prms->plr->dir->y * move - 0.01);
	if (((prms->map->map[a_plus][(int)prms->plr->x] == 0)
				|| (prms->map->map[a_plus][(int)prms->plr->x] == 3))
			&& ((prms->map->map[a_minus][(int)prms->plr->x] == 0)
				|| (prms->map->map[a_minus][(int)prms->plr->x] == 3)))
		prms->plr->y -= (prms->plr->dir->y * move);
	a_plus = (int)(prms->plr->x - prms->plr->dir->x * move + 0.01);
	a_minus = (int)(prms->plr->x - prms->plr->dir->x * move - 0.01);
	if (((prms->map->map[(int)i][a_minus] == 0)
				|| (prms->map->map[(int)i][a_minus] == 3))
			&& ((prms->map->map[(int)i][a_plus] == 0)
				|| (prms->map->map[(int)i][a_plus] == 3)))
		prms->plr->x -= (prms->plr->dir->x * move);
}

void	ft_go_left(t_param *prms, double move)
{
	double	i;
	int		a_plus;
	int		a_minus;

	i = prms->map->height - prms->plr->y;
	a_plus = (int)(i - prms->plr->dir->x * move + 0.01);
	a_minus = (int)(i - prms->plr->dir->x * move - 0.01);
	if (((prms->map->map[a_minus][(int)prms->plr->x] == 0)
				|| (prms->map->map[a_minus][(int)prms->plr->x] == 3))
			&& ((prms->map->map[a_plus][(int)prms->plr->x] == 0)
				|| (prms->map->map[a_plus][(int)prms->plr->x] == 3)))
		prms->plr->y += (prms->plr->dir->x * move);
	a_plus = (int)(prms->plr->x - prms->plr->dir->y * move + 0.01);
	a_minus = (int)(prms->plr->x - prms->plr->dir->y * move - 0.01);
	if (((prms->map->map[(int)i][a_minus] == 0)
				|| (prms->map->map[(int)i][a_minus] == 3))
			&& ((prms->map->map[(int)i][a_plus] == 0)
				|| (prms->map->map[(int)i][a_plus] == 3)))
		prms->plr->x -= (prms->plr->dir->y * move);
}

void	ft_go_right(t_param *prms, double move)
{
	double	i;
	int		a_plus;
	int		a_minus;

	i = prms->map->height - prms->plr->y;
	a_plus = (int)(prms->plr->x + prms->plr->dir->y * move + 0.01);
	a_minus = (int)(prms->plr->x + prms->plr->dir->y * move - 0.01);
	if (((prms->map->map[(int)i][a_plus] == 0)
				|| (prms->map->map[(int)i][a_plus] == 3))
			&& ((prms->map->map[(int)i][a_minus] == 0)
				|| (prms->map->map[(int)i][a_minus] == 3)))
		prms->plr->x += (prms->plr->dir->y * move);
	a_plus = (int)(i + prms->plr->dir->x * move + 0.01);
	a_minus = (int)(i + prms->plr->dir->x * move - 0.01);
	if (((prms->map->map[a_plus][(int)(prms->plr->x)] == 0)
				|| (prms->map->map[a_plus][(int)(prms->plr->x)] == 3))
			&& ((prms->map->map[a_minus][(int)(prms->plr->x)] == 0)
				|| (prms->map->map[a_minus][(int)(prms->plr->x)] == 3)))
		prms->plr->y -= (prms->plr->dir->x * move);
}
