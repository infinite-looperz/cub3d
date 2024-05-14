/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split_cub3d.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: seyildir <seyildir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/30 15:49:51 by seyildir      #+#    #+#                 */
/*   Updated: 2024/05/10 17:26:41 by akasiota      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	ft_free2m(char	**data, size_t word)
{
	size_t	i;

	i = 0;
	while (i <= word)
	{
		if (data[i])
			free(data[i]);
		data[i] = NULL;
		i++;
	}
	free(data);
	data = NULL;
}

static int	word_count(char const *s)
{
	int	rtn;

	rtn = 0;
	while (*s)
	{
		if ((is_whitespace(*s) == false) && \
		(is_whitespace(*(s + 1)) || !*(s + 1)))
			rtn++;
		s++;
	}
	return (rtn);
}

static int	word_len(char const *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (is_whitespace(*s))
		s++;
	while (is_whitespace(*s) == false && *s)
	{
		i++;
		s++;
	}
	return (i);
}

static int	word_fill(char const *s, char **d, size_t w_amount)
{
	size_t	i;
	size_t	word;
	size_t	s_size;
	size_t	s_sub;

	i = 0;
	word = 0;
	s_size = ft_strlen(s);
	while (word < w_amount)
	{
		while (is_whitespace(s[i]) && i < s_size)
			i++;
		s_sub = word_len(&s[i]);
		d[word] = ft_substr(s, i, s_sub);
		if (d[word] == 0)
		{
			ft_free2m(d, w_amount);
			return (-1);
		}
		word++;
		i += s_sub;
	}
	return (0);
}

char	**ft_split_cub3d(t_data *data, char const *s)
{
	char	**rtn;
	int		w_amount;

	if (!s)
		return (0);
	w_amount = word_count(s);
	rtn = (char **)ft_calloc_cub3d(data, w_amount + 1, sizeof(char *));
	if (word_fill((char *)s, rtn, w_amount) == -1)
		error_and_exit(data, "Malloc error", 42);
	return (rtn);
}
