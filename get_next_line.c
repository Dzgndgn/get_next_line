/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddogan <ddogan@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 13:59:16 by ddogan            #+#    #+#             */
/*   Updated: 2023/11/07 18:13:15 by ddogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*getstring(int fd, char *str)
{
	char	*buff;
	int		checkbyte;

	checkbyte = 1;
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	while (!(ft_strchr (str, '\n')) && checkbyte != 0)
	{
		checkbyte = read(fd, buff, BUFFER_SIZE);
		if (checkbyte == -1)
		{
			free (buff);
			free (str);
			return (NULL);
		}
		buff[checkbyte] = '\0';
		str = ft_strjoin(str, buff);
	}
	free(buff);
	return (str);
}

char	*line(char *buffer)
{
	int		n;
	char	*ptr;

	n = 0;
	if (buffer[n] == '\0')
		return (NULL);
	while (buffer[n] != '\n' && buffer[n] != '\0')
		n++;
	ptr = (char *) malloc((n + 2) * sizeof(char));
	if (!ptr)
		return (NULL);
	n = 0;
	while (buffer[n] != '\n' && buffer[n] != '\0')
	{
		ptr[n] = buffer[n];
		n++;
	}
	if (buffer[n] == '\n')
	{
		ptr[n] = buffer[n];
		n++;
	}
	ptr[n] = '\0';
	return (ptr);
}

char	*next_line(char *str)
{
	int		i;
	int		a;
	char	*ptr;

	a = 0;
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	i++;
	ptr = (char *)malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!ptr)
	{
		free (ptr);
		return (NULL);
	}
	while (str[i] != '\0')
		ptr[a++] = str[i++];
	ptr[a] = '\0';
	free (str);
	return (ptr);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*ptr;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = getstring(fd, str);
	if (!str)
		return (NULL);
	ptr = line (str);
	str = next_line (str);
	return (ptr);
}
/*char *get_next_line(int fd)
{
    char *str;
    char *ptr;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    static char *remainder = NULL;

    str = getstring(fd, remainder);
    if (!str)
        return (NULL);

    ptr = line(str);

    if (str == ptr)
        remainder = NULL;
    else
        remainder = next_line(str);

    return (ptr);
}*/
