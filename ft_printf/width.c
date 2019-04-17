#include "ft_printf.h"

char	*iwidth(t_pf *pf, char *str, int n)
{
	int		i;
	int		len;
	char	*pre;
	char	*fr;

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
	if (n < 0 && pf->flags[zero] == 1)
	{
		pre[0] = '-';
		str[0] = '0';
	}
	pre[i] = '\0';
	if (pf->flags[minus] == 0)
	{
		fr = str;
		str = ft_strjoin(pre, str);
		ft_strdel(&fr);
		ft_strdel(&pre);
	}
	else if (pf->flags[minus] == 1)
	{
		fr = str;
		str = ft_strjoin(str, pre);
		ft_strdel(&fr);
		ft_strdel(&pre);
	}
	return (str);
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