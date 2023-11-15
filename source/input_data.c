/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_data.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/13 17:20:00 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/11/15 11:33:31 by arommers      ########   odam.nl         */
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

t_input	*map_init(t_input *input, char *with_nl, t_file *file)
{
	int		i;
	char	*line;
	t_input	*temp;

	i = 1;
	input->map = malloc(sizeof(char *) * (file->lines_left + 1));
	temp = input;
	line = ft_strtrim(with_nl, "\n");
	free(with_nl);
	temp->map[0] = line;
	printf("temp->map[0] = %s\n", temp->map[0]);
	while (i < file->lines_left)
	{
		with_nl = get_next_line(file->fd);
		line = ft_strtrim(with_nl, "\n");
		free(with_nl);
		temp->map[i] = line;
		i++;
	}
	temp->map[i] = NULL;
	i = 0;
	while (temp->map[i] != NULL)
	{
		printf("temp->map[%d] = %s\n", i, temp->map[i]);
		i++;
	}
	return (input);
}

char	*init_input(t_input *input, t_file *file, char *line)
{
	int	count_line;

	count_line = 0;
	while (1)
	{
		line = get_next_line(file->fd);
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
	file->lines_left = file->file_lines - count_line;
	return (line);
}

void	input_data(int argc, char **argv, t_data *data)
{
	char	*line;
	t_file	*file;
	t_input	*temp;

	file = malloc(sizeof(t_file));
	temp = data->input;
	file->file_lines = line_counter(argv[1]);
	temp = initialize_data_struct(temp);
	file->fd = open(argv[1], O_RDONLY);
	line = init_input(temp, file, line);
	check_input_order(line, temp, file->lines_left);
	temp = map_init(temp, line, file);
	data->input = temp;
	check_input(data, file->lines_left);
}
