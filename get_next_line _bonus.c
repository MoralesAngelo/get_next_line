/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:43:36 by mac               #+#    #+#             */
/*   Updated: 2024/11/22 16:15:58 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.bonus.h"
#include <fcntl.h>
#include <stdio.h>

static char	*ft_trim_buffer(char *buffer)
{
	int		i;
	int		j;
	char	*new_buffer;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	new_buffer = (char *)malloc(ft_strlen(buffer) - i);
	if (!new_buffer)
		return (NULL);
	i++;
	while (buffer[i])
		new_buffer[j++] = buffer[i++];
	new_buffer[j] = '\0';
	free(buffer);
	return (new_buffer);
}

static char	*ft_join_and_free(char *buffer, char *temp)
{
	char	*new_buffer;

	new_buffer = ft_strjoin(buffer, temp);
	if (!new_buffer)
	{
		free(buffer);
		return (NULL);
	}
	free(buffer);
	return (new_buffer);
}

static char	*ft_trybuffer(char *buffer)
{
	if (!buffer)
	{
		buffer = (char *)malloc(1);
		if (!buffer)
			return (NULL);
		buffer[0] = '\0';
	}
	return (buffer);
}

static char	*ft_read_to_buffer(int fd, char *buffer)
{
	char	*temp;
	int		bytes_read;

	temp = (char *)malloc(BUFFER_SIZE + 1);
	if (!temp)
		return (NULL);
	buffer = ft_trybuffer(buffer);
	while (!ft_strchr(buffer, '\n'))
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(temp), free(buffer), NULL);
		if (bytes_read == 0)
			return (free(temp), buffer);
		temp[bytes_read] = '\0';
		buffer = ft_join_and_free(buffer, temp);
		if (!buffer)
			return (free(temp), NULL);
	}
	return (free(temp), buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = ft_read_to_buffer(fd, buffer[fd]);
	if (!buffer[fd] || *buffer[fd] == '\0')
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	line = ft_extract_line(buffer[fd]);
	buffer[fd] = ft_trim_buffer(buffer[fd]);
	return (line);
}