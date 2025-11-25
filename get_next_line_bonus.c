/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdourdoi <mdourdoi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:59:02 by mdourdoi          #+#    #+#             */
/*   Updated: 2025/11/25 12:50:00 by mdourdoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	*ft_exit(char *result, char residue[BUFFER_SIZE])
{
	size_t	i;

	if (result)
		free(result);
	if (residue)
	{
		i = 0;
		while (i < BUFFER_SIZE)
			residue[i++] = 0;
	}
	return (NULL);
}

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

static char	*ft_read(int fd, char *result, char residue[BUFFER_SIZE])
{
	int	result_size;
	int	total_readed;
	int	readed;

	total_readed = ft_strlen(result, 0);
	result_size = total_readed + BUFFER_SIZE;
	while (!ft_nl_found(result))
	{
		readed = read(fd, &result[total_readed], BUFFER_SIZE);
		if (readed < 0)
			return (ft_exit(result, residue));
		total_readed += readed;
		result[total_readed] = '\0';
		if (readed == 0)
			break ;
		if (total_readed + BUFFER_SIZE > result_size)
		{
			result_size *= 2;
			result = ft_realloc_result(result, total_readed, result_size);
			if (!result)
				return (ft_exit(NULL, residue));
		}
	}
	ft_get_residue(residue, result);
	return (result);
}

char	*get_next_line(int fd)
{
	static char	residue[1024][BUFFER_SIZE];
	char		*result;
	int			residue_len;

	if (fd < 0 || fd > 1023 || BUFFER_SIZE < 1)
		return (NULL);
	residue_len = ft_strlen(residue[fd], 0);
	result = malloc((residue_len + BUFFER_SIZE + 1) * sizeof(char));
	if (!result)
		return (NULL);
	ft_memcpy(result, residue[fd], residue_len);
	result[residue_len] = '\0';
	result = ft_read(fd, result, residue[fd]);
	if (!result)
		return (NULL);
	result = ft_get_result(result);
	if (result && result[0] == 0)
		return (ft_exit(result, residue[fd]));
	return (result);
}
