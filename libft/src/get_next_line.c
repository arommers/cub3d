/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/22 11:47:30 by psadeghi      #+#    #+#                 */
/*   Updated: 2022/11/24 15:29:13 by psadeghi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*read_and_save(int fd, char *stash)
{
	char	buffer[BUFFER_SIZE + 1];
	int		read_bytes;

	read_bytes = 1;
	while (!find_char(stash, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1 || (read_bytes == 0 && !ft_strlen(stash)))
			return (free(stash), NULL);
		buffer[read_bytes] = '\0';
		stash = join_stash_and_buffer(stash, buffer);
		if (!stash)
			return (NULL);
	}
	return (stash);
}

char	*print_line(char	*stash)
{
	char	*line;
	int		i;

	i = 0;
	if (!stash)
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	line = ft_substr_gnl(stash, 0, i + 1);
	return (line);
}

char	*get_new_stash(char *stash)
{
	int		i;
	char	*new_stash;

	i = 0;
	if (!stash)
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	new_stash = ft_substr_gnl(stash, i + 1, (ft_strlen(stash) - i + 1));
	return (free(stash), new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_and_save(fd, stash);
	if (!stash)
		return (NULL);
	line = print_line(stash);
	if (!line)
		return (free(stash), NULL);
	stash = get_new_stash(stash);
	if (!stash)
		return (free(line), NULL);
	return (line);
}

/*
int	main()
{
	int fd;
	char	*tmp;

	fd = open("paris.txt", O_RDONLY);
	while((tmp = get_next_line(fd)))
	{
		printf("%s", tmp);
		//printf("%s", get_next_line(fd));
		//printf("%s", get_next_line(fd));
		//printf("%s", get_next_line(fd));
		free(tmp);
	}
	close(fd);
	system("leaks a.out");
}
*/