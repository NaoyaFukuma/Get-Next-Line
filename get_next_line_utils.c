/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:28:01 by nfukuma           #+#    #+#             */
/*   Updated: 2022/07/22 02:27:56 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_newnode(int fd)
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
			return (str) ;
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
