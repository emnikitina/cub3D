/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odomenic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 20:40:06 by odomenic          #+#    #+#             */
/*   Updated: 2021/03/23 19:54:41 by odomenic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_check_file_type(char *str)
{
	char	**objs;
	int		num;

	objs = ft_split(str, '.');
	num = ft_numobjs(objs);
	if (!(ft_strncmp(objs[num - 1], "cub", 4)))
	{
		ft_free_objs(objs);
		return (0);
	}
	ft_free_objs(objs);
	return (-1);
}

void	ft_prepare_game(t_param *params, t_flags *flags, char **argv)
{
	int fd;

	if (ft_check_file_type(argv[1]))
	{
		ft_clean(params);
		write(2, "Error\nWrong type of map file\n", 29);
		exit(0);
	}
	if ((fd = open(argv[1], O_RDONLY)) == -1)
	{
		ft_clean(params);
		write(2, "Error\nCan't open map file\n", 26);
		exit(0);
	}
	ft_error(ft_read_file(fd, flags, params), params);
	if (params->map->map_str == NULL)
	{
		ft_clean(params);
		write(2, "Error\nMap is empty\n", 19);
		exit(0);
	}
	ft_check_file(params, flags);
	ft_error(ft_map(params), params);
}

void	ft_screenshot_or_not(t_param *params, int argc)
{
	if (argc == 2)
	{
		if (ft_write_win(params))
		{
			ft_clean(params);
			write(2, "Error\nmlx error\n", 16);
			exit(0);
		}
	}
	else if (argc == 3)
	{
		params->config->screenshot = 1;
		if (ft_screenshot(params) == -1)
		{
			ft_clean(params);
			write(2, "Error\nCan't open or create file for screenshot\n", 47);
			exit(0);
		}
	}
}

void	ft_wrong_arg(t_param *params)
{
	write(2, "Error\n", 6);
	write(2, "Wrong number of arguments or the second argument\n", 49);
	ft_clean(params);
	exit(0);
}

int		main(int argc, char **argv)
{
	t_flags *flags;
	t_param *params;

	flags = &(t_flags){0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	params = &(t_param){&(t_win){NULL, NULL, 0, 0, NULL, NULL, 0, 0, 0},
		&(t_plr){0.0, 0.0, &(t_point){0.0, 0.0}, &(t_point){0.0, 0.0}, 0,
			&(t_point){0.0, 0.0}, &(t_point){0.0, 0.0}}, &(t_map){NULL, NULL,
				0, 0}, &(t_config){0, 0, NULL, NULL, NULL, NULL, NULL, -1, -1,
					-1, -1, -1, -1, 0, 0}, &(t_textures){&(t_tex){0, 0, NULL,
						NULL, 0, 0, 0}, &(t_tex){0, 0, NULL, NULL, 0, 0, 0},
					&(t_tex){0, 0, NULL, NULL, 0, 0, 0}, &(t_tex){0, 0, NULL,
						NULL, 0, 0, 0}, &(t_tex){0, 0, NULL, NULL, 0, 0, 0}},
					NULL, NULL, 0, 0, &(t_key){0, 0, 0, 0, 0, 0}};
	if ((argc == 2) || ((argc == 3) && (!(ft_strncmp(argv[2], "--save", 7)))))
	{
		ft_prepare_game(params, flags, argv);
		params->c_clr = create_trgb(0, params->config->cr, params->config->cg,
				params->config->cb);
		params->f_clr = create_trgb(0, params->config->fr, params->config->fg,
				params->config->fb);
		ft_screenshot_or_not(params, argc);
	}
	else
		ft_wrong_arg(params);
	return (0);
}
