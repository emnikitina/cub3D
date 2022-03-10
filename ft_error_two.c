/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odomenic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 11:01:54 by odomenic          #+#    #+#             */
/*   Updated: 2021/03/21 20:33:00 by odomenic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_check_tex_path(t_config *config)
{
	int	fd;

	if ((fd = open(config->no, O_RDONLY)) == -1)
		return ("Can't open no texture file\n");
	if ((fd = open(config->so, O_RDONLY)) == -1)
		return ("Can't open so texture file\n");
	if ((fd = open(config->we, O_RDONLY)) == -1)
		return ("Can't open we texture file\n");
	if ((fd = open(config->ea, O_RDONLY)) == -1)
		return ("Can't open ea texture file\n");
	if ((fd = open(config->sprite, O_RDONLY)) == -1)
		return ("Can't open sprite texture file\n");
	return (NULL);
}

int		ft_check_tex_type(char *str)
{
	char	**objs;
	int		num;

	objs = ft_split(str, '.');
	num = ft_numobjs(objs);
	if (!(ft_strncmp(objs[num - 1], "xpm", 4)))
	{
		ft_free_objs(objs);
		return (1);
	}
	ft_free_objs(objs);
	return (0);
}

char	*ft_check_texs(t_param *prms)
{
	if (!(ft_check_tex_type(prms->config->no)))
		return ("Wrong type of NO texture\n");
	if (!(ft_check_tex_type(prms->config->so)))
		return ("Wrong type of SO texture\n");
	if (!(ft_check_tex_type(prms->config->we)))
		return ("Wrong type of WE texture\n");
	if (!(ft_check_tex_type(prms->config->ea)))
		return ("Wrong type of EA texture\n");
	if (!(ft_check_tex_type(prms->config->sprite)))
		return ("Wrong type of sprite texture\n");
	return (NULL);
}

char	*ft_flags_absent(t_flags *flags)
{
	if (flags->c < 1)
		return ("Setting for ceilling is absent\n");
	if (flags->f < 1)
		return ("Setting for floor is absent\n");
	if (flags->r < 1)
		return ("Setting for resolution is absent\n");
	if (flags->pers < 1)
		return ("Person is absent in map\n");
	return (NULL);
}

char	*ft_flags_double(t_flags *flags)
{
	if (flags->no != 1)
		return ("Wrong setting for NO texture\n");
	if (flags->so != 1)
		return ("Wrong setting for SO texture\n");
	if (flags->we != 1)
		return ("Wrong setting for  WE texture\n");
	if (flags->ea != 1)
		return ("Wrong setting for EA texture\n");
	if (flags->s != 1)
		return ("Wrong setting for sprite texture\n");
	if (flags->c > 1)
		return ("Double setting for ceilling\n");
	if (flags->f > 1)
		return ("Double setting for floor\n");
	if (flags->r > 1)
		return ("Double setting for resolution\n");
	if (flags->pers > 1)
		return ("Double person in map\n");
	return (NULL);
}
