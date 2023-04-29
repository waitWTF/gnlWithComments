/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thandel <thandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 20:00:55 by thandel           #+#    #+#             */
/*   Updated: 2023/04/28 20:00:56 by thandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
/*#include <stdio.h>

int		main()
{
	char	*line;
	int		fd;

	fd = open("test.txt", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		printf("%s", line);
		if (line == NULL)
			break ;
		free(line);
	}
	close(fd);
}
*/
// This function reads data from a file descriptor into a buffer, until a newline character is encountered or the end of the file is reached.
char	*ft_read_to_leftstr(int fd, char *l_str)
{
	// Allocate memory for a buffer to hold the read data.
	char	*buff;
	int		rd_bytes;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);

	// Initialize the read byte count.
	rd_bytes = 1;

	// Keep reading data into the buffer until a newline character is encountered or the end of the file is reached.
	while (!ft_strchr(l_str, '\n') && rd_bytes != 0)
	{
		// Read data from the file descriptor into the buffer.
		rd_bytes = read(fd, buff, BUFFER_SIZE);

		// Check for errors while reading from the file descriptor.
		if (rd_bytes == -1)
		{
			free(buff);
			return (NULL);
		}

		// Add a null terminator to the end of the read data.
		buff[rd_bytes] = '\0';

		// Append the read data to the left string.
		l_str = ft_strjoin((char *)l_str, buff);
	}

	// Free the buffer and return the updated left string.
	free(buff);
	return (l_str);
}


// This function reads data from a file descriptor and returns one line at a time until the end of the file is reached.
char	*get_next_line(int fd)
{
	// Declare local variables.
	char		*line;
	static char	*l_str;

	// Check for errors with the file descriptor or buffer size.
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		// Free any memory allocated for the leftover string and return NULL.
		if (l_str)
			free(l_str);
		l_str = NULL;
		return (NULL);
	}

	// Read data from the file descriptor into the leftover string.
	l_str = ft_read_to_leftstr(fd, l_str);

	// Check for errors while reading data from the file descriptor.
	if (!l_str)
		return (NULL);

	// Extract one line from the leftover string.
	line = ft_getline(l_str);

	// Create a new leftover string from any remaining data.
	l_str = ft_new_lstr(l_str);

	// Return the extracted line.
	return (line);
}

