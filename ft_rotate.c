/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odomenic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 21:00:23 by odomenic          #+#    #+#             */
/*   Updated: 2021/03/17 21:07:06 by odomenic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_rot_right(t_param *prms, double rot)
{
	double old_dir;
	double old_plane;

	old_dir = prms->plr->dir->x;
	prms->plr->dir->x = prms->plr->dir->x * cos(-rot) - prms->plr->dir->y *
		sin(-rot);
	prms->plr->dir->y = old_dir * sin(-rot) + prms->plr->dir->y * cos(-rot);
	old_plane = prms->plr->plane->x;
	prms->plr->plane->x = prms->plr->plane->x * cos(-rot) -
		prms->plr->plane->y * sin(-rot);
	prms->plr->plane->y = old_plane * sin(-rot) + prms->plr->plane->y *
		cos(-rot);
}

void	ft_rot_left(t_param *prms, double rot)
{
	double old_dir;
	double old_plane;

	old_dir = prms->plr->dir->x;
	prms->plr->dir->x = prms->plr->dir->x * cos(rot) - prms->plr->dir->y *
		sin(rot);
	prms->plr->dir->y = old_dir * sin(rot) + prms->plr->dir->y * cos(rot);
	old_plane = prms->plr->plane->x;
	prms->plr->plane->x = prms->plr->plane->x * cos(rot) - prms->plr->plane->y
		* sin(rot);
	prms->plr->plane->y = old_plane * sin(rot) + prms->plr->plane->y * cos(rot);
}
