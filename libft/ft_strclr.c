/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 13:39:36 by vlikhotk          #+#    #+#             */
/*   Updated: 2017/11/01 13:49:53 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_strclr(char *s)
{
	int i;

	i = 0;
	if (s)
	{
		while (s[i] != '\0')
			i++;
		while (i >= 0)
		{
			s[i] = '\0';
			i--;
		}
	}
}
