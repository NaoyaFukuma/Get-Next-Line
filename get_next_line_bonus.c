/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 13:18:05 by nfukuma           #+#    #+#             */
/*   Updated: 2022/07/22 10:46:12 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
// #include <stdio.h>
// static_strage_pointer == static lst pointer
//

char	*get_next_line(int fd)
{
	static t_list	*static_strage_pointer;
	t_list	*strage_p;
	t_list	*tmp_p;
	char			*newline;
	char			*buf;
	char			*catstr;
	ssize_t			readsize;
	size_t			i;

	if (BUFFER_SIZE <= 0 || read(fd, NULL, 0) == -1)
		return (NULL);

	if (static_strage_pointer == NULL)
	{
		static_strage_pointer = ft_newnode(fd);
		if (static_strage_pointer == NULL)
			return NULL;
	}

	strage_p = static_strage_pointer;
	tmp_p = NULL;
	while (1)
	{
		if (strage_p->fd == fd)
			break ;
		if (strage_p->next == NULL)
		{
			strage_p->next = ft_newnode(fd);
			if (strage_p->next == NULL)
				return NULL;
		}
		tmp_p = strage_p;
		strage_p = strage_p->next;
	}
	if (ft_strchar(strage_p->text, '\n'))
	{
		newline = ft_split(strage_p->text, strage_p->text_len, strage_p);
		if (newline == NULL)
			return (NULL);
		return (newline);
	}
	if (strage_p->fin_flag == 1 && strage_p->text_len == 0)
	{
		if (strage_p->next == NULL)
			static_strage_pointer = NULL;
		else
			tmp_p->next = strage_p->next;
		free(strage_p->text);
		free(strage_p);
		return (NULL);
	}

	if (strage_p->fin_flag == 1)
	{
		newline = malloc(strage_p->text_len + 1);
		if (newline == NULL)
			return (NULL);
		i = -1;
		while (strage_p->text[++i] != '\0')
			newline[i] = strage_p->text[i];
		newline[i] = '\0';
		free(strage_p->text);
		strage_p->text = NULL;
		strage_p->text_len = 0;
		return (newline);
	}

	buf = malloc(BUFFER_SIZE + 1);
	if (buf == NULL)
	{
		free(buf);
		return (NULL);
	}
	while (1)
	{
		readsize = read(strage_p->fd, buf, BUFFER_SIZE);
		if (readsize == -1 || (readsize == 0 && strage_p->text_len == 0))
		{

			free(strage_p->text);
			free(strage_p);
			free(buf);
			return (NULL);
		}
		if (readsize == 0)
		{
			strage_p->fin_flag = 1;
			free(buf);
			newline = malloc(strage_p->text_len + 1);
			if (newline == NULL)
				return (NULL);
			i = -1;
			while (strage_p->text[++i] != '\0')
				newline[i] = strage_p->text[i];
			newline[i] = '\0';
			free(strage_p->text);
			strage_p->text = NULL;
			strage_p->text_len = 0;
			return (newline);
		}

		if ((size_t)readsize < BUFFER_SIZE)
			strage_p->fin_flag = 1;
		buf[readsize] = '\0';
		catstr = ft_strcat(strage_p->text, buf, strage_p->text_len + readsize);
		if (catstr == NULL)
			return (NULL);
		if (ft_strchar(buf, '\n'))
		{
			free(buf);
			newline = ft_split(catstr, strage_p->text_len + readsize, strage_p);
			free(catstr);
			if (newline == NULL)
				return (NULL);
			return (newline);
		}
		free(strage_p->text);
		strage_p->text = catstr;
		strage_p->text_len = strage_p->text_len + readsize;
	}
}
