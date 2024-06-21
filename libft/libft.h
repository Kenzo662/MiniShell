/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evella <evella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 22:48:19 by evella            #+#    #+#             */
/*   Updated: 2024/06/06 15:59:24 by evella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdarg.h>
# include <stdint.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_line
{
	char	*str;
	char	buffer[BUFFER_SIZE + 1];
	int		oread;
}			t_line;

int			ft_isalnum(char c);
int			ft_isalpha(char c);
int			ft_isdigit(int nb);
char		*ft_strcat(char *dest, const char *src);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strcpy(char *dest, const char *src);
long long	ft_atoll(const char *str);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
size_t		ft_strlen(const char *str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strncpy(char *dest, const char *src, size_t n);
void		ft_bzero(void *str, size_t len);
void		*ft_memset(void *str, int c, size_t count);
void		*ft_memcpy(void *dest, const void *src, size_t len);
void		*ft_memccpy(void *dest, const void *src, int c, size_t len);
void		*ft_memmove(void *dest, const void *src, size_t len);
int			ft_isascii(int c);
int			ft_isprint(int c);
void		*ft_memchr(const void *memblock, int c, size_t size);
int			ft_memcmp(const void *pointer1, const void *pointer2, size_t size);
int			ft_toupper(int c);
int			ft_tolower(int c);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
char		*ft_strchr(const char *str, int c);
char		*ft_strrchr(const char *str, int c);
char		*ft_strnstr(const char *str, const char *to_find, size_t n);
int			ft_atoi(const char *str);
char		*ft_strstr(char *str, char *to_find);
void		ft_putnbr(int n);
void		*ft_calloc(size_t count, size_t size);
char		*ft_strdup(const char *src);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
char		*ft_itoa(int c);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
int			ft_putptr(unsigned long int n);
int			ft_putnbr_hexa(unsigned int n, int upper, int format);
int			ft_putchar(const char c);
int			ft_putstr(const char *s);
int			ft_putnbru(unsigned int n);
int			ft_printf(const char *s, ...);
int			ft_intlenn(int n);
char		*get_next_line(int fd);

#endif
