/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdourdoi <mdourdoi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:58:54 by mdourdoi          #+#    #+#             */
/*   Updated: 2025/11/18 15:09:37 by mdourdoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# if BUFFER_SIZE > 4096
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

size_t	ft_strlen(char const *s, char end);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_newline_found(char *s);
char	*ft_strndup(const char *s, int n);
char	*get_next_line(int fd);

#endif