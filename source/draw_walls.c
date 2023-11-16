/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_walls.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: adri <adri@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/02 16:01:04 by adri          #+#    #+#                 */
/*   Updated: 2023/11/16 15:31:49 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	prep_wall_draw(t_ray *ray)
{
	t_line	*tmp;

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

	return ((unsigned int)(r << 24 | g << 16 | b << 8 | 255));
}

/*	Fill in the celing color pixels on the x coordinate of the screen 
	until the start of the texture */

void	put_ceiling(t_data *data, int x, int start)
{
	int		y;
	int32_t	color;

	y = 0;
	color = ft_pixel(data->input->c_r, data->input->c_g, data->input->c_b, 255);
	while (y < start)
		mlx_put_pixel(data->img, x, y++, color);
}

/*	Fill in the floor color pixels on the x coordinate of the screen 
	from the end of the texture untill the bottom */

void	put_floor(t_data *data, int x, int start, int height)
{
	int32_t	color;

	color = ft_pixel(data->input->f_r, data->input->f_g, data->input->f_b, 255);
	while (start < height)
		mlx_put_pixel(data->img, x, start++, color);
}

/*	Calculate the x coordinate of our texture from where the ray hits the wall.
	If necessary the x coordinate of the texture is mirrored
	- x  		= coordinate of the texture
	- wall hit	= coordinate where the wall was hit, either x on a horo line or y on a vert line */

void	prep_vert_line(t_data *data, int x, int start, int end)
{
	int		tex_x; // x coordinate of the texture
	double	wall_hit; // coordinate where the wall was hit, either x on a horo line or y on a vert line

	// Calculate the value of wall_hit
	if (data->ray->side == 0)   // a vertical line is hit
		wall_hit = data->player->y + data->ray->perp_wall_dist * data->ray->diry;
	else    // a horizontal line is hit
		wall_hit = data->player->x + data->ray->perp_wall_dist * data->ray->dirx;
	wall_hit -= floor(wall_hit);

	// determine the x coordinate of the texture and mirror the location if necessary
	tex_x = (int)(wall_hit * (double)TEXW);
	if (data->ray->side == 0 && data->ray->dirx > 0)
		tex_x = TEXW - tex_x - 1;
	if (data->ray->side == 1 && data->ray->diry < 0)
		tex_x = TEXW - tex_x - 1;
	put_vert_line(data, start, end, tex_x);
}

/*	Fill in a vertical line of pixels for the passed x coordinate of the screen
	- First we determine how many pixels in our texture we need to increment based on the lineheigh.
	  This is stored in 'step'
	- Then we determine where we start drawing the texture pixels in our screen image
	- We fill the screen up until start with ceiling pixels
	- We retreive pixels from the corresponding texture and put them in the screen image
	- We fill the rest of the vertical line with floor pixels*/

void	put_vert_line(t_data *data, int start, int end, int tex_x)
{
	int32_t	color;
	int		tex_y; // y coordinate of the texture
	double	step; // determines our increment
	double	tex_start; // initial texture coordinate

	step = 1.0 * TEXH / data->ray->line->line_height;
	tex_start = (start - HEIGHT / 2 + data->ray->line->line_height / 2) * step;
	int y = start;
	// put_ceiling(data, data->x, start);
	while (y < end)
	{
		tex_y = (int)tex_start & (TEXH - 1);
		tex_start += step;
		color = get_pixel(check_side(data), tex_x, tex_y);
		// if (data->ray->side == 1)
		// 	color *= 0.75;
		mlx_put_pixel(data->img, data->x, y, color);
		y++;
	}
	// put_floor(data, data->x, end, HEIGHT);
}

// Draw al the walls by putting pixels where our rays hit the walls.

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
