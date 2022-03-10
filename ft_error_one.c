/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odomenic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 11:04:28 by odomenic          #+#    #+#             */
/*   Updated: 2021/03/23 21:59:13 by odomenic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_error(int error, t_param *prms)
{
	char	*str;

	str = NULL;
	if (error == -1)
		str = "Wrong format of colors\n";
	else if (error == -2)
		str = "Wrong format of resolution\n";
	else if (error == -3)
		str = "Empty line in the map\n";
	else if (error == -4)
		str = "Not valid map\n";
	else if (error == -5)
		str = "Error of malloc\n";
	else if (error == -6)
		str = "Wrong character in map\n";
	if (str)
	{
		ft_clean(prms);
		write(2, "Error\n", 6);
		write(2, str, ft_strlen(str));
		exit(0);
	}
}

void	ft_check_file(t_param *params, t_flags *flags)
{
	char	*str;

	str = NULL;
	if (ft_flags_absent(flags))
		str = ft_flags_absent(flags);
	else if (ft_flags_double(flags))
		str = ft_flags_double(flags);
	else if (ft_check_config(params->config))
		str = ft_check_config(params->config);
	else if (ft_check_tex_path(params->config))
		str = ft_check_tex_path(params->config);
	else if (ft_check_texs(params))
		str = ft_check_texs(params);
	if (str)
	{
		write(2, "Error\n", 6);
		write(2, str, ft_strlen(str));
		ft_clean(params);
		exit(0);
	}
}

char	*ft_check_config(t_config *conf)
{
	if ((conf->fr < 0) || (conf->fg < 0) || (conf->fb < 0) || (conf->fr > 255)
			|| (conf->fg > 255) || (conf->fb > 255))
		return ("Wrong format of floor colors\n");
	if ((conf->cr < 0) || (conf->cg < 0) || (conf->cb < 0) || (conf->cr > 255)
			|| (conf->cg > 255) || (conf->cb > 255))
		return ("Wrong format of ceilling colors\n");
	if ((conf->rx < 1) || (conf->ry < 1))
		return ("Wrong format of resolution numbers\n");
	return (NULL);
}

char	*ft_check_colors(const char *line)
{
	char	*s;
	int		i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if ((line[i] == 'F') || (line[i] == 'C'))
		i++;
	else
		return (NULL);
	while (line[i] == ' ')
		i++;
	s = ft_strdup(&line[i]);
	return (s);
}
