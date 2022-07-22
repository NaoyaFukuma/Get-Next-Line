/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 13:18:05 by nfukuma           #+#    #+#             */
/*   Updated: 2022/07/22 16:09:59 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
// #include <stdio.h>

char	*get_next_line(int fd)
{
	static t_list	*static_p;
	t_list	*strage_p;
	// t_list	*tmp_p;
	char			*newline;
	char			*buf;
	char			*catstr;
	ssize_t			readsize;
	size_t			i;

	if (BUFFER_SIZE <= 0 || read(fd, NULL, 0) == -1)
		return (NULL);

	strage_p = ft_set_pointer(&static_p, &strage_p, fd);
	// strage_p = ft_set_pointer(&static_p, &strage_p, &tmp_p, fd);
	if (strage_p == NULL)
		return (NULL);

	// if (ft_strchar(strage_p->text, '\n') != NULL || strage_p->fin_flag == 1)
	// 	return (ft_strage_check(&static_p, &strage_p, &tmp_p));

// strage part
	if (ft_strchar(strage_p->text, '\n'))
	{
		newline = ft_split(strage_p->text, strage_p->text_len, strage_p);
		if (newline == NULL)
			return (NULL);
		return (newline);
	}
	if (strage_p->fin_flag == 1 && strage_p->text_len == 0)
	{
		if (strage_p->previous == NULL)
			static_p = NULL;
		else
		{
			strage_p->previous->next = strage_p->next;
			strage_p->next->previous = strage_p->previous;
		}
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

// read part
	while (1)
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (buf == NULL)
			return (NULL);
		readsize = read(strage_p->fd, buf, BUFFER_SIZE);
		if (readsize == -1 || (readsize == 0 && strage_p->text_len == 0))
		{
			if (strage_p->previous == NULL)
				static_p = NULL;
			else
			{
				strage_p->previous->next = strage_p->next;
				strage_p->next->previous = strage_p->previous;
			}
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
		free(buf);
		buf = NULL;
		free(strage_p->text);
		strage_p->text = catstr;
		strage_p->text_len = strage_p->text_len + readsize;
	}
}
