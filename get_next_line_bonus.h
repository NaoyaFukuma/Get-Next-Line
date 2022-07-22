/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 11:51:00 by nfukuma           #+#    #+#             */
/*   Updated: 2022/07/22 21:17:50 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stdlib.h>
# include <unistd.h>

# define FD_MAX 256

typedef struct s_list
{
	int				fd;
	char			*text;
	size_t			text_len;
	int				fin_flag;
	struct s_list	*previous;
	struct s_list	*next;
}					t_list;

// in .c
char				*get_next_line(int fd);
t_list				*ft_newnode(int fd, t_list *prvious);
char				*ft_strchar(char *str, char c);
char				*ft_split(char *str, size_t strlen, t_list *strage_p);
t_list				*ft_set_pointer(t_list **static_p, t_list **strage_p,
						int fd);

// in utils.c
char				*ft_strcat(char **s1, char **s2, size_t len);
char				*ft_delete_one_strage(t_list **static_p, t_list **strage_p);
char				*ft_push_end_line(t_list **strage_p);
char				*ft_read_file_push_line(t_list **strage_p,
						t_list **static_p);
char				*ft_parse_readsize(ssize_t readsize, char **buf,
						t_list **strage_p, t_list **static_p);

#endif
