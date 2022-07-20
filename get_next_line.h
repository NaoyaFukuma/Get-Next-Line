/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 11:51:00 by nfukuma           #+#    #+#             */
/*   Updated: 2022/07/20 11:52:56 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>

# define BUFFER_SIZE 10
typedef struct s_list
{
	char			*text;
	int				fd;
	struct s_list	*next;
}					t_list;

char				*get_next_line(int fd);

#endif
