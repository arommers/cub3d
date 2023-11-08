/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 14:06:55 by arommers      #+#    #+#                 */
/*   Updated: 2023/03/18 22:23:09 by adri          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*ns1;
	unsigned char	*ns2;

	ns1 = (unsigned char *)s1;
	ns2 = (unsigned char *)s2;
	i = 0;
	if (n == 0 || ns1 == ns2)
		return (0);
	while ((i < n) && ns1[i] != '\0' && ns2[i] != '\0')
	{
		if (ns1[i] != ns2[i])
			return (ns1[i] - ns2[i]);
		i++;
	}
	if (ns1[i] != ns2[i] && i != n)
		return (ns1[i] - ns2[i]);
	return (0);
}

/*
int	main(void)
{
	char	*str1;
	char	*str2;
	size_t	i;

	str1 = "bulbasaur";
	str2 = "bulbasaur";
	i = 8;
	printf("%d\n", ft_strncmp(str1, str2, i));
	printf("%d\n", strncmp(str1, str2, i));
	return (0);
}
*/