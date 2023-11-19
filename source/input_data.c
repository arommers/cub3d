/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_data.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/13 17:20:00 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/11/19 22:03:35 by adri          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_input	*texture_color_init(t_input *input, char *with_nl)
{
	char	*line;

	line = ft_strtrim(with_nl, "\n");
	if (line[0] == 'F' || line[0] == 'C')
	{
		input = f_c_colors(input, line);
	}
	else
	{
		input = texture_data(input, line);
	}
	free(line);
	return (input);
}

t_input	*map_init(t_input *input, char *with_nl)
{
	int		i;
	char	*line;
	t_input	*temp;

	i = 1;
	input->map = malloc(sizeof(char *) * (input->file->lines_left + 1));
	temp = input;
	line = ft_strtrim(with_nl, "\n");
	free(with_nl);
	temp->map[0] = line;
	while (i < temp->file->lines_left)
	{
		with_nl = get_next_line(temp->file->fd);
		line = ft_strtrim(with_nl, "\n");
		free(with_nl);
		temp->map[i] = line;
		i++;
	}
	temp->map[i] = NULL;
	i = 0;
	while (temp->map[i] != NULL)
		i++;
	return (input);
}

char	*init_input(t_input *input, char *line)
{
	int	count_line;

	count_line = 0;
	while (1)
	{
		line = get_next_line(input->file->fd);
		if (!line)
			break ;
		if (strcmp(line, "\n") == 0)
		{
			count_line++;
			free(line);
			continue ;
		}
		if ((line[0] >= 'C' && line[0] <= 'W'))
		{
			count_line++;
			input = texture_color_init(input, line);
		}
		else
			break ;
		free(line);
	}
	input->file->lines_left = input->file->file_lines - count_line;
	return (line);
}

void	input_data(char **argv, t_data *data)
{
	char	*line;
	t_input	*temp;

	line = NULL;
	data->input->file = malloc(sizeof(t_file));
	data->input->file->file_lines = line_counter(argv[1]);
	temp = data->input;
	temp = initialize_data_struct(temp);
	data->input->file->fd = open(argv[1], O_RDONLY);
	line = init_input(temp, line);
	check_input_order(line, temp);
	temp = map_init(temp, line);
	data->input = temp;
	check_input(data, data->input->file->lines_left);
}
