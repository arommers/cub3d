/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_walls.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: adri <adri@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/02 16:01:04 by adri          #+#    #+#                 */
/*   Updated: 2023/11/08 11:48:38 by arommers      ########   odam.nl         */
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

unsigned int	get_pixel(mlx_texture_t	*t, int32_t x, int32_t y)
{
	int	r;
	int	g;
	int	b;

	r = t->pixels[(y * t->width + x) * t->bytes_per_pixel];
	g = t->pixels[(y * t->width + x) * t->bytes_per_pixel + 1];
	b = t->pixels[(y * t->width + x) * t->bytes_per_pixel + 2];
	
	return ((unsigned int)(r << 24 | g << 16 | b << 8 | 0xFF));
}

// Calculate the x coordinate of our texture from where the ray hits the wall

void	put_texture(t_data *data, int x, int start, int end)
{
	int		tex_x; // x coordinate of the texture
	double	wall_hit; // coordinate where the wall was hit, either x on a horo line or y on a vert line

	load_textures(data);
	// Calculate the value of wall_hit
	if (data->ray->side == 0)   // a vertical line is hit
		wall_hit = data->player->y + data->ray->perp_wall_dist * data->ray->diry;
	else    // a horizontal line is hit
		wall_hit = data->player->x + data->ray->perp_wall_dist * data->ray->dirx;
	wall_hit -= floor(wall_hit);

	// determine the x coordinate of the texture and mirror the location if necessary
	tex_x = (int)(wall_hit * (double)TEXW);
	if (data->ray->side == 0 && data->ray->dirx > 0)
		tex_x =  TEXW - tex_x - 1;
	if (data->ray->side == 1 && data->ray->diry < 0)
		tex_x =  TEXW - tex_x - 1;

	int32_t	color;
	int		tex_y; // y coordinate of the texture
	double	step; // determines our increment
	double	tex_start; // initial texture coordinate

	step = 1.0 * TEXH / data->ray->line->line_height;
	tex_start = (start - HEIGHT / 2 + data->ray->line->line_height / 2) * step;
	int y = start;
	while (y < end)
	{
		tex_y = (int)tex_start & (TEXH - 1);
		tex_start += step;
		color = get_pixel(check_side(data), tex_x, tex_y);
		if (data->ray->side == 1)
			color *= 0.75;
		mlx_put_pixel(data->img, x, y, color);
		y++;
	}
}

// void	draw_wall(t_data *data, int x, int start, int end)
// {
// 	int color;
// 	char mapValue;
	
// 	mapValue = data->input->map[data->ray->mapx][data->ray->mapy];
// 	if (mapValue == '1')
// 		color = ft_pixel(0, 255, 255, 255);  //red
// 	else if (mapValue == '2')
// 		color = ft_pixel(0, 255, 0, 255); //green
// 	else if (mapValue == '3')
// 		color = ft_pixel(0, 0, 255, 255); //blue
// 	else if (mapValue == '4')
// 		color = ft_pixel(255, 105, 180, 255); //pink
// 	else
// 		color = ft_pixel(255, 255, 0, 255); //yellow
// 	if (data->ray->side == 1) 
// 		color = color / 2; // Reduce intensity for side walls
// 	while (start < end)
// 		mlx_put_pixel(data->img, x, start++, color);
// }
