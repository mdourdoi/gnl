/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdourdoi <mdourdoi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:58:59 by mdourdoi          #+#    #+#             */
/*   Updated: 2025/11/26 10:42:57 by mdourdoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(char const *s, char end)
{
	size_t	i;

	i = 0;
	if (s)
	{
		while (s[i] && s[i] != end)
			i++;
		if (s[i] == end && end != 0)
			i++;
	}
	return (i);
}

void	ft_memcpy(char *dest, char *src, size_t n)
{
	size_t	i;

	if (!dest && !src)
		return ;
	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
}

char	*ft_realloc_result(char *result, int total_readed, int size)
{
	char	*temp;

	temp = result;
	result = malloc((size + 1) * sizeof(char));
	if (!result)
	{
		free(temp);
		return (NULL);
	}
	ft_memcpy(result, temp, total_readed + 1);
	free(temp);
	return (result);
}

int	ft_nl_found(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}
