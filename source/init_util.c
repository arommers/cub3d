/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_util.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: adri <adri@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/19 09:44:50 by adri          #+#    #+#                 */
/*   Updated: 2023/11/20 11:56:23 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*  Sets all members of the walls array to NULL */

void	init_walls(t_wall *walls)
{
	int	i;

	i = 0;
	while (i < 4)
		walls[i++].tex = NULL;
}

/*  Sets the intial values of the line struct to 0*/

void	init_line(t_line *line)
{
	line->line_height = 0;
	line->draw_start = 0;
	line->draw_end = 0;
}

void	init_mlx(t_data *data)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	if (!data->mlx)
		ft_error(data, "MLX42 Error");
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img)
		ft_error(data, "MLX42 Error");
}
