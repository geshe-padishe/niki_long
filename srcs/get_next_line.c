/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngenadie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 21:04:55 by ngenadie          #+#    #+#             */
/*   Updated: 2022/02/08 21:05:02 by ngenadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"
#include <unistd.h>

int	ft_nl_index(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_realloc(char *str, char *buff, int len)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	buff[len] = '\0';
	len = ft_strlen(str) + ft_strlen(buff);
	new_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	while (buff[j])
		new_str[i++] = buff[j++];
	new_str[i] = '\0';
	free(str);
	str = NULL;
	return (new_str);
}

char	*ft_send_clean(char **s, char *str, int nl_index)
{
	int		i;
	char	*new_str;

	i = -1;
	new_str = NULL;
	*s = (char *)malloc(sizeof(char) * (nl_index + 1));
	if (!(*s))
		return (NULL);
	while (str[++i] && str[i] != '\n')
		(*s)[i] = str[i];
	(*s)[i] = '\0';
	i = 0;
	if (ft_one_line_malloc(&new_str, ft_strlen(str) - nl_index + 1) == -1)
		return (free(str), str = NULL, NULL);
	while (str[nl_index + i])
	{
		new_str[i] = str[nl_index + i];
		i++;
	}
	new_str[i] = '\0';
	free(str);
	str = NULL;
	return (new_str);
}

int	get_next_line(int fd, char **line)
{
	int			nl_index;
	char		buff[BUFFER_SIZE + 1];
	static char	*str = NULL;
	int			len;

	len = 1;
	if (fd < 0 || BUFFER_SIZE <= 0 || line == NULL)
		return (-1);
	if (str == NULL)
	{
		str = malloc(BUFFER_SIZE + 1);
		if (!(str))
			return (-1);
		str[0] = 0;
	}
	while (ft_nl(&nl_index, str) == 0 && ft_len(&len, fd, buff) > 0)
	{
		str = ft_realloc(str, buff, len);
		if (!(str) || len == -1)
			return (-1);
	}
	return (get_next_line2(&str, &line, nl_index, len));
}

/*
**int main(int ac, char **av)
**{
**	char *s = NULL;
**	int fd;
**	(void)ac;
**	int n = 0;
**	int ret;
**	(void)n;
**	int i = 0;
**
**	if ((fd = open(av[1], O_RDONLY)) == -1)
**		return (-1);
**	while ((ret = get_next_line(fd, &s)) == 1)
**	{
**		if (ret == -1)
**			return -1;
**		printf("i: %i, ret: %i, line: %s\n", i, ret, s);
**		//printf("n = %i\n", n++);
**		free(s);
**		i++;
**		printf("-----------------------------------------------------\n");
**	}
**	printf("ret: %i", ret);
**	//	system("leaks a.out");
**	return (ret);
**}
*/
