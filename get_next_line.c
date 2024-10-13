/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 09:52:05 by tamehri           #+#    #+#             */
/*   Updated: 2023/12/06 20:21:09 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*stat;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
	{
		if (stat) // this line was added after validation
		{
			free(stat); // this line was added after validation
			stat = NULL; // this line was added after validation
		}
		return (NULL);
	}
	stat = read_to_nl(stat, fd);
	if (!stat)
		return (NULL);
	line = ft_before_nl(stat);
	stat = ft_after_nl(stat);
	return (line);
}

char	*read_to_nl(char *stat, int fd)
{
	char	*buff;
	int		bytes;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	bytes = 1;
	while (!ft_strchr(stat) && bytes)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buff);
			buff = NULL; // this line was added after validation
			return (NULL);
		}
		*(buff + bytes) = '\0';
		stat = ft_strjoin(stat, buff);
	}
	free(buff);
	buff = NULL; // this line was added after validation
	return (stat);
}

char	*ft_before_nl(char *stat)
{
	char	*line;
	int		i;

	if (!*stat)
		return (NULL);
	i = 0;
	while (*(stat + i) && *(stat + i) != '\n')
		i++;
	line = malloc(sizeof(char) * i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (*(stat + i) && *(stat + i) != '\n')
	{
		*(line + i) = *(stat + i);
		i++;
	}
	if (*(stat + i) == '\n')
		*(line + i++) = '\n';
	*(line + i) = '\0';
	return (line);
}

char	*ft_after_nl(char *stat)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	while (*(stat + i) && *(stat + i) != '\n')
		i++;
	if (!*(stat + i))
	{
		free(stat);
		return (stat = NULL, NULL); // This line was modified after validation (stat = NULL)
	}
	line = malloc(sizeof(char) * (ft_strlen(stat + i) + 1));
	if (!line)
	{
		free(stat);
		return (stat = NULL, NULL); // This line was modified after validation (stat = NULL)
	}
	i++;
	j = 0;
	while (*(stat + i))
		*(line + j++) = *(stat + i++);
	*(line + j) = '\0';
	free(stat);
	return (stat = NULL, line); // This line was modified after validation (stat = NULL)
}
