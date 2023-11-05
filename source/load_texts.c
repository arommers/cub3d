/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   load_texts.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: adri <adri@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/05 13:52:04 by adri          #+#    #+#                 */
/*   Updated: 2023/11/05 20:58:06 by adri          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void    load_textures(t_data *data)
{
    data->walls->path = "./textures/test.png";
    data->walls->tex = mlx_load_png(data->walls->path);
}