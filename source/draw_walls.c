/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_walls.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: adri <adri@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/02 16:01:04 by adri          #+#    #+#                 */
/*   Updated: 2023/11/05 21:13:57 by adri          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int32_t get_pixel(mlx_texture_t *texture, int32_t x, int32_t y)
{
    // Calculate the index of the pixel in the pixels array
    int32_t    index;
    
    index = (y * texture->width + x) * texture->bytes_per_pixel;

    // Extract the color components
    int8_t red = texture->pixels[index];
    int8_t green = texture->pixels[index + 1];
    int8_t blue = texture->pixels[index + 2];
    int8_t alpha = texture->pixels[index + 3];

    // Combine the color components into a single uint32_t value
    return (alpha << 24) | (red << 16) | (green << 8) | blue;
}

void    prep_wall_draw(t_ray *ray)
{
    t_line *tmp;

    tmp = ray->line;
    tmp->line_height = (int)(HEIGHT / ray->perp_wall_dist);
    tmp->draw_start = ((tmp->line_height * -1) / 2) + (HEIGHT / 2);
    if (tmp->draw_start < 0)
        tmp->draw_start = 0;
    tmp->draw_end = (int)((tmp->line_height / 2) + (HEIGHT / 2));
    if (tmp->draw_end >= HEIGHT)
        tmp->draw_end = HEIGHT -1;
}

// Calculate the x coordinate of our texture from where the ray hits the wall

void    put_texture(t_data *data, int x, int start, int end)
{
    int     tex_x; // x coordinate of the texture
    double  wall_hit; // coordinate where the wall was hit, either x on a horo line or y on a vert line

    
    // Calculate the value of wall_hit
    if (data->ray->side == 0)   // a vertical line is hit
        wall_hit = data->player->y + data->ray->perp_wall_dist * data->ray->diry;
    else    // a horizontal line is hit
        wall_hit = data->player->x + data->ray->perp_wall_dist * data->ray->dirx;
    wall_hit -= floor(wall_hit);

    // determine the x coordinate of the texture and mirror the location if necessary
    tex_x = (int)(wall_hit * (double)TEXW);
    if (data->ray->side == 0 && data->ray->dirx > 0)
        tex_x =  TEXW - tex_x - 1;
    if (data->ray->side == 1 && data->ray->diry < 0)
        tex_x =  TEXW - tex_x - 1;

    int32_t color;
    int     tex_y; // y coordinatie of the texture
    double  step; // determines our increment
    double  tex_start; // initial texture coordinate

    step = 1.0 * TEXH / data->ray->line->line_height;
    tex_start = (start - HEIGHT / 2 + data->ray->line->line_height / 2) * step;
    while (start < end)
    {
        tex_y = (int)start & (TEXH - 1);
        tex_start += step;
        color = get_pixel(data->walls->tex, tex_x, tex_y);
        if (data->ray->side == 1)
            color = color / 2;
        mlx_put_pixel(data->img, x, start, color);
        start++;
    }    
}


// void    draw_wall(t_data *data, int x, int start, int end)
// {
//     int color;
//     int mapValue = data->map[data->ray->mapx][data->ray->mapy];
    
//     if (mapValue == 1)
//         color = ft_pixel(0, 255, 255, 255);  //red
//     else if (mapValue == 2)
//         color = ft_pixel(0, 255, 0, 255); //green
//     else if (mapValue == 3)
//         color = ft_pixel(0, 0, 255, 255); //blue
//     else if (mapValue == 4)
//         color = ft_pixel(255, 105, 180, 255); //pink
//     else
//         color = ft_pixel(255, 255, 0, 255); //yellow
//     if (data->ray->side == 1) 
//         color = color / 2; // Reduce intensity for side walls
//     while (start < end)
//         mlx_put_pixel(data->img, x, start++, color);
// }