/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:08:43 by wkornato          #+#    #+#             */
/*   Updated: 2024/12/21 11:24:35 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>

// get_next_line.c:

char	*get_next_line(int fd);

// get_next_line_utils.c:

char	*ft_strjoin(char const *s1, char const *s2);
char	*find_newline(char *string);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
# endif /* BUFFER_SIZE */
#endif /* GET_NEXT_LINE_H */