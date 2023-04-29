/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thandel <thandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 20:00:16 by thandel           #+#    #+#             */
/*   Updated: 2023/04/28 20:00:29 by thandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char *l_str, char *buff)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!l_str)
	{
		l_str = (char *)malloc(1 * sizeof(char));
		l_str[0] = '\0';
	}
	if (!l_str || !buff)
		return (NULL);
	str = malloc(sizeof(char) * ((ft_strlen(l_str) + ft_strlen(buff)) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (l_str)
		while (l_str[++i] != '\0')
			str[i] = l_str[i];
	while (buff[j] != '\0')
		str[i++] = buff[j++];
	str[ft_strlen(l_str) + ft_strlen(buff)] = '\0';
	free(l_str);
	return (str);
}

// This function extracts a line of text from the input that has been stored in the leftover string.
char	*ft_getline(char *l_str)
{
	// Declare local variables.
	int		i;
	char	*str;

	// Find the first newline character in the leftover string.
	i = 0;
	if (!l_str[i])
		return (NULL);
	while (l_str[i] && l_str[i] != '\n')
		i++;

	// Allocate memory for the new string, including space for the newline character.
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);

	// Copy characters from the leftover string up until the first newline character into the new string.
	i = 0;
	while (l_str[i] && l_str[i] != '\n')
	{
		str[i] = l_str[i];
		i++;
	}

	// If the first newline character is found, include it in the new string.
	if (l_str[i] == '\n')
	{
		str[i] = l_str[i];
		i++;
	}

	// Add a null terminator to the end of the new string.
	str[i] = '\0';

	// Return the new string.
	return (str);
}

// This function creates a new leftover string from any remaining data in the original leftover string.
char	*ft_new_lstr(char *l_str)
{
	// Declare local variables.
	int		i;
	int		j;
	char	*str;

	// Find the first newline character in the original leftover string.
	i = 0;
	while (l_str[i] && l_str[i] != '\n')
		i++;

	// If no newline character is found, free the original leftover string and return NULL.
	if (!l_str[i])
	{
		free(l_str);
		return (NULL);
	}

	// Allocate memory for the new leftover string.
	str = (char *)malloc(sizeof(char) * (ft_strlen(l_str) - i + 1));
	if (!str)
		return (NULL);

	// Copy the remaining data after the newline character into the new leftover string.
	i++;
	j = 0;
	while (l_str[i])
		str[j++] = l_str[i++];
	str[j] = '\0';

	// Free the original leftover string and return the new leftover string.
	free(l_str);
	return (str);
}

