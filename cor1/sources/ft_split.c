#include "cub3d.h"

#include <string.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	s_len;
	size_t	i;

	if (!s)
		return (NULL);
	s_len = strlen(s);
	if (start >= s_len)
		return (strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	substr = (char *)malloc(len + 1);
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}


void	free_memory(char **ptr_ss, long index)
{
	while (index)
	{
		free(ptr_ss[index]);
		index--;
	}
	free(ptr_ss);
}

long	count_of_words(char const *s, char c)
{
	long	count;
	long	found_word;

	found_word = 1;
	count = 0;
	while (*s)
	{
		if (*s == c)
			found_word = 1;
		else
		{
			if (found_word)
			{
				count++;
				found_word = 0;
			}
		}
		s++;
	}
	return (count + 1);
}

long	word_len(char const *s, char c, long i)
{
	long	len;

	len = 0;
	while (s[i] && s[i] != c)
	{
		len++;
		i++;
	}
	return (len);
}

char	**ft_split(char const *s, char c, int *size, long *i)
{
	char	**res;
	long	j;

	if (!s)
		return (NULL);
	res = (char **)malloc((count_of_words(s, c)) * sizeof(char *));
	*i = 0;
	j = -1;
	if (!res)
		return (NULL);
	while (++j < count_of_words(s, c) - 1)
	{
		while (s[*i] == c)
			(*i)++;
		res[j] = ft_substr(s, (*i), word_len(s, c, (*i)));
		if (!res[j])
		{
			free_memory(res, j);
			return (NULL);
		}
		(*i) += word_len(s, c, (*i));
	}
	*size = j;
	res[j] = 0;
	return (res);
}

