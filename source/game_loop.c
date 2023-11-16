/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_loop.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: adri <adri@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/02 12:59:57 by adri          #+#    #+#                 */
/*   Updated: 2023/11/16 12:44:01 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

void	calc_ray_length(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->init_dist_x - ray->delta_dist_x);
	else
		ray->perp_wall_dist = (ray->init_dist_y - ray->delta_dist_y);
}

void	prep_dda_algo(t_ray *ray, t_player *player)
{
	ray->mapx = (int)player->x;
	ray->mapy = (int)player->y;

	if (ray->delta_dist_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->dirx);
		// ray->delta_dist_x = sqrt(1 + (ray->diry * ray->diry) / (ray->dirx * ray->dirx));
	if (ray->delta_dist_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->diry);
		// ray->delta_dist_y = sqrt(1 + (ray->dirx * ray->dirx) / (ray->diry * ray->diry));
	calc_start(ray, player);
	ray->wall = 0;
}

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

void	game_loop(void *param)
{
	t_data		*data;
	t_player	*p;
	t_ray		*r;

	data = param;
	p = data->player;
	r = data->ray;
	data->x = 0;
	// draw_background(data);
	while (data->x < WIDTH)
	{
		r->camera_x = 2 * data->x / (double)WIDTH -1;
		r->dirx = p->dirx + p->planex * r->camera_x;
		r->diry = p->diry + p->planey * r->camera_x;
		prep_dda_algo(r, p);
		run_dda_algo(data, r);
		prep_wall_draw(r);
		//draw_wall(data, x, r->line->draw_start, r->line->draw_end);
		prep_vert_line(data, data->x, r->line->draw_start, r->line->draw_end);
		data->x++;
	}
}