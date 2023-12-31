/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/17 08:44:25 by arommers      #+#    #+#                 */
/*   Updated: 2023/03/18 22:18:17 by adri          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	i;

	i = 0;
	ptr = malloc (count * size);
	if (ptr == NULL)
		return (NULL);
	while (i < (count * size))
	{
		(*(unsigned char *)(ptr + i)) = 0;
			i++;
	}
	return (ptr);
}

/*void	*ft_calloc(size_t count, size_t size);

int	main(void)
{
	char	*str = ft_calloc (3, sizeof(int));
	unsigned int	i;

	i = 0;
	while (i < 12)
	{
		printf("%c", str[i]);
		i++;
	}
	free (str);
	return (0);
}
*/