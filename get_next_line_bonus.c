/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:24:02 by seoson            #+#    #+#             */
/*   Updated: 2023/04/29 18:10:18 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_list	*find_fd(t_list *list, int fd)
{
	while (list)
	{
		if (list->fd == fd)
			return (list);
		list = list->next;
	}
	return (0);
}

t_list	*init_list(t_list *list, int fd)
{
	t_list *find;
	t_list *temp;

    if (fd < 0)
		return (0);
	find = (t_list *)malloc(sizeof(t_list));
	if (!find)
		return (0);
	temp = find_fd(list, fd);
	if (temp)
		return (temp);
	find->fd = fd;
	ft_lstadd_back(&list, find);
	return (find);
}

char	*init_s(char *s)
{
	int		total_len;
	int		len;
	char	*temp;

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
	static t_list	*list;
	char		    *temp;
	char		    *buff;
	int			    check;

    list = init_list(list, fd);
	if (!list)
        return (0);
	temp = init_s(list->s);
	if (!temp || has_newline(temp))
		return (temp);
	if (!init_b(temp, &buff, &check, fd))
		return (0);
	while (check > 0)
	{
		if (has_newline(buff))
		{
			ft_strlcpy(list->s, &buff[ft_strlen(buff)], check + 1 - ft_strlen(buff));
			temp = ft_strjoin(temp, buff, ft_strlen(buff));
			break ;
		}
		temp = ft_strjoin(temp, buff, ft_strlen(buff));
		check = do_read(buff, fd);
	}
	free(buff);
	return (temp);
}

// void   check_leak(void)
// {
// 		system("leaks --list -- a.out");
// }

// #include <stdio.h>
// #include <fcntl.h>
// int main()
// {
// 		atexit(check_leak);
// 		int	fd;
// 		fd = open("a.txt",O_RDONLY);
// 		char *line = get_next_line(fd);
// 		printf("%p\n", line);
// 		printf("%s\n", line);
		
// 		fd = open("b.txt",O_RDONLY);

// 		char *line2 = get_next_line(fd);
// 		printf("%p\n", line2);
// 		printf("%s\n", line2);
// 		fd = open("c.txt",O_RDONLY);

// 		char *line3 = get_next_line(fd);
// 		printf("%p\n", line3);
// 		printf("%s\n", line3);
// }