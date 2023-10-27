/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:01:29 by jgoudema          #+#    #+#             */
/*   Updated: 2023/10/27 16:56:22 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	*ft_free(char *s1, char *s2)
{
	free(s1);
	if (s2)
		free(s2);
	return (NULL);
}

char	*ft_find_line(char *str)
{
	char	*line;
	int		i;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	line = malloc((i + 1) * sizeof(char));
	if (!line)
		return (NULL);
	line[i--] = 0;
	while (i >= 0)
	{
		line[i] = str[i];
		i--;
	}
	return (line);
}

char	*ft_cut(char *str)
{
	size_t	i;
	size_t	j;
	char	*res;

	i = 0;
	while (str[i] != '\n' && str[i])
		i++;
	if (!str[i])
		return (ft_free(str, 0));
	res = malloc((ft_strlen(str) - i + 1) * sizeof(char));
	if (!res)
		return (ft_free(str, 0));
	j = 0;
	i++;
	while (str[i])
		res[j++] = str[i++];
	res[j] = 0;
	free(str);
	return (res);
}

char	*ft_get_line(int fd, char *str)
{
	char	*buff;
	char	*temp;
	int		rd;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (ft_free(str, 0));
	rd = 1;
	while (rd != 0)
	{
		rd = read(fd, buff, BUFFER_SIZE);
		if (rd == -1)
			return (ft_free(str, buff));
		buff[rd] = 0;
		temp = ft_strjoin(str, buff);
		free(str);
		str = temp;
		if (!str)
			return (ft_free(buff, 0));
		if (ft_strchr(str, '\n') != 0)
			break ;
	}
	free(buff);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*b[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	if (b[fd] == NULL)
		b[fd] = ft_calloc(1, sizeof(char));
	if (!b[fd])
		return (NULL);
	b[fd] = ft_get_line(fd, b[fd]);
	if (!b[fd])
		return (NULL);
	line = ft_find_line(b[fd]);
	if (!line)
	{
		free(b[fd]);
		b[fd] = 0;
		return (NULL);
	}
	b[fd] = ft_cut(b[fd]);
	return (line);
}

// int	main(void)
// {
// 	int fd = open("test.txt", O_RDONLY);
// 	//int fd2 = open("test2.txt", O_RDONLY);
// 	//int fd3 = open("test3.txt", O_RDONLY);

// 	printf("%s.", get_next_line(fd));
// 	// printf("%s.", get_next_line(fd2));
// 	// printf("%s.", get_next_line(fd2));
// 	// printf("%s.", get_next_line(fd));
// 	// printf("%s.", get_next_line(fd2));
// 	// printf("%s.", get_next_line(fd));
// 	// printf("%s.", get_next_line(fd2));
// 	// printf("%s.", get_next_line(fd));
// 	// printf("%s.", get_next_line(fd2));
// 	// printf("%s.", get_next_line(fd3));
// }
