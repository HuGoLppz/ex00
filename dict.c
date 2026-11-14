/*
Aquí están las funciones que usan el diccionario ya cargado:
-find_value: busca una clave en el array de parejas y devuelve su valor
(o NULL si no está)
-say_word: escribe la palabra de una clave. En el ensayo (print == 0)
solo comprueba que existe. Si no es la primera palabra pone un espacio
delante
-say_digits: crea una clave de 1 o 2 cifras y la busca
ej: ('4', '0') -> "40" -> forty
-say_scale: crea la clave de una escala (un 1 seguido de ceros) y la
busca
ej: 6 ceros -> "1000000" -> million
-free_dict: libera la memoria del diccionario (text y entries)
*/
#include "rush02.h"

static char	*find_value(t_dict *dict, char *key)
{
	int	i;

	i = 0;
	while (i < dict->size)
	{
		if (ft_strcmp(dict->entries[i].key, key) == 0)
			return (dict->entries[i].value);
		i++;
	}
	return (NULL);
}

int	say_word(t_dict *dict, char *key)
{
	char	*value;

	value = find_value(dict, key);
	if (value == NULL)
		return (0);
	if (dict->print == 1)
	{
		if (dict->first == 0)
			write(1, " ", 1);
		ft_putstr(value);
		dict->first = 0;
	}
	return (1);
}

int	say_digits(t_dict *dict, char a, char b)
{
	char	key[3];

	key[0] = a;
	key[1] = b;
	key[2] = '\0';
	return (say_word(dict, key));
}

int	say_scale(t_dict *dict, int zeros)
{
	char	*key;
	int		i;
	int		ok;

	key = malloc(zeros + 2);
	if (key == NULL)
		return (0);
	key[0] = '1';
	i = 1;
	while (i <= zeros)
	{
		key[i] = '0';
		i++;
	}
	key[i] = '\0';
	ok = say_word(dict, key);
	free(key);
	return (ok);
}

void	free_dict(t_dict *dict)
{
	free(dict->entries);
	free(dict->text);
	dict->entries = NULL;
	dict->text = NULL;
}
