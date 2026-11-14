/*
El archivo que convierte el número en palabras, de 3 en 3 cifras:
-pad_number: añade ceros a la izquierda hasta que la longitud sea
múltiplo de 3
ej: "1234567" -> "001234567"
-say_group: dice un bloque de 3 cifras (centena, decena y unidad)
ej: "342" -> three hundred forty two
-say_all_groups: recorre todos los bloques y detrás de cada uno dice
su escala (thousand, million...). Los bloques "000" se saltan
-say_number: dice el número entero. El 0 va aparte, porque su bloque
es "000" y no se diría nada
-convert: primero hace un ensayo sin escribir para ver si están todas
las palabras, y si están lo repite escribiendo. Se llama desde main.c
*/
#include "rush02.h"

static char	*pad_number(char *nb)
{
	char	*padded;
	int		len;
	int		zeros;
	int		i;

	len = ft_strlen(nb);
	zeros = (3 - len % 3) % 3;
	padded = malloc(zeros + len + 1);
	if (padded == NULL)
		return (NULL);
	i = 0;
	while (i < zeros)
	{
		padded[i] = '0';
		i++;
	}
	while (i < zeros + len)
	{
		padded[i] = nb[i - zeros];
		i++;
	}
	padded[i] = '\0';
	return (padded);
}

static int	say_group(t_dict *dict, char *g)
{
	if (g[0] != '0')
	{
		if (!say_digits(dict, g[0], '\0') || !say_word(dict, "100"))
			return (0);
	}
	if (g[1] == '1')
		return (say_digits(dict, '1', g[2]));
	if (g[1] != '0' && !say_digits(dict, g[1], '0'))
		return (0);
	if (g[2] != '0')
		return (say_digits(dict, g[2], '\0'));
	return (1);
}

static int	say_all_groups(t_dict *dict, char *nb)
{
	int	len;
	int	i;

	len = ft_strlen(nb);
	i = 0;
	while (i < len)
	{
		if (nb[i] != '0' || nb[i + 1] != '0' || nb[i + 2] != '0')
		{
			if (!say_group(dict, nb + i))
				return (0);
			if (len - i - 3 > 0 && !say_scale(dict, len - i - 3))
				return (0);
		}
		i = i + 3;
	}
	return (1);
}

static int	say_number(t_dict *dict, char *nb)
{
	char	*padded;
	int		ok;

	if (nb[0] == '0')
		return (say_word(dict, "0"));
	padded = pad_number(nb);
	if (padded == NULL)
		return (0);
	ok = say_all_groups(dict, padded);
	free(padded);
	return (ok);
}

int	convert(t_dict *dict, char *nb)
{
	dict->print = 0;
	if (!say_number(dict, nb))
		return (0);
	dict->print = 1;
	dict->first = 1;
	say_number(dict, nb);
	write(1, "\n", 1);
	return (1);
}
