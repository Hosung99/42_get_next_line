/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:24:32 by seoson            #+#    #+#             */
/*   Updated: 2023/05/01 17:25:34 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	has_newline(char *temp)
{
	int	index;

	index = 0;
	while (temp[index])
	{
		if (temp[index] == '\n')
			return (1);
		index++;
	}
	return (0);
}

int	s_len(char *s)
{
	int	cnt;

	if (!s)
		return (0);
	cnt = 0;
	while (*s)
	{
		cnt++;
		if (*s == '\n')
			break ;
		s++;
	}
	return (cnt);
}

void	cpy(char *dst, char *src, int dstsize)
{
	int	i;
	int	length_src;

	i = 0;
	length_src = 0;
	if (src && dst)
	{
		if (dstsize != 0)
		{
			while (i + 1 < dstsize && src[i])
			{
				dst[i] = src[i];
				i++;
			}
			dst[i] = '\0';
		}
	}
}

char	*ft_strjoin(char *s1, char *s2, int index)
{
	char	*str;
	int		i;
	int		save;

	str = (char *)malloc(sizeof(char) * (s_len(s1) + index + 1));
	if (!str)
	{
		free(s1);
		return (0);
	}
	i = 0;
	save = 0;
	if (s1)
	{
		while (s1[i])
			str[save++] = s1[i++];
	}
	i = 0;
	while (s2[i] && i < index)
		str[save++] = s2[i++];
	str[save] = '\0';
	free(s1);
	return (str);
}

int	do_read(char *buff, int fd)
{
	int		read_size;

	read_size = (int)read(fd, buff, BUFFER_SIZE);
	if (read_size <= 0)
		return (read_size);
	buff[read_size] = 0;
	return (read_size);
}
