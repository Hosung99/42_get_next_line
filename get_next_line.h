/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 22:22:37 by shson1217         #+#    #+#             */
/*   Updated: 2023/04/29 16:20:26 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# define GET_NEXT_LINE_H

char	*get_next_line(int fd);
char	*init_s(char *s, int fd);
int     init_b(char *temp, char **buff, int *check, int fd);
int		do_read(char *buff, int fd);
int		has_newline(char *temp);
int		ft_strlen(char *s);
void	ft_strlcpy(char *dst, char *src, int dstsize);
char	*ft_strjoin(char *s1, char *s2, int index);

#endif
