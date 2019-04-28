#include "ft_printf.h"


void check(t_pf *pf,char **str, char **pre, intmax_t n)
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

char	*iwidth(t_pf *pf, char *str, intmax_t n)
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
	check(pf, &str, &pre, n);
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


char	*swidth(t_pf *pf, char *str)
{
	int		i;
	int		len;
	char	*pre;

	i = 0;
	len = pf->flags[width] - (int) ft_strlen(str);
	pre = (char *) malloc((sizeof(char)) * (len + 1));
	while (i < len)
	{
		if (pf->flags[zero] == 1)
			pre[i] = '0';
		else
			pre[i] = ' ';
		i++;
	}
	pre[i] = '\0';
	if (pf->flags[minus] == 0)
		str = ft_strjoin(pre, str);
	else if (pf->flags[minus] == 1)
		str = ft_strjoin(str, pre);
	return (str);
}
