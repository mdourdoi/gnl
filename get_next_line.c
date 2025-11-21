/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdourdoi <mdourdoi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:59:02 by mdourdoi          #+#    #+#             */
/*   Updated: 2025/11/20 18:11:26 by mdourdoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	*ft_exit(char *result, char residue[BUFFER_SIZE])
{
	size_t	i;

	if (result)
		free(result);
	if (residue)
	{
		i = 0;
		while (residue[i] != 0)
		{
			residue[i] = 0;
			i++;
		}
	}
	return (NULL);
}

// static void	ft_clean_residue(char *residue)
// {
// 	size_t	i;
// 	size_t	len;

// 	len = ft_strlen(residue, '\n');
// 	if (len == ft_strlen(residue, 0))
// 	{
// 		ft_exit(NULL, residue);
// 		return ;
// 	}
// 	i = 0;
// 	while (residue[i + len])
// 	{
// 		residue[i] = residue[i + len];
// 		i++;
// 	}
// 	residue[i] = 0;
// }

static void	ft_get_residue(char residue[BUFFER_SIZE], char *result)
{
	size_t	i;
	size_t	j;

	if (!residue || !result)
		return ;
	i = 0;
	while (result[i] && result[i] != '\n')
		i++;
	if (result[i] == '\n')
		i++;
	j = 0;
	while (result[i])
		residue[j++] = result[i++];
	residue[j] = 0;
}

static char	*ft_get_result(char *result)
{
	int		len;
	char	*ret;

	if (!result)
		return (NULL);
	len = ft_strlen(result, '\n');
	ret = malloc ((len +1) * sizeof(char));
	if (!ret)
	{
		free(result);
		return (NULL);
	}
	ft_memcpy(ret, result, len);
	ret[len] = 0;
	free(result);
	return (ret);
}

static char	*ft_read(int fd, char *r, char residue[BUFFER_SIZE + 1],
				int *r_size, int *total_readed)
{
	int	readed;

	while (!ft_nl_found(r))
	{
		readed = read(fd, &r[*total_readed], BUFFER_SIZE);
		if (readed < 0)
			return (ft_exit(r, residue));
		*total_readed += readed;
		r[*total_readed] = '\0';
		if (readed == 0)
			break ;
		if (*total_readed + BUFFER_SIZE > *r_size)
		{
			*r_size *= 2;
			r = ft_realloc_result(r, *total_readed, *r_size);
			if (!r)
				return (ft_exit(NULL, residue));
		}
	}
	ft_get_residue(residue, r);
	return (r);
}

char	*get_next_line(int fd)
{
	static char	residue[BUFFER_SIZE + 1] = "\0";
	char		*r;
	int			r_size;
	int			total_readed;

	if (read(fd, NULL, 0) < 0)
		return (ft_exit(NULL, residue));
	total_readed = ft_strlen(residue, 0);
	r_size = total_readed + BUFFER_SIZE;
	r = malloc((r_size + 1) * sizeof(char));
	if (!r)
		return (NULL);
	if (total_readed > 0)
		ft_memcpy(r, residue, total_readed);
	r[total_readed] = '\0';
	r = ft_read(fd, r, residue, &r_size, &total_readed);
	if (!r)
		return (NULL);
	r = ft_get_result(r);
	if (r && r[0] == 0)
		return (ft_exit(r, NULL));
	return (r);
}


// char	*get_next_line(int fd)
// {
// 	static char	residue[BUFFER_SIZE + 1] = "\0";
// 	char		*result;
// 	int			read_size;

// 	if (read(fd, NULL, 0) < 0)
// 		return (ft_exit(NULL, residue));
// 	result = ft_strndup(residue, ft_strlen(residue, '\n'));
// 	while (result && !ft_newline_found(result))
// 	{
// 		read_size = read(fd, residue, BUFFER_SIZE);
// 		if (read_size < 0)
// 			return (ft_exit(result, residue));
// 		if (read_size == 0)
// 			break ;
// 		residue[read_size] = '\0';
// 		result = ft_strjoin(result, residue);
// 		if (!result)
// 			return (ft_exit(NULL, residue));
// 	}
// 	ft_clean_residue(residue);
// 	if (result && result[0] == 0)
// 		return (ft_exit(result, NULL));
// 	return (result);
// }

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