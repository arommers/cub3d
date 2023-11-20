/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_loop.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: adri <adri@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/02 12:59:57 by adri          #+#    #+#                 */
/*   Updated: 2023/11/20 10:48:56 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*	- Sets the perp_wall_dist based on which the side of the wall is hit
	- Vertical (side 0) or horizontal (side 1) */

void	calc_ray_length(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->init_dist_x - ray->delta_dist_x);
	else
		ray->perp_wall_dist = (ray->init_dist_y - ray->delta_dist_y);
}

/*	- Sets up the initial values for the DDA algorithm
	  based on the direction of the ray and the player's position
	- Determines the step direction (stepx and stepy)
	- Calculates the initial distances (init_dist_x and init_dist_y)
	  for the DDA algorithm based on the direction of the ray
	  and the player's position.*/

void	calc_start(t_ray *ray, t_player *player)
{
	if (ray->dirx < 0)
	{
		ray->stepx = -1;
		ray->init_dist_x = (player->x - ray->mapx) * ray->delta_dist_x;
	}
	else
	{
		ray->stepx = 1;
		ray->init_dist_x = (ray->mapx + 1.0 - player->x) * ray->delta_dist_x;
	}
	if (ray->diry < 0)
	{
		ray->stepy = -1;
		ray->init_dist_y = (player->y - ray->mapy) * ray->delta_dist_y;
	}
	else
	{
		ray->stepy = 1;
		ray->init_dist_y = (ray->mapy + 1.0 - player->y) * ray->delta_dist_y;
	}
}

/*	- Prepares the variables necessary for the DDA algorithm
	- Set the initial map coordinates based on the player's position
	- Ensure non-zero values for delta_dist_x and y to avoid division by zero */

void	prep_dda_algo(t_ray *ray, t_player *player)
{
	ray->mapx = (int)player->x;
	ray->mapy = (int)player->y;
	if (ray->delta_dist_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->dirx);
	if (ray->delta_dist_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->diry);
	calc_start(ray, player);
	ray->wall = 0;
}

/*	- Implemnets the DDA) algorithm to determine the distance
	  to the nearest wall in the ray's path
	- Updates the ray's position (init_dist_x or y)
	  based on the side with the shorter distance
	- Stops when it encounters a wall */

void	run_dda_algo(t_data *data, t_ray *ray)
{
	while (!ray->wall)
	{
		if (ray->init_dist_x < ray->init_dist_y)
		{
			ray->init_dist_x += ray->delta_dist_x;
			ray->mapx += ray->stepx;
			ray->side = 0;
		}
		else
		{
			ray->init_dist_y += ray->delta_dist_y;
			ray->mapy += ray->stepy;
			ray->side = 1;
		}
		if (data->input->map[ray->mapx][ray->mapy] == '1'
				|| data->input->map[ray->mapx][ray->mapy] == '2')
			ray->wall = 1;
	}
	calc_ray_length(ray);
}

/*	- The main loop for rendering the game
	- It iterates through each x coordinate of the screen
	- Calculates the ray direction based on the player's view
	- Performs the DDA algorithm for each individual ray
	- Prepares the data for drawing the walls
	- Draws the vertical column one at a time */

void	game_loop(void *param)
{
	t_data		*data;
	t_player	*p;
	t_ray		*r;

	data = param;
	p = data->player;
	r = data->ray;
	data->x = 0;
	while (data->x < WIDTH)
	{
		r->camera_x = 2 * data->x / (double)WIDTH -1;
		r->dirx = p->dirx + p->planex * r->camera_x;
		r->diry = p->diry + p->planey * r->camera_x;
		prep_dda_algo(r, p);
		run_dda_algo(data, r);
		prep_wall_draw(r);
		prep_vert_line(data, data->x, r->line->draw_start, r->line->draw_end);
		data->x++;
	}
}
