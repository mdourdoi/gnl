/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdourdoi <mdourdoi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:59:02 by mdourdoi          #+#    #+#             */
/*   Updated: 2025/11/17 16:20:18 by mdourdoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_line(int fd, char *residue)
{
	char	cur[BUFFER_SIZE + 1];
	size_t	security;
	char	*temp;
	char	*res;

	if (ft_newline_found(residue))
		return (residue);
	res = residue;
	while (1)
	{
		security = read(fd, cur, BUFFER_SIZE);
		if (security <= 0)
			break ;
		cur[security] = 0;
		temp = res;
		res = ft_strjoin(temp, cur);
		free(temp);
		if (ft_newline_found(res))
			break ;
	}
	return (res);
}

static char	*ft_get_result(char *s)
{
	int		len;
	char	*result;

	len = ft_strlen(s, '\n');
	result = ft_strndup(s, len);
	return (result);
}

static char	*ft_get_residue(char *s)
{
	int		len;
	int		start;
	char	*residue;

	len = ft_strlen(s, 0);
	start = ft_strlen(s, '\n');
	residue = ft_strndup(&s[start], len - start);
	return (residue);
}

static void	*ft_free_all(char *line, char *result, char *residue)
{
	if (line)
		free(line);
	if (result)
		free(result);
	if (residue)
		free(residue);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*residue = NULL;
	char		*result;
	char		*line;

	line = NULL;
	result = NULL;
	line = ft_line(fd, residue);
	if (!line)
		return (ft_free_all(line, result, residue));
	result = ft_get_result(line);
	residue = ft_get_residue(line);
	free(line);
	if (!result || !residue)
		return (ft_free_all(NULL, result, residue));
	if (ft_strlen(result, 0) == 0)
		return (ft_free_all(NULL, result, residue));
	return (result);
}
