/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 11:51:00 by nfukuma           #+#    #+#             */
/*   Updated: 2022/07/22 16:07:39 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>


# define FD_MAX	256
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

// in utils.c
t_list	*ft_newnode(int fd, t_list *prvious);
// t_list	*ft_newnode(int fd);
char	*ft_strchar(char *str, char c);
char	*ft_split(char *str, size_t strlen, t_list *strage_p);
char	*ft_strcat(char *s1, char *s2, size_t len);
t_list	*ft_set_pointer(t_list **static_p, t_list **strage_p, int fd);
// t_list	*ft_set_pointer(t_list **static_p, t_list **strage_p, t_list **tmp_p, int fd);
// char	*ft_strage_check(t_list	**static_p, t_list	**strage_p, t_list	**tmp_p);

#endif
