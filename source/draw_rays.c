/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_rays.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: adri <adri@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/02 16:01:04 by adri          #+#    #+#                 */
/*   Updated: 2023/11/02 21:28:58 by adri          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void    prep_wall_draw(t_ray *ray)
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

void    draw_wall(t_data *data, int x, int start, int end)
{
    int color;
    int mapValue = data->map[data->ray->mapx][data->ray->mapy];
    
    if (mapValue == 1)
        color = 0xFF0000; // Red
    else if (mapValue == 2)
        color = 0x00FF00; // Green
    else if (mapValue == 3)
        color = 0x0000FF; // Blue
    else if (mapValue == 4)
        color = 0xFFFFFF; // White
    else
        color = 0xFFFF00; // Yellow (default)

    if (data->ray->side == 1) 
        color = (color >> 1) & 0x7F7F7F; // Reduce intensity for side walls
    
    for (int y = start; y <end; y++)
        mlx_put_pixel(data->img, x, y, color);
}