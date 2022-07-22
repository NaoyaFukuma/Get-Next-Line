/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 13:18:05 by nfukuma           #+#    #+#             */
/*   Updated: 2022/07/22 21:35:03 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_split(char *str, size_t strlen, t_list *strage_p)
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
	newline[i + 1] = '\0';
	tmp_str = malloc(strlen - i - 1 + 1);
	if (tmp_str == NULL)
		return (NULL);
	i++;
	j = -1;
	while (++j + i < strlen)
		tmp_str[j] = str[j + i];
	tmp_str[j] = '\0';
	free(strage_p->text);
	strage_p->text = tmp_str;
	strage_p->text_len = j;
	return (newline);
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

t_list	*ft_newnode(int fd, t_list *previous)
{
	t_list	*newnode;

	newnode = malloc(sizeof(t_list));
	if (newnode == NULL)
		return (NULL);
	newnode->fd = fd;
	newnode->text = malloc(1);
	newnode->text[0] = '\0';
	newnode->text_len = 0;
	newnode->fin_flag = 0;
	newnode->previous = previous;
	newnode->next = NULL;
	return (newnode);
}

t_list	*ft_set_pointer(t_list **static_p, t_list **strage_p, int fd)
{
	if (*static_p == NULL)
		*static_p = ft_newnode(fd, NULL);
	if (*static_p == NULL)
		return (NULL);
	*strage_p = *static_p;
	while (1)
	{
		if ((*strage_p)->fd == fd)
			break ;
		if ((*strage_p)->next == NULL)
			(*strage_p)->next = ft_newnode(fd, *strage_p);
		(*strage_p) = (*strage_p)->next;
	}
	return (*strage_p);
}

char	*get_next_line(int fd)
{
	static t_list	*static_p;
	t_list			*strage_p;

	if (BUFFER_SIZE <= 0 || read(fd, NULL, 0) == -1)
		return (NULL);
	strage_p = ft_set_pointer(&static_p, &strage_p, fd);
	if (strage_p == NULL)
		return (NULL);
	if (ft_strchar(strage_p->text, '\n'))
		return (ft_split(strage_p->text, strage_p->text_len, strage_p));
	if (strage_p->fin_flag == 1 && strage_p->text_len == 0)
		return (ft_delete_one_strage(&static_p, &strage_p));
	if (strage_p->fin_flag == 1)
		return (ft_push_end_line(&strage_p));
	return (ft_read_file_push_line(&strage_p, &static_p));
}
