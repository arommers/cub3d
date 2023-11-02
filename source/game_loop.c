/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_loop.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: adri <adri@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/02 12:59:57 by adri          #+#    #+#                 */
/*   Updated: 2023/11/02 21:26:07 by adri          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void    calc_start(t_ray *ray, t_player *player)
{
    if (ray->dirx < 0)
    {
        ray->stepx = -1;
        ray->init_dist_x =(player->x - ray->mapx) * ray->delta_dist_x;
    }
    else
    {
        ray->stepx = 1;
        ray->init_dist_x = (ray->mapx + 1.0 - player->x) * ray->delta_dist_x;
    }
    if (ray->diry < 0)
    {
        ray->stepy = -1;
        ray->init_dist_y =(player->y - ray->mapy) * ray->delta_dist_y;
    }
    else
    {
        ray->stepy = 1;
        ray->init_dist_y = (ray->mapy + 1.0 - player->y) * ray->delta_dist_y;
    }
}

void    calc_ray_length(t_ray *ray)
{
    if (ray->side == 0)
        ray->perp_wall_dist = (ray->init_dist_x - ray->delta_dist_x);
    else
        ray->perp_wall_dist = (ray->init_dist_y - ray->delta_dist_y);
}

void    prep_DDA_algo(t_ray *ray, t_player *player)
{
    ray->mapx = (int)player->x;
    ray->mapy = (int)player->y;

    if (ray->delta_dist_x == 0)
        ray->delta_dist_x = 1e30;
    else
        ray->delta_dist_x = sqrt(1 + (ray->diry * ray->diry) / (ray->dirx * ray->dirx));
    if (ray->delta_dist_y == 0)
        ray->delta_dist_y = 1e30;
    else
        ray->delta_dist_y = sqrt(1 + (ray->dirx * ray->dirx) / (ray->diry * ray->diry));
    calc_start(ray, player);
    ray->wall = 0;
        
}

void    run_DDA_algo(t_data *data, t_ray *ray)
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
        if (data->map[ray->mapx][ray->mapy] == 1)
            ray->wall = true;
    }
    calc_ray_length(ray);
}


void    game_loop(void *param)
{
    int         i;
    t_data      *data;
    t_player    *tmp_p;
    t_ray       *tmp_r;

    i = 0;
    data = param;
    tmp_p = data->player;
    tmp_r = data->ray;
    while (i < WIDTH)
    {
        tmp_r->camera_x = 2 * i / (double)WIDTH -1;
        tmp_r->dirx = tmp_p->dirx + tmp_p->planex * tmp_r->camera_x;
        tmp_r->diry = tmp_p->diry + tmp_p->planey * tmp_r->camera_x;
        prep_DDA_algo(tmp_r, tmp_p);
        run_DDA_algo(data, tmp_r);
        prep_wall_draw(tmp_r);
        draw_wall(data, tmp_r->camera_x, tmp_r->line->draw_start, tmp_r->line->draw_end);
        i++;
    }
}