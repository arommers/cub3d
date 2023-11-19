/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_util.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: adri <adri@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/19 09:44:50 by adri          #+#    #+#                 */
/*   Updated: 2023/11/19 10:59:18 by adri          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void    init_walls(t_wall *walls)
{
    int i;

    i = 0;
    while (i < 4)
        walls[i++].tex = NULL;
}

void	init_line(t_line *line)
{
	line->line_height = 0;
	line->draw_start = 0;
	line->draw_end = 0;
}