/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_screenshot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odomenic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 18:36:20 by odomenic          #+#    #+#             */
/*   Updated: 2021/03/23 20:22:39 by odomenic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_fill_bmp_header(t_param *prms, unsigned char *bmp)
{
	bmp[0] = 'B';
	bmp[1] = 'M';
	bmp[2] = (unsigned char)prms->win->width * prms->win->height + 54;
	bmp[3] = (unsigned char)((prms->win->width * prms->win->height + 54) >> 8);
	bmp[4] = (unsigned char)((prms->win->width * prms->win->height + 54) >> 16);
	bmp[5] = (unsigned char)((prms->win->width * prms->win->height + 54) >> 24);
	bmp[10] = 54;
	bmp[14] = 40;
	bmp[18] = (unsigned char)prms->win->width;
	bmp[19] = (unsigned char)(prms->win->width >> 8);
	bmp[20] = (unsigned char)(prms->win->width >> 16);
	bmp[21] = (unsigned char)(prms->win->width >> 24);
	bmp[22] = (unsigned char)prms->win->height;
	bmp[23] = (unsigned char)(prms->win->height >> 8);
	bmp[24] = (unsigned char)(prms->win->height >> 16);
	bmp[25] = (unsigned char)(prms->win->height >> 24);
	bmp[26] = 1;
	bmp[28] = (unsigned char)prms->win->bpp;
}

void	ft_fill_bmp(t_param *prms, int fd)
{
	int	i;
	int	j;
	int	color;

	i = prms->win->height - 1;
	while (i >= 0)
	{
		j = 0;
		while (j < prms->win->width)
		{
			color = *(unsigned int*)(prms->win->addr + (i * prms->win->line_l +
						j * (prms->win->bpp / 8)));
			write(fd, &color, 4);
			j++;
		}
		i--;
	}
}

int		ft_screenshot(t_param *prms)
{
	int				fd;
	unsigned char	bmp_header[54];
	int				i;

	if ((fd = open("cub3D.bmp", O_CREAT | O_RDWR | O_TRUNC, S_IRWXU)) == -1)
		return (-1);
	ft_init_win(prms);
	i = 0;
	while (i < 54)
	{
		bmp_header[i] = (unsigned char)0;
		i++;
	}
	ft_fill_bmp_header(prms, bmp_header);
	write(fd, bmp_header, 54);
	ft_raycasting(prms);
	ft_fill_bmp(prms, fd);
	close(fd);
	return (0);
}
