/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 09:22:49 by arommers      #+#    #+#                 */
/*   Updated: 2023/03/18 22:21:05 by adri          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*str;
	unsigned char	d;
	size_t			i;

	str = (unsigned char *)b;
	d = (unsigned char)c;
	i = 0;
	while (i < len)
	{
		str[i] = d;
			i++;
	}
	return (b);
}

/*int	main(void)
{
	char	str[] = "jovanka";
	printf("%s\n", ft_memset(str, 'X', 5));
	printf("%s\n", memset(str, 'X', 5));
	return (0);
}*/