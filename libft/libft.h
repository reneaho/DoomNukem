/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raho <raho@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 17:57:33 by okinnune          #+#    #+#             */
/*   Updated: 2023/03/25 20:53:24 by raho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include "get_next_line.h"
# include <math.h>

# ifndef INT_MAX
#  define INT_MAX 2147483647
# endif

/* memory	*/
void			*ft_memset(void *ptr, int value, size_t num);
void			*ft_memcpy(void *dst, const void *src,
					size_t n);
void			*ft_memccpy(void *dst, const void *src,
					int c, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
char			*ft_memdup(const void *m, size_t n);
void			*ft_memjoin(const void *dst, const void *src, size_t dst_len, \
							size_t src_len);
int				ft_memcmp(const void *ptr1, const void*ptr2, size_t num);
void			ft_memdel(void **ap);
void			*ft_memalloc(size_t size);
void			*ft_memchr(const void *ptr, int c, size_t n);
void			ft_bzero(void *s, size_t n);
void			protected_free(void	*ptr);

/* strings	*/
size_t			ft_strlcat(char *dst, const char *src, size_t siz);
size_t			ft_strlen(const char *str);
char			*ft_strchr(const char *str, int character);
char			*ft_strrchr(const char *str, int character);
char			*ft_strstr(const char *haystack, const char *needle);
char			*ft_strnstr(const char *haystack, const char *needle,
					size_t len);
char			*ft_strdup(const char *str);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strcat(char *destination, const char *source);
char			*ft_strncat(char *s1, const char *s2, size_t n);
char			*ft_strcpy(char *dest, const char *src);
void			ft_strdel(char **as);
char			*ft_strnew(size_t size);
void			ft_strclr(char *s);
void			ft_strfill(char *s, char c); /*extra*/
char			**ft_strsplit(const char *s, char c);
char			**ft_strscrape(const char*s, char *delims);
void			ft_strreplace(char *str, int c1, int c2);
char			*ft_strncpy(char *dest, const char *src, size_t num);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
int				ft_strequ(const char *s1, const char *s2);
int				ft_strnequ(const char *s1, const char *s2, size_t n);
char			*ft_strmap(const char *s, char (*f)(char));
char			*ft_strmapi(const char *s, char (*f)(unsigned int, char));
char			*ft_strtrim(const char *s);
char			*ft_strsub(const char *s, unsigned int start, size_t len);
char			*ft_strjoin(const char *s1, const char *s2);
int				ft_isdigit(int c);
char			*ft_itoa(int n);
char			*ft_ftoa(float f, int dec);
int				ft_isprint(int c);
int				ft_isspace(int c);
int				ft_isalpha(int c);
int				ft_atoi(const char *str);
int				ft_tolower(int c);
int				ft_toupper(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
void			ft_putstr(const char *s);
void			ft_putstr_fd(const char *s, int fd);
void			ft_putendl(const char *s);
void			ft_putendl_fd(const char *s, int fd);
void			ft_putchar(char c);
void			ft_putchar_fd(char s, int fd);
void			ft_putnbr(int i);
void			ft_putnbr_fd(int n, int fd);

/* "math" */
int				ft_digitcount(int n);/*extra*/
int				ft_pow(int n, int p);/*extra*/
int				ft_abs(int n);/*extra*/
float			ft_absf(float f);
int				ft_sqrt(int nb);/*extra*/
int				ft_clamp(int val, int min, int max);
int				ft_min(int i1, int i2);
int				ft_max(int i1, int i2);
float			ft_minf(float f1, float f2);
float			ft_maxf(float f1, float f2);
float			ft_clampf(float val, float min, float max);
float			ft_flerp(float from, float to, float delta);
double			ft_degtorad(double angle);
float			ft_fmovetowards(float f1, float f2, float delta);

/* lists */
typedef struct s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}	t_list;

t_list			*ft_lstnew(const void *content, size_t content_size);
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
// Actually deletes the list without the dumb function pointer shenanigans
// Calls free for each content
void			listdel(t_list **alst);
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstapp(t_list **alst, t_list *new);/*extra*/
int				ft_listlen(t_list *lst);

char			*ft_strcdup(const char *str, char c);
char			*ft_strncpy_term(char *dest, const char *src, size_t num);
int				get_next_line(const int fd, char **line);
double			ft_atof(const char *str);

#endif