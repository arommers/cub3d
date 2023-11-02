/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_loop.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: adri <adri@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/02 12:59:57 by adri          #+#    #+#                 */
/*   Updated: 2023/11/02 14:06:30 by adri          ########   odam.nl         */
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

void    prep_DDA_algo(t_ray *ray, t_player *player)
{
    ray->mapx = (int)player->x;
    ray->mapy = (int)player->y;

    if (ray->delta_dist_x == 0)
        ray->delta_dist_x = 1e30;
    else
        ray->delta_dist_x = sqrt(1 + (ray->diry * ray->diry) / (ray->dirx * ray->dirx));
    if (ray->delta_dist_y == 0)
        ray->delta dist_y = 1e30;
    else
        ray->delta_dist_y = sqrt(1 + (ray->dirx * ray->dirx) / (ray->diry * ray->diry));
    calc_start(ray, player);
    ray->wall = 0;
        
}

void    run_DDA_algo(t_data *data, t_ray *ray)
{
    while (!hit)
    {
        if (ray->init_dist_x < ray->init_dist_y)
        {
            ray->init_dist_x += ray->delta_dist_x;
            ray->mapx += ray->step_x;
            side = 0;
        }
        else
        {
            ray->init_dist_y += ray->delta_dist_y;
            ray->mapy += ray->step_y;
            side = 1;
        }
        if (data->map[ray->mapx][ray->mapy] == 1)
            wall = true;
    }
}


void    game_loop(t_data *data)
{
    int         i;
    t_player    *tmp_p;
    t_ray       *tmp_r;

    i = 0;
    tmp_p = data->player;
    tmp_r = data->ray;
    while (i < WIDTH)
    {
        tmp_r->camera_x = 2 * i / (double)WIDTH -1;
        tmp_r->raydir_x = tmp_p->dirx + tmp_p->planex * tmp_r->camera_x;
        tmp_r->raydir_y = tmp_p->diry + tmp_p->planey * tmp_r->camera_x;
        prep_DDA_algo(tmp_r, tmp_p);
        run_DDA_algo(data, tmp_r);
        i++;
    }
}