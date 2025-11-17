/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdourdoi <mdourdoi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:58:59 by mdourdoi          #+#    #+#             */
/*   Updated: 2025/11/17 16:30:55 by mdourdoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char const *s, char end)
{
	int	i;

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

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	char	*res;
	size_t	len_s1;
	size_t	len_s2;

	i = 0;
	len_s1 = ft_strlen(s1, 0);
	len_s2 = ft_strlen(s2, 0);
	res = malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (i < len_s1)
	{
		res[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < len_s2)
	{
		res[i + len_s1] = s2[i];
		i++;
	}
	res[len_s1 + len_s2] = 0;
	return (res);
}

char	*ft_strndup(const char *s, int n)
{
	size_t		len;
	size_t		i;
	char		*res;

	i = 0;
	len = ft_strlen(s, 0);
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (i < len && i < (size_t)n)
	{
		res[i] = s[i];
		i++;
	}
	res[i] = 0;
	return (res);
}

int	ft_newline_found(char *s)
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
