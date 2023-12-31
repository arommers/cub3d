/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 09:04:11 by arommers      #+#    #+#                 */
/*   Updated: 2023/03/18 22:23:30 by adri          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	ft_checkset(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new;
	int		i;
	int		start;
	int		end;

	start = 0;
	while (s1[start] && ft_checkset(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_checkset(s1[end -1], set))
		end--;
	new = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (start < end)
	{
		new[i] = s1[start];
		i++;
		start++;
	}
	new[i] = '\0';
	return (new);
}

// int	main(void)
// {
// 	char const	str1[] = "";
// 	char const	str2[] = "\0";
// 	printf("%s\n", ft_strtrim(str1, str2));
// 	return (0);
// }