/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:24:02 by seoson            #+#    #+#             */
/*   Updated: 2023/05/01 17:27:25 by seoson           ###   ########.fr       */
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

t_list	*find(t_list **head, int fd)
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
	temp = *head;
	while (temp->next && *head != find)
		temp = temp->next;
	if (*head != find)
		temp->next = find;
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
	len = s_len(s);
	temp = (char *)malloc(sizeof(char) * len + 1);
	if (!temp)
		return (0);
	cpy(temp, s, len + 1);
	while (s[total_len])
		total_len++;
	cpy(s, &s[len], total_len + 1 - len);
	return (temp);
}

int	init_b(char **temp, char **buff, int *check, int fd)
{
	*buff = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!*buff)
	{
		free(*temp);
		*temp = 0;
		*check = -1;
		return (0);
	}
	*check = do_read(*buff, fd);
	if (*check == -1 || (*check == 0 && s_len(*temp) == 0))
	{
		free(*temp);
		*temp = 0;
		return (0);
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static t_list	*head;
	char			*temp;
	char			*buff;
	int				size;

	if (!find(&head, fd))
		return (0);
	temp = init_s(find(&head, fd)->s, fd);
	if (temp && has_newline(temp))
		return (temp);
	init_b(&temp, &buff, &size, fd);
	while (size > 0)
	{
		if (has_newline(buff))
		{
			cpy(find(&head, fd)->s, &buff[s_len(buff)], size + 1 - s_len(buff));
			temp = ft_strjoin(temp, buff, s_len(buff));
			if (!temp)
				free_targetlist(&head, fd);
			return (free(buff), temp);
		}
		temp = ft_strjoin(temp, buff, s_len(buff));
		size = do_read(buff, fd);
	}
	return (free_targetlist(&head, fd), free(buff), temp);
}
