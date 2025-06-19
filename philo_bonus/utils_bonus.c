/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:16:17 by mourhouc          #+#    #+#             */
/*   Updated: 2025/06/19 17:40:19 by mourhouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str && str[len])
		len++;
	return (len);
}

size_t	nb_digit_id(size_t num)
{
	size_t	count;

	count = 0;
	if (num == 0)
		return (1);
	while (num != 0)
	{
		count++;
		num /= 10;
	}
	return (count);
}

char	*ft_itoa(size_t id)
{
	size_t	nb_digit;
	char	*result;

	nb_digit = nb_digit_id(id);
	result = malloc((nb_digit + 1) * sizeof(char));
	if (!result)
		return (NULL);
	result[nb_digit] = '\0';
	while (id != 0)
	{
		result[--nb_digit] = (id % 10) + '0';
		id /= 10;
	}
	return (result);
}

char	*get_name_sem(size_t id, char *name)
{
	char	*result;
	char	*string_n;
	size_t	i;
	size_t	len_name;
	size_t	len_id;

	i = 0;
	string_n = ft_itoa(id);
	if (!string_n)
		return (NULL);
	len_name = ft_strlen(name);
	len_id = ft_strlen(string_n);
	result = malloc((len_name + len_id + 1) * sizeof(char));
	if (!result)
		return (free(string_n), NULL);
	result[len_name + len_id] = '\0';
	while (++i <= len_name)
		result[i - 1] = name[i - 1];
	i = 0;
	while (++i <= len_id)
		result[len_name + (i - 1)] = string_n[i - 1];
	free(string_n);
	return (result);
}
