/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:28:01 by nfukuma           #+#    #+#             */
/*   Updated: 2022/07/22 21:16:08 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strcat(char **s1, char **s2, size_t len)
{
	char	*catstr;
	size_t	i;
	size_t	j;

	catstr = malloc(len + 1);
	if (catstr == NULL)
		return (NULL);
	i = -1;
	while ((*s1)[++i] != '\0')
		catstr[i] = (*s1)[i];
	j = -1;
	while ((*s2)[++j] != '\0')
		catstr[j + i] = (*s2)[j];
	catstr[j + i] = '\0';
	free(*s1);
	*s1 = NULL;
	free(*s2);
	*s2 = NULL;
	return (catstr);
}

char	*ft_delete_one_strage(t_list **static_p, t_list **strage_p)
{
	if ((*static_p)->next == NULL)
		(*static_p) = NULL;
	else if ((*strage_p)->previous == NULL)
	{
		(*static_p) = (*strage_p)->next;
		(*static_p)->previous = NULL;
	}
	else if ((*strage_p)->next == NULL)
		(*strage_p)->previous->next = NULL;
	else
	{
		(*strage_p)->previous->next = (*strage_p)->next;
		(*strage_p)->next->previous = (*strage_p)->previous;
	}
	free((*strage_p)->text);
	free(*strage_p);
	return (NULL);
}

char	*ft_push_end_line(t_list **strage_p)
{
	char	*newline;
	size_t	i;

	newline = malloc((*strage_p)->text_len + 1);
	if (newline == NULL)
		return (NULL);
	i = -1;
	while ((*strage_p)->text[++i] != '\0')
		newline[i] = (*strage_p)->text[i];
	newline[i] = '\0';
	free((*strage_p)->text);
	(*strage_p)->text = NULL;
	(*strage_p)->text_len = 0;
	return (newline);
}

char	*ft_parse_readsize(ssize_t readsize, char **buf, t_list **strage_p,
		t_list **static_p)
{
	free(*buf);
	*buf = NULL;
	if (readsize == -1)
		return (NULL);
	if ((*strage_p)->text_len == 0)
		return (ft_delete_one_strage(static_p, strage_p));
	(*strage_p)->fin_flag = 1;
	return (ft_push_end_line(&(*strage_p)));
}

char	*ft_read_file_push_line(t_list **strage_p, t_list **static_p)
{
	char	*buf;
	ssize_t	readsize;

	while (1)
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (buf == NULL)
			return (NULL);
		readsize = read((*strage_p)->fd, buf, BUFFER_SIZE);
		buf[readsize] = '\0';
		if (readsize == 0 || readsize == -1)
			return (ft_parse_readsize(readsize, &buf, strage_p, static_p));
		if ((size_t)readsize < BUFFER_SIZE)
			(*strage_p)->fin_flag = 1;
		(*strage_p)->text = ft_strcat(&((*strage_p)->text), &buf,
				(*strage_p)->text_len + readsize);
		if (ft_strchar((*strage_p)->text, '\n'))
			return (ft_split((*strage_p)->text, (*strage_p)->text_len
					+ readsize, *strage_p));
		(*strage_p)->text_len = (*strage_p)->text_len + readsize;
	}
}
