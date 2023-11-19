/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_walls.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: adri <adri@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/02 16:01:04 by adri          #+#    #+#                 */
/*   Updated: 2023/11/19 21:37:39 by adri          ########   odam.nl         */
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

/*	Calculate the x coordinate of our texture from where the ray hits the wall.
	If necessary the x coordinate of the texture is mirrored
	- x  		= coordinate of the texture
	- hit	= coordinate where the wall was hit, either x on a horo line or y on a vert line */

void	prep_vert_line(t_data *data, int x, int start, int end)
{
	t_ray	*r;
	int		tex_x;
	double	hit;

	r = data->ray;
	if (r->side == 0)
		hit = data->player->y + r->perp_wall_dist * r->diry;
	else
		hit = data->player->x + r->perp_wall_dist * r->dirx;
	hit -= floor(hit);

	tex_x = (int)(hit * (double)TEXW);
	if (r->side == 0 && r->dirx > 0)
		tex_x = TEXW - tex_x - 1;
	if (r->side == 1 && r->diry < 0)
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
	int		tex_y;
	double	step;
	double	tex_start;

	step = 1.0 * TEXH / data->ray->line->line_height;
	tex_start = (start - HEIGHT / 2 + data->ray->line->line_height / 2) * step;
	data->y = start;
	put_ceiling(data, data->x, start);
	while (data->y < end)
	{
		tex_y = (int)tex_start & (TEXH - 1);
		tex_start += step;
		color = get_pixel(check_side(data), tex_x, tex_y);
		mlx_put_pixel(data->img, data->x, data->y, color);
		data->y++;
	}
	put_floor(data, data->x, end, HEIGHT);
}
