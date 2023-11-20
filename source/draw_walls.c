/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psadeghi <psadeghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:01:04 by adri              #+#    #+#             */
/*   Updated: 2023/11/20 11:13:12 by psadeghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*	- Calculates the line height based on the perpendicular wall distance
	- Determines the starting and ending positions on the screen
	  where the wall should be drawn.
	- We make sure these positions are within the bounds of the screen. */

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

/*	- Preps the data for drawing a vertical line on the screen
	  based on the wall hit during the raycasting process.
	- Calculates the texture coordinates based on the hit point of the ray
	  with the wall and adjusts them based on
	  which side and direction of the wal was hit */

void	prep_vert_line(t_data *data, int start, int end)
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

/*	- Fill a vert line of pixels for the passed x coord of the screen
	- We determine how many pixels in our texture we need to increment
	  based on the lineheight and stores this in 'step'
	- We determine where we start drawing the texture pixels
	  in our screen image
	- We fill the screen up until start with ceiling pixels
	- We retreive pixels from the corresponding texture
	  and put them in the screen image
	- We fill the rest of the vertical line with floor pixels */

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
