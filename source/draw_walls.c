/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_walls.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: adri <adri@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/02 16:01:04 by adri          #+#    #+#                 */
/*   Updated: 2023/11/03 11:17:36 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	prep_wall_draw(t_ray *ray)
{
	t_line *tmp;

	tmp = ray->line;
	tmp->line_height = (int)(HEIGHT / ray->perp_wall_dist);
	tmp->draw_start = ((tmp->line_height * -1) / 2) + (HEIGHT / 2);
	if (tmp->draw_start < 0)
		tmp->draw_start = 0;
	tmp->draw_end = (int)((tmp->line_height / 2) + (HEIGHT / 2));
	if (tmp->draw_end >= HEIGHT)
		tmp->draw_end = HEIGHT -1;
}

void	draw_wall(t_data *data, int x, int start, int end)
{
	int color;
	int mapValue = data->map[data->ray->mapx][data->ray->mapy];
	
	if (mapValue == 1)
		color = ft_pixel(255, 0, 0, 255);  
	else if (mapValue == 2)
		color = ft_pixel(0, 255, 0, 255); //green
	else if (mapValue == 3)
		color = ft_pixel(0, 0, 255, 255); //blue
	else if (mapValue == 4)
		color = ft_pixel(255, 108, 125, 255); //white
	else
		color = ft_pixel(255, 255, 0, 255); //yellow

	if (data->ray->side == 1) 
		color = color / 2; // Reduce intensity for side walls
	while (start < end)
		mlx_put_pixel(data->img, x, start++, color);
}