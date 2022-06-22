/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdi-lell <bdi-lell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 09:55:29 by bdi-lell          #+#    #+#             */
/*   Updated: 2022/06/22 09:56:19 by bdi-lell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line_bonus.h"

static char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	c_copy;
	char	*s_copy;

	c_copy = (unsigned char) c;
	s_copy = (char *)s;
	i = 0;
	while (s_copy[i] != '\0')
	{
		if (s_copy[i] == c_copy)
			return (s_copy + i);
		i++;
	}
	if (c_copy == '\0')
		return (s_copy + i);
	return (NULL);
}

static char	*ft_copy_line(int fd, char *was_read, char *buffer, int byte_read)
{
	char	*temp;

	temp = was_read;
	was_read = ft_strjoin(was_read, buffer);
	free(temp);
	while (byte_read > 0 && ft_strchr(buffer, '\n') == NULL)
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		buffer[byte_read] = '\0';
		temp = was_read;
		was_read = ft_strjoin(was_read, buffer);
		free(temp);
	}
	return (was_read);
}

static char	*ft_read(int fd, char *nextl)
{
	int		byte_read;
	char	*buffer;
	char	*was_read;

	was_read = (char *) calloc(1, sizeof(char *));
	buffer = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (nextl != NULL && *nextl != 0)
		byte_read = ft_strlcpy(buffer, nextl, ft_strlen(nextl) + 1);
	else
		byte_read = read(fd, buffer, BUFFER_SIZE);
	free(nextl);
	if (byte_read > 0)
	{
		buffer[byte_read] = '\0';
		was_read = ft_copy_line(fd, was_read, buffer, byte_read);	
	}
	else
	{
		free(was_read);
		was_read = NULL;
	}
	free(buffer);
	return (was_read);
}

static char	*trim(char **nextl)
{
	int		i;
	char	*temp;
	char	*result_line;

	temp = *nextl;
	i = 0;
	if (ft_strchr(temp, '\n') != NULL)
	{
		while (temp[i] != '\n')
			i++;
	}
	else
		i = ft_strlen(temp);
	result_line = ft_substr(temp, 0, (i + 1));
	*nextl = ft_substr(temp, i + 1, ft_strlen(temp));
	free(temp);
	return (result_line);
}

char	*get_next_line(int fd)
{
	static char	*nextl[1024];
	char		*line;

	if(fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	nextl[fd] = ft_read(fd, nextl[fd]);
	line = NULL;
	if (nextl[fd] != NULL)
		line = trim(&nextl[fd]);
	return (line);
}
