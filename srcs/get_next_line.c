/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 21:13:37 by wkornato          #+#    #+#             */
/*   Updated: 2024/12/21 11:49:28 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*shift_buffer(char *static_buffer, int *i)
{
	int		j;
	int		new_len;
	char	*shifted_buffer;

	new_len = strlen(static_buffer) - *i;
	if (new_len <= 1)
		return (NULL);
	shifted_buffer = calloc(new_len, sizeof(char));
	if (!shifted_buffer)
		return (NULL);
	(*i)++;
	j = 0;
	while (static_buffer[*i])
		shifted_buffer[j++] = static_buffer[(*i)++];
	return (shifted_buffer);
}

char	*read_and_append(char *static_buffer, char *read_buffer, int fd)
{
	int		bytes;
	char	*temp;

	bytes = 1;
	while (bytes > 0)
	{
		if (find_newline(read_buffer))
			break ;
		bytes = read(fd, read_buffer, BUFFER_SIZE);
		if (bytes == -1)
			return (NULL);
		if (bytes == 0)
			break ;
		read_buffer[bytes] = '\0';
		if (!static_buffer)
			static_buffer = calloc(1, sizeof(char));
		temp = static_buffer;
		static_buffer = ft_strjoin(temp, read_buffer);
		free(temp);
		if (find_newline(read_buffer))
			break ;
	}
	return (static_buffer);
}

char	*set_result(char *static_buffer, int *i)
{
	char	*result;

	*i = 0;
	while (static_buffer[*i] && static_buffer[*i] != '\n')
		(*i)++;
	result = calloc(*i + 1 + (static_buffer[*i] == '\n'), sizeof(char));
	if (!result)
		return (NULL);
	*i = 0;
	while (static_buffer[*i] && static_buffer[*i] != '\n')
	{
		result[*i] = static_buffer[*i];
		(*i)++;
	}
	if (static_buffer[*i] == '\n')
		result[*i] = '\n';
	return (result);
}

/*
Czyta fd linijka po linijce, nie ważne jaka gigantyczna jest linijka
linijka zwracana ma na końcu \n jeżeli w pliku też na końcu miała \n
czyli ostatnia linijka nie bedzie miala \n na koncu
zwraca NULL gdy cos sie nie powiedzie lub gdy dotrze do konca pliku
Napisana wczesniej, po prostu wykorzytujemy ja tutaj zamiast getline()
*/
char	*get_next_line(int fd)
{
	static char	*static_buffer;
	char		*read_buffer;
	char		*temp;
	char		*result;
	int			i;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	read_buffer = calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!read_buffer)
		return (NULL);
	static_buffer = read_and_append(static_buffer, read_buffer, fd);
	free(read_buffer);
	if (!static_buffer || !(static_buffer[0]))
		return (NULL);
	result = set_result(static_buffer, &i);
	if (!result)
		return (NULL);
	temp = shift_buffer(static_buffer, &i);
	free(static_buffer);
	static_buffer = temp;
	return (result);
}