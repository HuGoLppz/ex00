
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
