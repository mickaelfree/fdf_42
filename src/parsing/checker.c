/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:22:55 by mickmart          #+#    #+#             */
/*   Updated: 2025/04/18 16:12:34 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

static int	check_file_extension(char *filename)
{
	char	*ext;

	ext = ft_strrchr(filename, '.');
	if (!ext || ft_strcmp(ext, ".fdf") != 0)
		return (0);
	return (access(filename, R_OK) != -1);
}

static int	is_valid_format(char *line)
{
	int	i;
	int	digit_found;

	i = 0;
	digit_found = 0;
	while (line && line[i])
	{
		if (ft_isdigit(line[i]) || (line[i + 1] && (line[i] == '-'
					&& ft_isdigit(line[i + 1]))))
			digit_found = 1;
		else if (line[i] == ',' && digit_found)
		{
			if (ft_ishexformat(&line[i + 1]))
				return (0);
			i += 8;
		}
		else if (!ft_isspace(line[i]) && line[i] != '\n')
			return (0);
		i++;
	}
	return (digit_found);
}

static int	count_elements(char *line)
{
	int	count;
	int	i;
	int	in_number;

	count = 0;
	i = 0;
	in_number = 0;
	while (line && line[i])
	{
		if (!ft_isspace(line[i]) && line[i] != '\n' && !in_number)
		{
			in_number = 1;
			count++;
		}
		else if (ft_isspace(line[i]) || line[i] == '\n')
			in_number = 0;
		i++;
	}
	return (count);
}

static int	check_map_content(int fd, char *line)
{
	int	first_width;
	int	current_width;

	first_width = count_elements(line);
	free(line);
	line = get_next_line(fd);
	while (line)
	{
		if (!is_valid_format(line))
		{
			free(line);
			return (0);
		}
		current_width = count_elements(line);
		free(line);
		if (current_width != first_width)
			return (0);
		line = get_next_line(fd);
	}
	return (first_width > 0);
}

int	checker_map(char *filename)
{
	int		fd;
	int		result;
	char	*line;

	if (!filename || !check_file_extension(filename))
		return (0);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	if (!line || !is_valid_format(line))
	{
		free(line);
		return (0);
	}
	result = check_map_content(fd, line);
	close(fd);
	return (result);
}
