/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils_bonus.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dligthar <dligthar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/19 14:47:48 by dligthar      #+#    #+#                 */
/*   Updated: 2023/03/26 14:57:49 by dligthar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

#include <stddef.h>
#include <stdlib.h>

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if ((char)c == '\0' && s[i] == '\0')
		return ((char *)(s + i));
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	int		size_s1;
	char	*s2;

	if (!s1)
		return (NULL);
	size_s1 = ft_strlen(s1);
	s2 = (char *)malloc((size_s1 + 1) * sizeof(char));
	if (!s2)
		return (NULL);
	s2[size_s1] = '\0';
	while (size_s1--)
		s2[size_s1] = s1[size_s1];
	return (s2);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		s1_len;
	int		s2_len;
	char	*result;

	if (s1 && !s2)
		return (ft_strdup(s1));
	else if (!s1 && s2)
		return (ft_strdup(s2));
	else if (!s1 && !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	result = malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	result[s1_len + s2_len] = '\0';
	while (s2_len--)
		result[s1_len + s2_len] = s2[s2_len];
	while (s1_len--)
		result[s1_len] = s1[s1_len];
	return (result);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	len_s;
	char	*result;

	if (!s || !s[0])
		return (ft_strdup(""));
	len_s = 0;
	while (s[len_s])
		len_s++;
	if (start >= len_s)
		return (ft_strdup(""));
	if (len + start > len_s)
		len = len_s - start;
	result = (char *)malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	result[len] = '\0';
	while (len--)
		result[len] = s[start + len];
	return (result);
}
