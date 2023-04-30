/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:24:02 by seoson            #+#    #+#             */
/*   Updated: 2023/04/30 22:19:02 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	free_targetlist(t_list **head, int fd)
{
	t_list	*prev;
	t_list	*temp;

	if (!(*head))
		return ;
	temp = *head;
	prev = *head;
	while (temp)
	{
		if (temp->fd == fd)
			break ;
		prev = temp;
		temp = temp->next;
	}
	if (temp->fd == fd)
	{
		if (temp->next != 0)
			prev->next = temp->next;
		else
			prev->next = 0;
		if ((*head)->fd == temp->fd)
			*head = temp->next;
		free(temp);
	}
}

t_list	*init_list(t_list **head, int fd)
{
	t_list	*find;
	t_list	*temp;

	temp = *head;
	while (temp)
	{
		if (temp->fd == fd)
			return (temp);
		temp = temp->next;
	}
	find = (t_list *)malloc(sizeof(t_list));
	if (!find)
		return (0);
	find->fd = fd;
	find->s[0] = 0;
	find->next = 0;
	if (!*head)
		*head = find;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = find;
	}
	return (find);
}

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
	static t_list	*head;
	t_list			*list;
	char			*temp;
	char			*buff;
	int				check;
	
	list = init_list(&head, fd);
	if (!list)
		return (0);
	temp = init_s(list->s, fd);
	if (!temp)
	{
		free_targetlist(&head, fd);
		return (0);
	}
	if (has_newline(temp))
		return (temp);
	if (!init_b(temp, &buff, &check, fd))
	{
		free_targetlist(&head, fd);
		return (0);
	}
	while (check > 0)
	{
		if (has_newline(buff))
		{
			ft_strlcpy(list->s, &buff[ft_strlen(buff)], check + 1 - ft_strlen(buff));
			temp = ft_strjoin(temp, buff, ft_strlen(buff));
			if (!temp)
				free_targetlist(&head, fd);
			free(buff);
			return (temp);
		}
		temp = ft_strjoin(temp, buff, ft_strlen(buff));
		check = do_read(buff, fd);
	}
	free(buff);
	free_targetlist(&head, fd);
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
// 		int	fd1;
// 		int	fd2;
// 		int	fd3;
// 		fd1 = open("a.txt",O_RDONLY);
// 		fd2 = open("b.txt",O_RDONLY);
// 		fd3 = open("c.txt",O_RDONLY);
// 		for (int i =0; i<3; i++)
// 		{
// 			char *line = get_next_line(fd1);
// 			printf("%s", line);
// 			free(line);
// 			char *line2 = get_next_line(fd2);
// 			printf("%s", line2);
// 			free(line2);
// 			char *line3 = get_next_line(fd3);
// 			printf("%s", line3);
// 			free(line3);
// 		}
// 		// char *line = get_next_line(fd1);
// 		// printf("%s\n", line);
// 		// printf("%p", line);
// 		// free(line);
// 		// atexit(check_leak);
// 		// fd = open("b.txt",O_RDONLY);

// 		// char *line2 = get_next_line(fd);
// 		// printf("%p\n", line2);
// 		// printf("%s\n", line2);
// 		// fd = open("c.txt",O_RDONLY);

// 		// char *line3 = get_next_line(fd);
// 		// printf("%p\n", line3);
// 		// printf("%s\n", line3);
// }