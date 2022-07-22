/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:28:01 by nfukuma           #+#    #+#             */
/*   Updated: 2022/07/22 16:09:26 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	strage_p->text = NULL;
	strage_p->text = tmp_str;
	strage_p->text_len = j;
	return (newline);
}

char	*ft_strcat(char *s1, char *s2, size_t len)
{
	char	*catstr;
	size_t	i;
	size_t	j;

	catstr = malloc(len + 1);
	if (catstr == NULL)
		return (NULL);
	i = -1;
	while (s1[++i] != '\0')
		catstr[i] = s1[i];
	j = -1;
	while (s2[++j] != '\0')
		catstr[j + i] = s2[j];
	catstr[j + i] = '\0';
	return (catstr);
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

// t_list	*ft_set_pointer(t_list **static_p, t_list **strage_p,t_list **tmp_p, int fd)
// {
// 	if (*static_p == NULL)
// 		*static_p = ft_newnode(fd);
// 	if (*static_p == NULL)
// 		return (NULL);
// 	*strage_p = *static_p;
// 	*tmp_p = NULL;
// 	while (1)
// 	{
// 		if ((*strage_p)->fd == fd)
// 			break ;
// 		if ((*strage_p)->next == NULL)
// 			(*strage_p)->next = ft_newnode(fd);
// 		*tmp_p = *strage_p;
// 		(*strage_p) = (*strage_p)->next;
// 	}
// 	return (*strage_p);
// }
//

// char	*ft_strage_check(t_list	**static_p, t_list	**strage_p, t_list	**tmp_p)
// {
// 	char	*newline;
// 	size_t	i;
//
// 	if (ft_strchar((*strage_p)->text, '\n'))
// 	{
// 		newline = ft_split((*strage_p)->text, (*strage_p)->text_len, *strage_p);
// 		if (newline == NULL)
// 			return (NULL);
// 	}
// 	if ((*strage_p)->fin_flag == 1 && (*strage_p)->text_len == 0)
// 	{
// 		if ((*static_p)->next == NULL)
// 			*static_p = NULL;
// 		else
// 			(*tmp_p)->next = (*strage_p)->next;
// 		free((*strage_p)->text);
// 		free(*strage_p);
// 		return (NULL);
// 	}
//
// 	if ((*strage_p)->fin_flag == 1)
// 	{
// 		newline = malloc((*strage_p)->text_len + 1);
// 		if (newline == NULL)
// 			return (NULL);
// 		i = -1;
// 		while ((*strage_p)->text[++i] != '\0')
// 			newline[i] =(*strage_p)->text[i];
// 		newline[i] = '\0';
// 		free((*strage_p)->text);
// 		(*strage_p)->text = NULL;
// 		(*strage_p)->text_len = 0;
// 	}
// 	return (newline);
// }
