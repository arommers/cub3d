/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/17 11:28:19 by arommers      #+#    #+#                 */
/*   Updated: 2023/03/18 22:21:47 by adri          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dst;
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(s1) + 1;
	dst = (char *) malloc(j);
	if (dst == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

/*int	main(void)
{
	char str[] = "jovanka";
	printf("%s\n", ft_strdup(str));
	printf("%s\n", strdup(str));
	return(0);
}
*/
