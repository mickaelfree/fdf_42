/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isutils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:34:32 by mickmart          #+#    #+#             */
/*   Updated: 2025/04/20 16:43:14 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(char c)
{
	return ((c >= '0' && c <= '9'));
}

int	ft_isspace(char c)
{
	return ((c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f'
			|| c == '\v'));
}

int	ft_ishex(char c)
{
	return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A'
			&& c <= 'F'));
}

int	ft_isnothexformat(char *hex)
{
	int	i;

	i = 0;
	if (!hex || !hex[0] || !hex[1])
		return (0);
	if (hex[0] == '0' && (hex[1] == 'x' || hex[1] == 'X'))
	{
		hex += 2;
		if (!hex[0])
			return (0);
		while (hex[i])
		{
			if (!ft_ishex(hex[i]) || i > 6)
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

int	pos_in_str(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}
