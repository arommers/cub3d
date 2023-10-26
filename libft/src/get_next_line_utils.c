/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/22 11:48:06 by psadeghi      #+#    #+#                 */
/*   Updated: 2022/11/24 15:07:03 by psadeghi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*find_char(char *str, char p)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] != '\0' && str[i] != p)
		i++;
	if (str[i] == p)
		return (str);
	return (NULL);
}

char	*join_stash_and_buffer(char *stash, char *buffer)
{
	char	*new_stash;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!stash)
	{
		stash = malloc (1);
		if (!stash)
			return (free(stash), NULL);
		stash[0] = '\0';
	}
	new_stash = malloc(ft_strlen(stash) + ft_strlen(buffer) + 1);
	if (!new_stash || !buffer)
		return (free(stash), NULL);
	while (stash[i] != '\0')
	{
		new_stash[i] = stash[i];
		i++;
	}
	while (buffer[j] != '\0')
		new_stash[i++] = buffer[j++];
	new_stash[i] = '\0';
	return (free(stash), new_stash);
}

char	*ft_substr_gnl(char	*s, unsigned int start, size_t	len)
{
	char	*ns;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	if ((size_t)start > ft_strlen(s))
		return (ft_strdup_gnl(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen (s) - start;
	ns = (char *)malloc(sizeof(char) * (len + 1));
	if (!ns)
		return (NULL);
	i = start;
	j = 0;
	while (i < ft_strlen(s) && j < len)
		ns[j++] = s[i++];
	ns[j] = '\0';
	return (ns);
}

char	*ft_strdup_gnl(char *str)
{
	char	*dst;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	dst = malloc(ft_strlen(str) + 1);
	if (!dst)
		return (NULL);
	while (str[i])
	{
		dst[i] = str[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
