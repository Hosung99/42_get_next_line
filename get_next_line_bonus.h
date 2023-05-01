/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:24:13 by seoson            #+#    #+#             */
/*   Updated: 2023/05/01 17:51:49 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	char			s[BUFFER_SIZE + 1];
	struct s_list	*next;
	int				fd;
}	t_list;

char	*get_next_line(int fd);
t_list	*find(t_list **head, int fd);
char	*init_s(char *s, int fd);
int		init_b(char **temp, char **buff, int *check, int fd);
void	free_targetlist(t_list **head, int fd);
int		do_read(char *buff, int fd);
int		has_newline(char *temp);
int		s_len(char *s);
void	cpy(char *dst, char *src, int dstsize);
char	*ft_strjoin(char *s1, char *s2, int index);

#endif