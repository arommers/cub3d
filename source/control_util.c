/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psadeghi <psadeghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 21:00:59 by adri              #+#    #+#             */
/*   Updated: 2023/11/20 11:16:44 by psadeghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	move_up_down(mlx_key_data_t key, t_data *d, double move)
{
	t_player	*p;

	p = d->player;
	if (key.key == MLX_KEY_W && key.action == MLX_PRESS)
	{
		if (d->input->map[(int)(p->x + p->dirx * move)][(int)(p->y)] != '1')
			p->x += p->dirx * move;
		if (d->input->map[(int)(p->x)][(int)(p->y + p->diry * move)] != '1')
			p->y += p->diry * move;
	}
	if (key.key == MLX_KEY_S && key.action == MLX_PRESS)
	{
		if (d->input->map[(int)(p->x - p->dirx * move)][(int)(p->y)] != '1')
			p->x -= p->dirx * move;
		if (d->input->map[(int)(p->x)][(int)(p->y - p->diry * move)] != '1')
			p->y -= p->diry * move;
	}
}

void	move_left_right(mlx_key_data_t key, t_data *d, double move)
{
	t_player	*p;

	p = d->player;
	if (key.key == MLX_KEY_A && key.action == MLX_PRESS)
	{
		if (d->input->map[(int)(p->x - p->diry * move)][(int)(p->y)] != '1')
			p->x -= p->diry * move;
		if (d->input->map[(int)(p->x)][(int)(p->y + p->dirx * move)] != '1')
			p->y += p->dirx * move;
	}
	if (key.key == MLX_KEY_D && key.action == MLX_PRESS)
	{
		if (d->input->map[(int)(p->x + p->diry * move)][(int)(p->y)] != '1')
			p->x += p->diry * move;
		if (d->input->map[(int)(p->x)][(int)(p->y - p->dirx * move)] != '1')
			p->y -= p->dirx * move;
	}
}

void	rot_left_right(mlx_key_data_t key, t_data *d, double rot)
{
	t_player	*p;
	double		old_x;
	double		old_p_x;

	p = d->player;
	if (key.key == MLX_KEY_RIGHT && key.action == MLX_PRESS)
	{
		old_x = p->dirx;
		p->dirx = p->dirx * cos(-rot) - p->diry * sin(-rot);
		p->diry = old_x * sin(-rot) + p->diry * cos(-rot);
		old_p_x = p->planex;
		p->planex = p->planex * cos(-rot) - p->planey * sin(-rot);
		p->planey = old_p_x * sin(-rot) + p->planey * cos(-rot);
	}
	if (key.key == MLX_KEY_LEFT && key.action == MLX_PRESS)
	{
		old_x = p->dirx;
		p->dirx = p->dirx * cos(rot) - p->diry * sin(rot);
		p->diry = old_x * sin(rot) + p->diry * cos(rot);
		old_p_x = p->planex;
		p->planex = p->planex * cos(rot) - p->planey * sin(rot);
		p->planey = old_p_x * sin(rot) + p->planey * cos(rot);
	}
}

void	scroll_left(t_data *data, double rot)
{
	t_player	*p;
	double		old_x;
	double		old_p_x;

	p = data->player;
	old_x = p->dirx;
	old_p_x = p->planex;
	p->dirx = p->dirx * cos(-rot) - p->diry * sin(-rot);
	p->diry = old_x * sin(-rot) + p->diry * cos(-rot);
	p->planex = p->planex * cos(-rot) - p->planey * sin(-rot);
	p->planey = old_p_x * sin(-rot) + p->planey * cos(-rot);
}

void	scroll_right(t_data *data, double rot)
{
	t_player	*p;
	double		old_x;
	double		old_p_x;

	p = data->player;
	old_x = p->dirx;
	old_p_x = p->planex;
	p->dirx = p->dirx * cos(rot) - p->diry * sin(rot);
	p->diry = old_x * sin(rot) + p->diry * cos(rot);
	p->planex = p->planex * cos(rot) - p->planey * sin(rot);
	p->planey = old_p_x * sin(rot) + p->planey * cos(rot);
}
