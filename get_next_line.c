/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdourdoi <mdourdoi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:59:02 by mdourdoi          #+#    #+#             */
/*   Updated: 2025/11/18 15:44:47 by mdourdoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	*ft_free_all(char *result, char **residue)
{
	int	i;

	if (result)
		free(result);
	if (residue && *residue)
	{
		i = 0;
		while ((*residue)[i])
			(*residue)[i++] = 0;
		free(*residue);
		*residue = NULL;
	}
	return (NULL);
}

static char	*ft_line(int fd, char *residue)
{
	char	cur[BUFFER_SIZE + 1];
	ssize_t	security;
	char	*temp;
	char	*res;

	res = ft_strndup(residue, ft_strlen(residue, 0));
	if (ft_newline_found(res))
		return (res);
	while (res)
	{
		security = read(fd, cur, BUFFER_SIZE);
		if (security == 0)
			break ;
		if (security == -1)
			return (ft_free_all(res, NULL));
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

char	*get_next_line(int fd)
{
	static char	*residue = NULL;
	char		*result;
	char		*line;

	if (fd < 0 || fd > 1023 || BUFFER_SIZE < 1)
		return (ft_free_all(NULL, &residue));
	line = NULL;
	result = NULL;
	line = ft_line(fd, residue);
	if (!line)
		return (ft_free_all(NULL, &residue));
	ft_free_all(NULL, &residue);
	result = ft_get_result(line);
	residue = ft_get_residue(line);
	free(line);
	if (!result || !residue || ft_strlen(result, 0) == 0)
		return (ft_free_all(result, &residue));
	return (result);
}

// #include <stdio.h>
// int	main(int, char** argv)
// {
// 	int fd = open(argv[1], 0, 0);
// 	char *test;
// 	while ((test = get_next_line(fd)))
// 	{
// 		printf("%s", test);
// 		free(test);
// 	}
// 	return (0);
// }