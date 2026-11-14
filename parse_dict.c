/*
count_lines: cuenta los saltos de linea de un texto
clean_value: limpia el valor de una linea. Quita los espacios del
principio y del final, y deja solo 1 espacio entre palabras. Si queda
vacio o tiene caracteres de control (tabulador, '\r'...) da error
ej: "   hey     everybody !  " -> "hey everybody !"
parse_line: separa una linea en clave y valor poniendo '\0' en el texto,
y guarda la pareja en el array
ej: "20   :   twenty" -> clave "20", valor "twenty"
parse_text: recorre todo el texto linea a linea y llama a parse_line
con cada una (las lineas vacias se saltan)
load_dict: la que lo ejecuta todo. Lee el fichero con read_file,
reserva el array de parejas y lo rellena con parse_text.
Se llama desde main.c
*/
#include "rush02.h"

static int	count_lines(char *text)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (text[i] != '\0')
	{
		if (text[i] == '\n')
			count++;
		i++;
	}
	return (count);
}

static int	clean_value(char *value)
{
	int	r;
	int	w;

	r = 0;
	w = 0;
	while (value[r] != '\0')
	{
		if ((value[r] >= 1 && value[r] <= 31) || value[r] == 127)
			return (0);
		if (value[r] != ' ' || (w > 0 && value[w - 1] != ' '))
		{
			value[w] = value[r];
			w++;
		}
		r++;
	}
	if (w > 0 && value[w - 1] == ' ')
		w--;
	value[w] = '\0';
	return (w > 0);
}

static int	parse_line(t_dict *dict, char *line)
{
	char	*value;
	int		i;
	int		key_len;

	i = 0;
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	key_len = i;
	while (line[i] == ' ')
		i++;
	if (key_len == 0 || line[i] != ':')
		return (0);
	value = line + i + 1;
	if (!clean_value(value))
		return (0);
	line[key_len] = '\0';
	dict->entries[dict->size].key = skip_zeros(line);
	dict->entries[dict->size].value = value;
	dict->size++;
	return (1);
}

static int	parse_text(t_dict *dict)
{
	char	*line;
	int		i;

	line = dict->text;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\n')
		{
			line[i] = '\0';
			if (line[0] != '\0' && !parse_line(dict, line))
				return (0);
			line = line + i + 1;
			i = 0;
		}
		else
			i++;
	}
	if (line[0] != '\0' && !parse_line(dict, line))
		return (0);
	return (1);
}

int	load_dict(t_dict *dict, char *path)
{
	dict->entries = NULL;
	dict->size = 0;
	dict->text = read_file(path);
	if (dict->text == NULL)
		return (0);
	dict->entries = malloc(sizeof(t_entry) * count_lines(dict->text));
	if (dict->entries == NULL)
		return (0);
	return (parse_text(dict));
}
