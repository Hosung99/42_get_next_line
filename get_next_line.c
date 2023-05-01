/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 13:10:38 by seoson            #+#    #+#             */
/*   Updated: 2023/05/01 17:53:59 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*init_s(char *s, int fd)
{
	int		total_len;
	int		len;
	char	*temp;

	if (fd < 0)
		return (0);
	total_len = 0;
	len = ft_strlen(s);
	temp = (char *)malloc(sizeof(char) * len + 1);
	if (!temp)
		return (0);
	ft_strlcpy(temp, s, len + 1);
	while (s[total_len])
		total_len++;
	ft_strlcpy(s, &s[len], total_len + 1 - len);
	return (temp);
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

int	init_b(char *temp, char **buff, int *check, int fd)
{
	*buff = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!*buff)
	{
		free(temp);
		return (0);
	}
	*check = do_read(*buff, fd);
	if (*check == -1 || (*check == 0 && ft_strlen(temp) == 0))
	{
		free(temp);
		free(*buff);
		return (0);
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static char	s[BUFFER_SIZE + 1];
	char		*temp;
	char		*buff;
	int			check;

	temp = init_s(s, fd);
	if (!temp || has_newline(temp))
		return (temp);
	if (!init_b(temp, &buff, &check, fd))
		return (0);
	while (check > 0)
	{
		if (has_newline(buff))
		{
			ft_strlcpy(s, &buff[ft_strlen(buff)], check + 1 - ft_strlen(buff));
			temp = ft_strjoin(temp, buff, ft_strlen(buff));
			break ;
		}
		temp = ft_strjoin(temp, buff, ft_strlen(buff));
		check = do_read(buff, fd);
	}
	return (free(buff), temp);
}
