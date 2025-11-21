/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdourdoi <mdourdoi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:58:54 by mdourdoi          #+#    #+#             */
/*   Updated: 2025/11/21 16:31:29 by mdourdoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

size_t	ft_strlen(char const *s, char end);
char	*ft_realloc_result(char *result, int total_readed, int size);
int		ft_nl_found(char *s);
char	*ft_strndup(const char *s, int n);
void	ft_memcpy(char *dest, char *src, size_t n);
char	*get_next_line(int fd);

#endif