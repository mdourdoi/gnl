/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdourdoi <mdourdoi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:59:02 by mdourdoi          #+#    #+#             */
/*   Updated: 2025/11/19 17:32:36 by mdourdoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	*ft_bzero(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != 0)
	{
		str[i] = 0;
		i++;
	}
	return (NULL);
}

static void	ft_clean_residue(char *residue)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(residue, '\n');
	if (len == ft_strlen(residue, 0))
	{
		ft_bzero(residue);
		return ;
	}
	i = 0;
	while (residue[i + len])
	{
		residue[i] = residue[i + len];
		i++;
	}
	residue[i] = 0;
}

char	*get_next_line(int fd)
{
	static char	residue[BUFFER_SIZE + 1] = "\0";
	char		*result;
	int			read_size;

	if (read(fd, NULL, 0) < 0)
		return (ft_bzero(residue));
	result = ft_strndup(residue, ft_strlen(residue, '\n'));
	while (result && !ft_newline_found(result))
	{
		read_size = read(fd, residue, BUFFER_SIZE);
		if (read_size < 0)
			return (ft_bzero(residue));
		residue[read_size] = '\0';
		result = ft_strjoin(result, residue);
		if (!result)
			return (ft_bzero(residue));
	}
	ft_clean_residue(residue);
	if (result && result[0] == 0)
	{
		free(result);
		return (NULL);
	}
	return (result);
}

#include <stdio.h>
int	main(int, char** argv)
{
	int fd = open(argv[1], 0, 0);
	char *test;

	while ((test = get_next_line(fd)))
	{
		printf("%s", test);
		free(test);
	}
	return (0);
}