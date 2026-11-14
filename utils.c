/*
Este archivo colecciona 5 funciones que se usan en diferentes 
apartados: 
-ft_strlen: cuenta el número de caracteres de la cadena
-ft_strcmp: compara 2 cadenas de texto y devuelve la diferencia ASCII (si hay)
-ft_putstr: imprime la letra que le pidas (se usa en bucles)
-is_number: valida que todos los caracteres de la cadena sean números
-skip_zeros: omite los ceros de cada cadena
*/
#include "rush02.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

int	is_number(char *str)
{
	int	i;

	if (str[0] == '\0')
		return (0);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

char	*skip_zeros(char *str)
{
	while (str[0] == '0' && str[1] != '\0')
		str++;
	return (str);
}
