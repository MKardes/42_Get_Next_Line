/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 23:03:43 by mkardes           #+#    #+#             */
/*   Updated: 2022/02/19 12:40:19 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_putten(char *putline)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (putline[i] != '\0' && putline[i] != '\n')
		i++;
	if (!putline[i])
	{
		free(putline);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(putline) - i));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (putline[i + j] != '\0')
	{
		str[j] = putline[j + i];
		j++;
	}
	str[j] = '\0';
	free(putline);
	return (str);
}

char	*get_main_line(char *putline)
{
	int		i;
	char	*str;

	i = 0;
	if (!putline[i])
		return (NULL);
	while (putline[i] != '\0' && putline[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * i + 2);
	if (!str)
		return (NULL);
	i = 0;
	while (putline[i] != '\0' && putline[i] != '\n')
	{
		str[i] = putline[i];
		i++;
	}
	if (putline[i] == '\n')
	{
		str[i] = putline[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*get_read(int fd, char *putline)
{
	char	*buff;
	int		reader;

	buff = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (0);
	reader = 1;
	while (!ft_strchr(putline, '\n') && reader != 0)
	{
		reader = read(fd, buff, BUFFER_SIZE);
		if (reader == -1)
		{
			free(buff);
			return (NULL);
		}			
		buff[reader] = '\0';
		putline = ft_strjoin(putline, buff);
	}
	free(buff);
	return (putline);
}

//get_read Fonksiyonu putline'a eşitlemeyince (null) geri döndürüyor.
char	*get_next_line(int fd)
{
	char		*mainline;
	static char	*putline[10000];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	putline[fd] = get_read(fd, putline[fd]);
	if (!putline[fd])
		return (NULL);
	mainline = get_main_line(putline[fd]);
	putline[fd] = get_putten(putline[fd]);
	return (mainline);
}
/*
int	main()
{
	int		fd = open("src", O_RDONLY);
	int		dsfd = open("dst", O_RDWR);
	int     fd1 = open("src1", O_RDONLY);
    int     dsfd1 = open("dst1", O_RDWR);
	int     fd2 = open("src2", O_RDONLY);
    int     dsfd2 = open("dst2", O_RDWR);
	int		i = 0;
	char	**str;

	str = (char **)malloc(sizeof(char*) * 15);
	while (i < 15)
	{
		str[i] = get_next_line(fd);
		write(dsfd, str[i], ft_strlen(str[i]));
		i++;
		str[i] = get_next_line(fd1);
		write(dsfd1, str[i], ft_strlen(str[i]));
		i++;
		str[i] = get_next_line(fd2);
        write(dsfd2, str[i], ft_strlen(str[i]));
        i++;
	}
	i = 0;
	while (i < 15)
	{
		printf("%s\n",str[i]);
		i+=1;
	}
}*/
