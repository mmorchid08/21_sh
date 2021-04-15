/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_commande.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <mmorchid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 17:12:40 by mmorchid          #+#    #+#             */
/*   Updated: 2021/04/15 13:27:48 by mmorchid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"

int	check_for_exclamation_mark(t_tokens *tokens)
{
	int	index;

	index = 1;
	while (tokens)
	{
		if (ft_strcmp("!", tokens->data) == 0 && index == 2)
			return (1);
		index++;
		tokens = tokens->next;
	}
	return (0);
}

int	count_tokens(t_tokens *tokens)
{
	int	counter;

	counter = 0;
	while (tokens)
	{
		counter++;
		tokens = tokens->next;
	}
	return (counter);
}

int	ft_is_number(char *number)
{
	int	i;

	i = 0;
	while (number[i])
	{
		if (ft_isdigit(number[i]) == 1)
			i++;
		else
			return (0);
	}
	return (1);
}

int	ft_binary(char *arg1, char *arg2, test_operation ope)
{
	int	num1;
	int	num2;

	num1 = ft_is_number(arg1);
	num2 = ft_is_number(arg2);
	if (num1 == 0 || num2 == 0)
		return (ft_error_arg(arg1, arg2, num1));
	num1 = ft_atoi(arg1);
	num2 = ft_atoi(arg2);
	if (num1 == num2 && ope == OPERATER_AL_E)
		return (0);
	if (num1 > num2 && ope == OPERATER_AL_G)
		return (0);
	if (num1 <= num2 && ope == OPERATER_AL_L_E)
		return (0);
	return (1);
}

int	test_commade(t_tokens *tokens)
{
	int	arg_num;
	int	dif;

	arg_num = count_tokens(tokens->args) - 1;
	dif = check_for_exclamation_mark(tokens->args);
	arg_num -= dif;
	tokens->args = tokens->args->next;
	if (dif == 1)
		tokens->args = tokens->args->next;
	if (arg_num == 0)
		return (1 ^ dif);
	if (arg_num == 1)
		return ((!ft_strequ("", tokens->data)) ^ dif);
	if (arg_num == 2)
		return (check_unary_op(tokens->args) ^ dif);
	if (arg_num == 3)
		return (check_binary_op(tokens->args) ^ dif);
	if (arg_num >= 4)
		ft_putendl_fd("42_sh: test: too many arguments", 2);
	return (2);
}
