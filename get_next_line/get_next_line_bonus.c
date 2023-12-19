/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 18:19:47 by cedmulle          #+#    #+#             */
/*   Updated: 2023/11/02 14:20:56 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

char	*line_reader(int fd, char *line)
{
	char	*temp;
	ssize_t	bytes;

	temp = (char *)malloc(BUFFER_SIZE + 1);
	if (!temp)
		return (NULL);
	bytes = 1;
	while (!ft_strchr(line, '\n') && bytes > 0)
	{
		bytes = read(fd, temp, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(temp);
			return (NULL);
		}
		temp[bytes] = '\0';
		line = ft_strjoin(line, temp);
	}
	free(temp);
	return (line);
}

char	*line_extractor(char *line)
{
	char	*dest;
	int		i;

	i = 0;
	if (!line[i])
		return (NULL);
	while (line[i] && line[i] != '\n')
		i++;
	dest = (char *)malloc(i + 2);
	if (!dest)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		dest[i] = line[i];
		i++;
	}
	if (line[i] == '\n')
	{
		dest[i] = line[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*line_remover(char *line)
{
	char	*dest;
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (!line[i])
	{
		free(line);
		return (NULL);
	}
	dest = (char *)malloc(sizeof(char) * (ft_strlen(line) - i) + 1);
	if (!dest)
		return (NULL);
	i++;
	while (line[i])
		dest[k++] = line[i++];
	dest[k] = '\0';
	free(line);
	return (dest);
}

char	*get_next_line(int fd)
{
	static char	*current_line[OPEN_MAX];
	char		*dest;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (read(fd, 0, 0) == -1)
	{
		free(current_line[fd]);
		current_line[fd] = NULL;
		return (NULL);
	}
	current_line[fd] = line_reader(fd, current_line[fd]);
	if (!current_line[fd])
		return (NULL);
	dest = line_extractor(current_line[fd]);
	current_line[fd] = line_remover(current_line[fd]);
	return (dest);
}
