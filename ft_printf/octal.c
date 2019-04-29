/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   octal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwispmot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 19:39:11 by nwispmot          #+#    #+#             */
/*   Updated: 2019/04/20 19:39:14 by nwispmot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_printf.h"

void ocheck(t_pf *pf,char **str, char **pre, intmax_t n)
{
	if (ft_strchr(*str, '-') != NULL && pf->flags[zero] == 1)
	{
		*pre[0] = '-';
		*str[0] = '0';
	}
	if (*str[0] == ' ' && *pre[0] == '0')
	{
		*pre[0] = ' ';
		*str[0] = '0';
	}
	if (ft_strchr(*str, '+') != NULL && n != 0 && pf->flags[zero] == 1)
	{
		*pre[0] = '+';
		*str[0] = '0';
	}
}

char	*owidth(t_pf *pf, char *str, intmax_t n)
{
	int		i;
	int		len;
	char	*pre;

	i = -1;
	len = pf->flags[width] - (int) ft_strlen(str);
	pre = (char *) malloc((sizeof(char)) * ((pf->flags[width] - (int) ft_strlen(str)) + 1));
	while (++i < len)
	{
		if (pf->flags[zero] == 1)
			pre[i] = '0';
		else
			pre[i] = ' ';
	}
	ocheck(pf, &str, &pre, n);
	if (str[0] == '+' && str[1] == '0' && pf->flags[zero] == 1)
	{
		pre[0] = '+';
		str[0] = '0';
	}
	pre[i] = '\0';
	if (pf->flags[minus] == 0)
		return(str = ft_strjoin(pre, str));
	else
		return (str = ft_strjoin(str, pre));
}

char *oplus(char *str)
{
	char *plus;
	char *fresh;

	plus = ft_strdup("+");
	fresh = ft_strjoin(plus, str);
	return (fresh);
}

char *oprec(t_pf *pf, char *str)
{
	int len;
	int i;
	char *pre;

	i = 0;
	len = pf->flags[prec] - (int)ft_strlen(str);
	if (ft_strchr(str, '-') != NULL || ft_strchr(str, '+') != NULL)
		len++;
	pre = (char*)malloc((sizeof(char)) * (len + 1));
	while(i < len)
	{
		pre[i] = '0';
		i++;
	}
	if (ft_strchr(str, '-') != NULL)
	{
		pre[0] = '-';
		str[0] = '0';
	}
	if (ft_strchr(str, '+') != NULL)
	{
		pre[0] = '+';
		str[0] = '0';
	}
	pre[i] = '\0';
	str = ft_strjoin(pre, str);
	ft_strdel(&pre);
	return (str);
}

void conv_o(t_pf *pf, va_list ap)
{
	uintmax_t n;
	char *str;
	char *pre;

	if(pf->flags[l] == 1)
		n = va_arg(ap, unsigned long int);
	else if(pf->flags[ll] == 1)
		n = va_arg(ap, unsigned long long int);
	else
		n = va_arg(ap, unsigned int);
	if(pf->flags[h] == 1)
		n = (unsigned short int)n;
	if(pf->flags[hh] == 1)
		n = (unsigned char) n;

	str = ft_itoa_base(n, 8, 0);
    if (pf->flags[sharp] == 1)
        str = ft_sharp(str);
	if (pf->flags[plus] == 1 && n > 0)
		str = oplus(str);
	if (pf->flags[prec] >= (int)(ft_strlen(str)) || ( pf->flags[prec] > (int)(ft_strlen(str) - 1) && ft_strchr(str, '-') != NULL))
		str = oprec(pf, str);
	else if (pf->flags[prec] == 0 && str[0] == '0' && str[1] == '\0')
		str[0] = '\0';
	pre = ft_strdup(" ");
	if (pf->flags[plus] == 1 && n == 0)
		str = oplus(str);
	if (pf->flags[space] == 1)
		str = ft_strjoin(pre, str);
	if (pf->flags[width] != 0 && (pf->flags[width] > (int)ft_strlen(str)))
		str = owidth(pf, str, n);
	pf->size += ft_strlen(str);
	ft_putstr(str);
}