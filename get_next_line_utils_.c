/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:28:01 by nfukuma           #+#    #+#             */
/*   Updated: 2022/07/23 16:57:07 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_split_gnl(char *str, size_t strlen, t_list *strage_p)
{
	char	*newline;
	char	*tmp_str;
	size_t	i;
	size_t	j;

	newline = malloc(ft_strchar(str, '\n') - str + 2);
	if (newline == NULL)
		return (NULL);
	i = -1;
	while (str[++i] != '\n')
		newline[i] = str[i];
	newline[i] = '\n';
	newline[i++ + 1] = '\0';
	tmp_str = malloc(strlen - i + 1);
	if (tmp_str == NULL)
	{
		free(newline);
		return (NULL);
	}
	j = -1;
	while (++j + i <= strlen)
		tmp_str[j] = str[j + i];
	free(strage_p->text);
	strage_p->text = tmp_str;
	strage_p->text_len = j;
	return (newline);
}

char	*ft_strcat_gnl(char **s1, char **s2, size_t len)
{
	char	*catstr;
	size_t	i;
	size_t	j;

	catstr = malloc(len + 1);
	if (catstr == NULL)
	{
		free(*s1);
		*s1 = NULL;
		free(*s2);
		*s2 = NULL;
		return (NULL);
	}
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

t_list	*ft_newnode(int fd, t_list *previous)
{
	t_list	*newnode;

	newnode = malloc(sizeof(t_list));
	if (newnode == NULL)
		return (NULL);
	newnode->fd = fd;
	newnode->text = malloc(1);
	if (newnode->text == NULL)
	{
		free(newnode);
		return (NULL);
	}
	newnode->text[0] = '\0';
	newnode->text_len = 0;
	newnode->fin_flag = 0;
	newnode->previous = previous;
	newnode->next = NULL;
	return (newnode);
}

char	*ft_strchar(char *str, char c)
{
	if (str == NULL)
		return (NULL);
	while (*str != '\0')
	{
		if (*str == c)
			return (str);
		str++;
	}
	return (NULL);
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
		buf = malloc((size_t)BUFFER_SIZE + 1);
		if (buf == NULL)
			return (NULL);
		readsize = read((*strage_p)->fd, buf, BUFFER_SIZE);
		if (readsize == 0 || readsize == -1)
			return (ft_parse_readsize(readsize, &buf, strage_p, static_p));
		buf[readsize] = '\0';
		if ((size_t)readsize < BUFFER_SIZE)
			(*strage_p)->fin_flag = 1;
		(*strage_p)->text = ft_strcat_gnl(&((*strage_p)->text), &buf,
				(*strage_p)->text_len + readsize);
		if (ft_strchar((*strage_p)->text, '\n'))
			return (ft_split_gnl((*strage_p)->text, (*strage_p)->text_len
					+ readsize, *strage_p));
		(*strage_p)->text_len = (*strage_p)->text_len + readsize;
	}
}
