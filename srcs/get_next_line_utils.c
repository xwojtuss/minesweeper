/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:08:59 by wkornato          #+#    #+#             */
/*   Updated: 2024/12/21 11:15:00 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*find_newline(char *string)
{
	int	i;

	if (!string)
		return (NULL);
	i = 0;
	while (string[i] != '\n' && string[i] != '\0')
		i++;
	if (string[i] == '\n')
		return (string);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	length;
	char	*string;
	char	*ptr;

	length = strlen(s1) + strlen(s2);
	string = (char *)malloc((length + 1) * sizeof(char));
	if (!string)
		return (NULL);
	ptr = string;
	while (*s1)
	{
		*string = *s1;
		string++;
		s1++;
	}
	while (*s2)
	{
		*string = *s2;
		string++;
		s2++;
	}
	*string = '\0';
	return (ptr);
}