/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 13:18:05 by nfukuma           #+#    #+#             */
/*   Updated: 2022/07/22 02:39:42 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

	// if ((fd < 0 && fd <= FD_MAX) || BUFFER_SIZE < 1 || read(fd, NULL, 0))
	// 	return (NULL);
	if (BUFFER_SIZE < 1 || read(fd, NULL, 0) == -1)
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
printf("strage_p->finflag? [%d]\n", strage_p->fin_flag);
printf("strage_p->text_len? [%zu]\n", strage_p->text_len);
	if (strage_p->fin_flag == 1 && strage_p->text_len == 0)
	{
		printf("test");
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
		newline = malloc(strage_p->text_len + 2);
		if (newline == NULL)
			return (NULL);
		i = -1;
		while (strage_p->text[++i] != '\0')
			newline[i] = strage_p->text[i];
		newline[i] = '\n';
		newline[i + 1] = '\0';
		free(strage_p->text);
		strage_p->text = NULL;
		strage_p->text_len = 0;
		return (newline);
	}

	buf = malloc(BUFFER_SIZE + 1);
	if (buf == NULL)
		return (NULL);
	while (1)
	{
		readsize = read(strage_p->fd, buf, BUFFER_SIZE);
		if (readsize == -1)
			return (NULL);
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
		printf("\n\ntest\n\n");
		fflush(stdout);
		exit(0);
		free(strage_p->text);
		strage_p->text = catstr;
		strage_p->text_len = strage_p->text_len + readsize;
	}
}
